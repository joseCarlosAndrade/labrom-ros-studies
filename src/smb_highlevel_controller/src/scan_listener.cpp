#include"ros/ros.h"
#include"sensor_msgs/LaserScan.h"
#include"geometry_msgs/Twist.h"
#include<vector>
#include<stdlib.h>

#include"LaserScan.hpp"

geometry_msgs::Twist twist_msg;


void laserscan_callback(const sensor_msgs::LaserScan& msg) {
    
    // std::vector<float> ranges = msg.ranges;
    int i = 0;
    int min_i = 0;
    float min = msg.range_max;
    for (float range : msg.ranges) {
        if ( range < min && range >= msg.range_min) { // se o range atual eh menor que o menor ja registrado E maior ou igual ao minimo
            min = range;
            min_i = i;
        }
        i++;
    }

    float angle = msg.angle_min + (min_i * msg.angle_increment); 

    if( min_i > 0) {
        twist_msg.angular.z = -1*(M_PI + msg.angle_min - (min_i * msg.angle_increment))*2 ; 
        twist_msg.linear.x = min/5;

    } else { // rodando quando nao encontra objeto
        twist_msg.angular.z = 1;
        twist_msg.linear.x = 1;
    }
    
    ROS_INFO("\n=======\ni: %d, ang: %f, ang_min :%f, \n\nRange minimo: %f\nAngulo z: %f\nVel x: %f\n, ", min_i, angle, msg.angle_min,
    min, twist_msg.angular.z, twist_msg.linear.x);
}

int main(int argc, char ** argv) {
    ros::init(argc, argv, "scan_listener");

    // pegando parametros
    std::string topic_name;
    int queue;
    int k_p_linear;
    int k_p_angular;
    ros::NodeHandle n("~");
    
    if (!n.getParam("/my_scan_listener/topic/name", topic_name) 
        || !n.getParam("/my_scan_listener/topic/queue", queue)
        || !n.getParam("/my_scan_listener/laser_controller/k_p_linear", k_p_linear)
        || !n.getParam("/my_scan_listener/laser_controller/k_p_angular", k_p_angular)) {
        ROS_ERROR("Parâmetros não encontrados!");
        exit(EXIT_FAILURE);
    }

    ros::Subscriber laser_listener = n.subscribe(topic_name, queue, laserscan_callback);

    ros::Publisher cmd_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

    // ros::spin();
    ros::Rate loop_rate(15);
    
    while ( ros::ok()) {
        twist_msg.angular.z *= k_p_linear;
        twist_msg.linear.x *= k_p_angular;
        cmd_publisher.publish(twist_msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
 
    return 0;
}