cmake_minimum_required(VERSION 2.8.3)
project(minimization)	

add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  geometry_msgs
  sensor_msgs
  message_generation
  std_msgs
  std_srvs
  tf
)

#find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)
find_package(Eigen3 QUIET)
#find_package(catkin REQUIRED genmsg actionlib_msgs actionlib)

if(NOT EIGEN3_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(EIGEN3 REQUIRED eigen3)
    set(EIGEN3_INCLUDE_DIR ${EIGEN3_INCLUDE_DIRS})
endif()


add_service_files(
   FILES
)

# include_directories(${EIGEN3_INCLUDE_DIR})
# include_directories(include/${PROJECT_NAME})
# include_directories(src)

catkin_package(
  INCLUDE_DIRS 
   include/${PROJECT_NAME}
  CATKIN_DEPENDS 
   roscpp
   rospy
   geometry_msgs
   sensor_msgs
   std_msgs
   message_runtime
   tf
  DEPENDS
   Boost
 )

include_directories(
  include/${PROJECT_NAME}
  src
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_executable(Example src/Example.cpp include/minimization/Path.h include/minimization/Trajectory.h ${SOURCES})
target_link_libraries(Example ${catkin_LIBRARIES})
add_dependencies(Example ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS}) 


# add_executable(Test src/Test.cpp include/minimization/Path.h include/minimization/Trajectory.h)
# target_link_libraries(Test ${catkin_LIBRARIES})
# add_dependencies(Test ${catkin_EXPORTED_TARGETS})

install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)


###################################################################

# add_executable(nav_service_test src/service_test.cpp ${SOURCES})
# target_link_libraries(nav_service_test ${catkin_LIBRARIES})
# add_dependencies(nav_service_test ${catkin_EXPORTED_TARGETS} villa_navi_service_gencpp)


# add_executable(client_test src/service_client.cpp ${SOURCES})
# target_link_libraries(client_test ${catkin_LIBRARIES} )
# add_dependencies(client_test ${catkin_EXPORTED_TARGETS} villa_navi_service_gencpp)

# add_executable(waypoint_test src/waypoint_client.cpp ${SOURCES})
# target_link_libraries(waypoint_test ${catkin_LIBRARIES})
# add_dependencies(waypoint_test  ${catkin_EXPORTED_TARGETS} villa_navi_service_gencpp )

# add_executable(waypoint_server src/waypoint_server_node.cpp ${SOURCES})
# target_link_libraries(waypoint_server ${catkin_LIBRARIES})
# add_dependencies(waypoint_server  ${catkin_EXPORTED_TARGETS} villa_navi_service_gencpp)

# add_executable(approach_server src/approach_server_node.cpp ${SOURCES})
# target_link_libraries(approach_server ${catkin_LIBRARIES})
# add_dependencies(approach_server  ${catkin_EXPORTED_TARGETS} villa_navi_service_gencpp)

# add_executable(fastapproach_server src/fastapproach_action_server.cpp ${SOURCES})
# target_link_libraries(fastapproach_server ${catkin_LIBRARIES})
# add_dependencies(fastapproach_server  ${catkin_EXPORTED_TARGETS} villa_navi_service_gencpp)

# add_executable(fastapproach_client src/fastapproach_action_client.cpp ${SOURCES})
# target_link_libraries(fastapproach_client ${catkin_LIBRARIES})
# add_dependencies(fastapproach_client  ${catkin_EXPORTED_TARGETS} villa_navi_service_gencpp)

# add_executable(fast_approach_cancel src/fastapproach_action_cancel.cpp ${SOURCES})
# target_link_libraries(fast_approach_cancel ${catkin_LIBRARIES})
# add_dependencies(fast_approach_cancel  ${catkin_EXPORTED_TARGETS} villa_navi_service_gencpp)

# add_executable(predict_waypoint src/waypoint_prediction_action.cpp ${SOURCES})
# target_link_libraries(predict_waypoint ${catkin_LIBRARIES} ${Boost_LIBRARIES})
# add_dependencies(predict_waypoint  ${catkin_EXPORTED_TARGETS} villa_navi_service_gencpp)


# install(DIRECTORY scripts/
#     DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#     USE_SOURCE_PERMISSIONS
# )
