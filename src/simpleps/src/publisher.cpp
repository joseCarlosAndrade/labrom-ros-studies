#include"ros/ros.h"
#include "std_msgs/String.h"

#include<sstream>
#include<string>

int main(int argc, char** argv) {
    ros::init(argc, argv, "chatter");

    ros::NodeHandle n ; // handler do no, serve para criar pubs, subs, services, clients

    ros::Publisher chatter = n.advertise<std_msgs::String>("chatter", 1000);

    ros::Rate loop_rate(10);

    int count = 0;
    while (ros::ok()) {
        std_msgs::String msg ; // criando mensagem do tipo std_msgs -> String

        std::stringstream string_stream ; // criando um stream de string para podermos usar o operador << para redirecionar buffers (concatenar strings de forma rapida)
        string_stream << "Mensagem aqui! Contagem: " << count; 
        
        // std::stringstream::str transforma o buffer da stream em uma string
        msg.data = string_stream.str();

        ROS_INFO("%s", msg.data.c_str()); // c_str retorna um char *

        chatter.publish(msg);

        ros::spinOnce(); // processa todas as callbacks recebidas ate aqui, neste loop

        loop_rate.sleep(); // aguarda a faixa descrita em loop_rate, podendo assim customizar a frequencia de publicação

        count++;
    }
}