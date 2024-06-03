#include"ros/ros.h"
#include"geometry_msgs/Twist.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "my_walker");

    ros::NodeHandle n;

    ros::Publisher walker = n.advertise<geometry_msgs::Twist>("smb_velocity_controller/cmd_vel", 1000);

    ros::Rate rate(50);

    while (ros::ok()) {
        geometry_msgs::Twist msg;
        msg.linear.x = 5;

        ROS_INFO("Publicando mensagem: velocidade x: %lf", msg.linear.x);
        
        walker.publish(msg);

        ros::spinOnce();

        rate.sleep();
    }
}