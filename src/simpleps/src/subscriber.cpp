#include"ros/ros.h"
#include"std_msgs/String.h"

void msg_callback(const std_msgs::String& msg) {
    ROS_INFO("%s", msg.data.c_str());
}

int main(int argc, char ** argv) {
    ros::init(argc, argv, "listener");

    ros::NodeHandle n;

    ros::Subscriber listener = n.subscribe("chatter", 1000, msg_callback);

    ros::spin();

    return 0;
}