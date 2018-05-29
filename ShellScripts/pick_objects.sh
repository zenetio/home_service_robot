#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 10
xterm -e " rosservice call /gazebo/set_model_state '{model_state: { model_name: mobile_base, pose: { position: { x: 0.0, y: -9.0 ,z: 0.0 }}}}' " &  
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5
xterm -e " rosrun map_server map_server `rospack find pick_objects`/../world/mymap22.yaml " &
sleep 3


