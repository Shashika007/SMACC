#include <ros_timer_client/client_behaviors/cb_ros_timer.h>

namespace ros_timer_client
{
void CbTimer::onEntry()
{
    this->requiresClient(timerClient_);

    timerClient_->onTimerTick(&CbTimer::onClientTimerTickCallback, this);
}

void CbTimer::onClientTimerTickCallback()
{
    this->postTimerEvent_();
}

void CbTimer::onExit()
{
}
} // namespace ros_timer_client