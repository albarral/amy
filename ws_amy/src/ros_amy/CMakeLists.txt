cmake_minimum_required(VERSION 2.8.3)

project(ros_amy)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(catkin REQUIRED COMPONENTS
  actionlib
  control_msgs
  roscpp
)

find_package(Tron REQUIRED)
find_package(Amy REQUIRED)
find_package(Ignition REQUIRED)
find_package(Protobuf REQUIRED)


catkin_package(CATKIN_DEPENDS 
  actionlib
  control_msgs
  roscpp
  DEPENDS
  tron
  amy
)


include_directories(${catkin_INCLUDE_DIRS})
include_directories(${TRON_INCLUDE_DIRS})
include_directories(${AMY_INCLUDE_DIRS})
include_directories(${IGNITION_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})

add_executable(ros_amyarm src/RosAmyArm.cpp src/YoubotArm.cpp src/UR5Arm.cpp)

target_link_libraries(ros_amyarm ${catkin_LIBRARIES}
				 ${TRON_LIBRARIES} 
				 ${AMY_LIBRARIES} 
				 ${IGNITION_LIBRARIES} 
				 ${PROTOBUF_LIBRARIES})

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
