#pragma once

#include <smacc/smacc.h>
#include <ros_timer_client/cl_ros_timer.h>

namespace ros_timer_client
{
class CbTimer : public smacc::SmaccClientBehavior
{
public:
  virtual void onEntry() override;
  virtual void onExit() override;

  template <typename TObjectTag, typename TDerived>
  void configureEventSourceTypes()
  {
    this->postTimerEvent_ = [=]() {
      this->template postEvent<EvTimer<TDerived, TObjectTag>>();
    };
  }

  void onClientTimerTickCallback();

private:
  ClRosTimer *timerClient_;
  std::function<void()> postTimerEvent_;
  boost::signals2::scoped_connection c_;
};
} // namespace ros_timer_client
