#include"ros/ros.h"
#include"sensor_msgs/LaserScan.h"
#include<vector>

void laserscan_callback(const sensor_msgs::LaserScan& msg) {
    
    // std::vector<float> ranges = msg.ranges;
    float min = msg.range_max;
    for (float range : msg.ranges) {
        if ( range < min && range >= msg.range_min) { // se o range atual eh menor que o menor ja registrado E maior ou igual ao minimo
            min = range;
        }
    }
    ROS_INFO("Range minimo: %f", min);
}

int main(int argc, char ** argv) {
    ros::init(argc, argv, "scan_listener");

    ros::NodeHandle n("~");

    ros::Subscriber laser_listener = n.subscribe("/scan", 10, laserscan_callback);

    ros::spin();
    return 0;
}