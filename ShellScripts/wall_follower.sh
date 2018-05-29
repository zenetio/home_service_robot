#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 10
xterm -e " rosservice call /gazebo/set_model_state '{model_state: { model_name: mobile_base, pose: { position: { x: -0.0, y: -9.0 ,z: 0.0 }, orientation: {x: 0.0, y: 0.0, z: 00, w: 0.0}}}}' " &  
sleep 5
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 5
#rosparam set /slam_gmapping/angularUpdate 0.1
#rosparam set /slam_gmapping/linearUpdate 0.1
#rosparam set /slam_gmapping/lskip 10
#rosparam set /slam_gmapping/xmax 10
#rosparam set /slam_gmapping/xmin -10
#rosparam set /slam_gmapping/ymax 10
#rosparam set /slam_gmapping/ymin -10
#rosparam set /slam_gmapping/map_update_interval 2.0
#rosparam set /slam_gmapping/ogain 4.0
rosparam set /slam_gmapping/particles 100
rosparam set /slam_gmapping/minimumScore 10000
#rosparam set /slam_gmapping/entropy 0
#xterm -e " roslaunch turtlebot_navigation gmapping_demo.launch " &

sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 10
#xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch " &
#sleep 5
xterm -e " rosrun wall_follower wall_follower_node " &
