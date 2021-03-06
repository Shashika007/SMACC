namespace sm_dance_bot_strikes_back
{
namespace s_pattern_states
{
// STATE DECLARATION
struct StiSPatternRotate1 : smacc::SmaccState<StiSPatternRotate1, SS>
{
    using SmaccState::SmaccState;

// TRANSITION TABLE
    typedef mpl::list<
    
    Transition<EvActionSucceeded<ClMoveBaseZ, OrNavigation>, StiSPatternForward1>,
    Transition<EvActionAborted<ClMoveBaseZ, OrNavigation>, StiSPatternLoopStart>
    
    >reactions;

// STATE FUNCTIONS
    static void staticConfigure()
    {
    }

    void runtimeConfigure()
    {
        auto &superstate = this->context<SS>();
        ROS_INFO("[StiSPatternRotate] SpatternRotate rotate: SS current iteration: %d/%d", superstate.iteration_count, SS::total_iterations());

        if (superstate.iteration_count < SS::total_iterations())
        {
            // float angle = 0;
            // if (superstate.direction() == TDirection::LEFT)
            //     angle = 90;
            // else
            //     angle = -90;
            //this->configure<OrNavigation, CbRotate>(angle);


            float offset = 7;
            if (superstate.direction() == TDirection::RIGHT)
            {
                // - offset because we are looking to the north and we have to turn clockwise
                this->configure<OrNavigation, CbAbsoluteRotate>(0 - offset);
            }
            else 
            {
                // - offset because we are looking to the south and we have to turn counter-clockwise
                this->configure<OrNavigation, CbAbsoluteRotate>(180 + offset);
            }

            this->configure<OrLED, CbLEDOff>();
        }
    }
};
} // namespace s_pattern_states
} // namespace sm_dance_bot_strikes_back