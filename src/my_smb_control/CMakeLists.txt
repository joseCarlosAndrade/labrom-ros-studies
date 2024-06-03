cmake_minimum_required(VERSION 3.0.2)
project(my_smb_control)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  # message_generation
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES simpleps
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

# generate_messages(DEPENDENCIES geometry_msgs)

# nao remover!!!!!! ros/ros.h e outros includes padroes
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(my_walker src/my_walker.cpp)
target_link_libraries(my_walker ${catkin_LIBRARIES})