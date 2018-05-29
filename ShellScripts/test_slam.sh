#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 10
xterm -e " rosservice call /gazebo/set_model_state '{model_state: { model_name: mobile_base, pose: { position: { x: 2.0, y: -8.0 ,z: 0.0 }, orientation: {x: 0.0, y: 0.0, z: 0.0, w: 0.0}}}}' " &   
sleep 5
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 5
rosparam set /slam_gmapping/angularUpdate 0.1
rosparam set /slam_gmapping/linearUpdate 0.2
rosparam set /slam_gmapping/lskip 5
rosparam set /slam_gmapping/xmax 0.5
rosparam set /slam_gmapping/xmin -0.5
rosparam set /slam_gmapping/ymax 0.5
rosparam set /slam_gmapping/ymin -0.5
rosparam set /slam_gmapping/map_update_interval 4.0
rosparam set /slam_gmapping/ogain 4.0
rosparam set /slam_gmapping/particles 100
#xterm -e " roslaunch turtlebot_navigation gmapping_demo.launch " &
#sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch " &
sleep 5
