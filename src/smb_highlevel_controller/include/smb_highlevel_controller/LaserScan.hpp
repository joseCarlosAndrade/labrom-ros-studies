#ifndef LASER_SCAN_H
#define LASER_SCAN_H

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

class LaserScanWrapper  {
    private:
        ros::NodeHandle this_n;
        ros::Publisher publisher;
        ros::Subscriber subscriber;

        geometry_msgs::Twist twist_msg;
        std::string topic_name;
        int queue_size;
        float k_p_linear;
        float k_p_angular;

        bool is_detected = false;

    public:
        LaserScanWrapper();

        LaserScanWrapper(ros::NodeHandle n);
        int get_params(); 

        void laser_scan_callback(const sensor_msgs::LaserScan msg) ;

        void init_subscriber();

        void init_publisher();

        void publish_twist();

};



#endif