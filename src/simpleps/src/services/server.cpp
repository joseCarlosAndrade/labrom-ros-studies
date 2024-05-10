#include"ros/ros.h"
#include"simpleps/AddTwoInts.h"

/*
requisição:
int64 a
int64 b

resposta:
int64 sum
*/

// callback que é chamado quando o serviço é solicitado 
bool add_two_ints(
    simpleps::AddTwoInts::Request &req, 
    simpleps::AddTwoInts::Response &res) {
        res.sum = req.a + req.b;

        ROS_INFO("Requisicao solicitada: %ld + %ld", (long int) req.a, (long int) req.b);
        ROS_INFO("Resposta: %ld", (long int) res.sum);

        return true; // serviço concluido com sucesso
    }

int main(int argc, char ** argv) {
    ros::init(argc, argv, "add_ints_server");

    ros::NodeHandle node_handle;

    // advertising o serviço 'add_two_ints_please', dizendo tambem que o callback eh a funcao
    // add_two_ints 
    ros::ServiceServer server = node_handle.advertiseService("add_two_ints_please", add_two_ints);

    ROS_INFO("yes bab im ready");
    ros::spin();
}
