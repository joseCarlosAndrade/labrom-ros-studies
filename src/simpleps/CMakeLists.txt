cmake_minimum_required(VERSION 3.0.2)
project(simpleps)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
  message_generation
)



## Generate services in the 'srv' folder
add_service_files(
  FILES
  AddTwoInts.srv
)


generate_messages(DEPENDENCIES std_msgs)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES simpleps
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


# configuração de compilaçao do publisher e subscriber
add_executable(chatter src/publisher.cpp)
target_link_libraries(chatter ${catkin_LIBRARIES})


add_executable(listener src/subscriber.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})

# configuração de compilaçao do servidor e cliente
add_executable(server_addints src/services/server.cpp)
target_link_libraries(server_addints ${catkin_LIBRARIES})


add_executable(client_addints src/services/client.cpp)
target_link_libraries(client_addints ${catkin_LIBRARIES})
