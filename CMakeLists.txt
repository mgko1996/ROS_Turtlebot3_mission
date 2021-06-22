cmake_minimum_required(VERSION 2.8.3)
project(midterm_kmg)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  sensor_msgs
  std_msgs
)
## msg_1: power
## msg_2: velocity
## msg_3: angle

add_message_files(FILES msg_1.msg msg_2.msg msg_3.msg)

generate_messages(DEPENDENCIES sensor_msgs std_msgs)


catkin_package(
  LIBRARIES midterm_kmg
  CATKIN_DEPENDS roscpp sensor_msgs std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## mid_1 : (publisher) = input power(0,1)
add_executable(mid_1 src/mid_1.cpp) 
add_dependencies(mid_1 ${${PROJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPOTED_TARGETS})
target_link_libraries(mid_1 ${catkin_LIBRARIES})

## mid_2 : (publisher) = input velocity(0~1)
add_executable(mid_2 src/mid_2.cpp) 
add_dependencies(mid_2 ${${PROJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPOTED_TARGETS})
target_link_libraries(mid_2 ${catkin_LIBRARIES})

## mid_3 : (publisher) = input angle(0~359)
add_executable(mid_3 src/mid_3.cpp) 
add_dependencies(mid_3 ${${PROJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPOTED_TARGETS})
target_link_libraries(mid_3 ${catkin_LIBRARIES})

## mid_4 : (subscriber) 
## if (motor power off) => motor stop
## if (robot tilts below -45 or more than 45) => motor stop
## if (minimum distance between angle1, angle2 < 0.3) =>motor stop
## Show minimum distance value between two angles / 1 sec
add_executable(mid_4 src/mid_4.cpp) 
add_dependencies(mid_4 ${${PROJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPOTED_TARGETS})
target_link_libraries(mid_4 ${catkin_LIBRARIES})

## mid_5 : (subscriber)
## Show angle tilted forward, backward, left, right / 100ms 
add_executable(mid_5 src/mid_5.cpp) 
add_dependencies(mid_5 ${${PROJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPOTED_TARGETS})
target_link_libraries(mid_5 ${catkin_LIBRARIES})
