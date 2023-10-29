cmake_minimum_required(VERSION 2.8.3)

project(sentry9)

find_package(catkin REQUIRED COMPONENTS
  roscpp
 std_msgs
)

catkin_package(  CATKIN_DEPENDS roscpp std_msgs message_runtime)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

find_package(roslaunch)

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)

add_executable(chassis_control src/chassis_control.cpp)
target_link_libraries(chassis_control ${catkin_LIBRARIES})
