#include"ros/ros.h"
#include"sensor_msgs/LaserScan.h"
#include<vector>
#include<stdlib.h>

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

    // pegando parametros
    std::string topic_name;
    int queue;
    ros::NodeHandle n("~");
    
    if (!n.getParam("/my_scan_listener/topic/name", topic_name) || !n.getParam("/my_scan_listener/topic/queue", queue)) {
        ROS_ERROR("Parâmetros não encontrados!");
        exit(EXIT_FAILURE);
    }

    ros::Subscriber laser_listener = n.subscribe(topic_name, queue, laserscan_callback);

    ros::spin();
    return 0;
}