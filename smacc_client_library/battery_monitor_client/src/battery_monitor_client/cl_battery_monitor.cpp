#include <battery_monitor_client/cl_battery_monitor.h>

namespace battery_monitor_client
{

ClBatteryMonitor::ClBatteryMonitor()
{
}

ClBatteryMonitor::ClBatteryMonitor(std::string topicname)
    : smacc::client_bases::SmaccSubscriberClient<sensor_msgs::BatteryState>(topicname)
{

}

ClBatteryMonitor::~ClBatteryMonitor()
{
}

} 