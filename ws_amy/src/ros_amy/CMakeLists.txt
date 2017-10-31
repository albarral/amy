cmake_minimum_required(VERSION 2.8.3)

project(ros_amy)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(catkin REQUIRED COMPONENTS
  actionlib
  control_msgs
  roscpp
)

find_package(tron REQUIRED)
find_package(amy REQUIRED)

catkin_package(CATKIN_DEPENDS 
  actionlib
  control_msgs
  roscpp
  DEPENDS
  tron
  amy
)

include_directories(${catkin_INCLUDE_DIRS} ${tron_INCLUDE_DIRS} ${amy_INCLUDE_DIRS})

add_executable(ros_amyarm src/RosAmyArm.cpp src/YoubotArm.cpp src/UR5Arm.cpp)

target_link_libraries(ros_amyarm ${catkin_LIBRARIES} ${tron_LIBRARIES} ${amy_LIBRARIES})

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
