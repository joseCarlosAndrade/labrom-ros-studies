#include"LaserScan.hpp"

LaserScanWrapper::LaserScanWrapper() : this_n("~") {
            // construtor que inicializa o node handle 
        }

LaserScanWrapper::LaserScanWrapper(ros::NodeHandle n) : this_n(n) {
    // construtor que recebe um nodehandle por parametro

}

int LaserScanWrapper::get_params() {
    if (!this_n.getParam("/my_scan_listener/topic/name", topic_name) 
        || !this_n.getParam("/my_scan_listener/topic/queue", queue_size)
        || !this_n.getParam("/my_scan_listener/laser_controller/k_p_linear", k_p_linear)
        || !this_n.getParam("/my_scan_listener/laser_controller/k_p_angular", k_p_angular)) {
        
        ROS_ERROR("Parametros nao encontrados.");
        return 0;
    }
    ROS_INFO("Parametros incluidos.");
    return 1;
    
}

void LaserScanWrapper::laser_scan_callback(const sensor_msgs::LaserScan msg) {
    int i = 0;
    int min_i = 0;
    float min = msg.range_max;
    for (float range : msg.ranges) {
        if ( range < min && range >= msg.range_min) { // se o range atual eh menor que o menor ja registrado E maior ou igual ao minimo
            min = range;
            min_i = i;
            this->is_detected = true;
        }
        i++;
    }

    float angle = msg.angle_min + (min_i * msg.angle_increment); 

    if( min_i > 0) {
        twist_msg.angular.z = -1*(M_PI + msg.angle_min - (min_i * msg.angle_increment))*this->k_p_angular ; 
        twist_msg.linear.x = (min) * this->k_p_linear;

    } else { // rodando quando nao encontra objeto
        ROS_WARN("Objeto nao detectado, procurando..");
        twist_msg.angular.z = 3;
        twist_msg.linear.x = 1;
    }
    
    // ROS_INFO("\n=======\ni: %d, ang: %f, ang_min :%f, \n\nRange minimo: %f\nAngulo z: %f\nVel x: %f\n, ", min_i, angle, msg.angle_min,
    // min, twist_msg.angular.z, twist_msg.linear.x);
}

void LaserScanWrapper::init_subscriber() {
    this->subscriber = this_n.subscribe(this->topic_name, this->queue_size, &LaserScanWrapper::laser_scan_callback, this);

}

void LaserScanWrapper::init_publisher() {
    this->publisher = this->this_n.advertise<geometry_msgs::Twist>("/cmd_vel", this->queue_size);
}   

void LaserScanWrapper::publish_twist() {
    this->publisher.publish(this->twist_msg);
    ROS_INFO("Twist: x: %f, w: %f", this->twist_msg.linear.x, this->twist_msg.angular.z);
}