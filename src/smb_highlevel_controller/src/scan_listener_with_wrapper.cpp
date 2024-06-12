#include"ros/ros.h"
#include"sensor_msgs/LaserScan.h"
#include"geometry_msgs/Twist.h"
#include<vector>
#include<stdlib.h>

#include"LaserScan.hpp"


int main(int argc, char ** argv) {
    ros::init(argc, argv, "laser_scan_wrapper");

    LaserScanWrapper scan_wrapper;

    scan_wrapper.get_params();
    scan_wrapper.init_subscriber();
    scan_wrapper.init_publisher();

    ros::Rate loop_rate(15);

    while (ros::ok)
    {   
        ros::spinOnce();
        scan_wrapper.publish_twist();
        loop_rate.sleep();
    }
    


}