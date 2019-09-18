#pragma once

#include <thread>
#include <tf/transform_listener.h>
#include <tf/tf.h>
#include <smacc_navigation_plugin/move_base_to_goal.h>
#include <smacc_odom_tracker/odom_tracker.h>
#include <smacc_planner_switcher/planner_switcher.h>

class SbNavigateBackwards : public smacc::SmaccSubStateBehavior
{
public:
    boost::optional<float> backwardDistance;

    // just a stub to show how to use parameterless constructor
    boost::optional<float> backwardSpeed;

    tf::TransformListener listener;

    smacc::SmaccMoveBaseActionClient *moveBaseClient_;

    smacc_odom_tracker::OdomTracker *odomTracker_;

    smacc_planner_switcher::PlannerSwitcher *plannerSwitcher_;

    SbNavigateBackwards(float backwardDistance)
    {
        if(backwardDistance <0 )
        {
            ROS_ERROR("sb backward: distance must be greater or equal than 0");
            this->backwardDistance = 0;
        }
        this->backwardDistance = backwardDistance;
    }

    SbNavigateBackwards()
    {
    }

    virtual void onEntry() override
    {
        // straight motion distance
        double dist;

        if (!backwardDistance)
        {
            this->currentState->param("straight_motion_distance", dist, 3.5);
        }
        else
        {
            dist = *backwardDistance;
        }

        ROS_INFO_STREAM("Straight motion distance: " << dist);

        this->requiresComponent(moveBaseClient_, ros::NodeHandle("move_base"));
        this->requiresComponent(odomTracker_);
        this->requiresComponent(plannerSwitcher_, ros::NodeHandle("move_base"));

        //this should work better with a coroutine and await
        ros::Rate rate(10.0);
        tf::StampedTransform currentPose;

        while (ros::ok())
        {
            try
            {
                listener.lookupTransform("/odom", "/base_link", 
                                         ros::Time(0), currentPose);

                break;
            }
            catch (tf::TransformException ex)
            {
                ROS_ERROR("%s", ex.what());
                ros::Duration(1.0).sleep();
            }
        }

        tf::Transform forwardDeltaTransform;
        forwardDeltaTransform.setIdentity();
        forwardDeltaTransform.setOrigin(tf::Vector3(-dist, 0, 0));

        tf::Transform targetPose = currentPose * forwardDeltaTransform;

        smacc::SmaccMoveBaseActionClient::Goal goal;
        goal.target_pose.header.frame_id = "/odom";
        goal.target_pose.header.stamp = ros::Time::now();
        tf::poseTFToMsg(targetPose, goal.target_pose.pose);

        ROS_INFO_STREAM("TARGET POSE FORWARD: " << goal.target_pose.pose);
        ros::Duration(10).sleep();
        this->odomTracker_->clearPath();

        geometry_msgs::PoseStamped currentPoseMsg;
        currentPoseMsg.header.frame_id = "/odom";
        currentPoseMsg.header.stamp = ros::Time::now();
        tf::poseTFToMsg(currentPose, currentPoseMsg.pose);
        this->odomTracker_->setStartPoint(currentPoseMsg);
        this->odomTracker_->setWorkingMode(smacc_odom_tracker::WorkingMode::RECORD_PATH_FORWARD);

        this->plannerSwitcher_->setBackwardPlanner();

        moveBaseClient_->sendGoal(goal);
    }

    virtual bool onExit()
    {
        this->odomTracker_->setWorkingMode(smacc_odom_tracker::WorkingMode::IDLE);
    }
};
