#include"ros/ros.h"
#include "simpleps/AddTwoInts.h"

int main(int argc, char ** argv) {
    ros::init(argc, argv, "add_ints_client");

    if ( argc != 3) {
        ROS_ERROR("Uso correto: add_two_ints x y");
        return EXIT_FAILURE;
    }

    ros::NodeHandle node_handle;
    // criando um cliente que pode chamar o servico "add_two_ints_please"
    ros::ServiceClient client = node_handle.serviceClient<simpleps::AddTwoInts>("add_two_ints_please");

    // criando a requisiçao
    simpleps::AddTwoInts srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);

    // fazendo a requisiçao
    if (client.call(srv)) {
        ROS_INFO("chique: %ld", (long int) srv.response.sum);
        return EXIT_SUCCESS;

    } else {
        ROS_ERROR("num deu");
        return EXIT_FAILURE;
    }
}