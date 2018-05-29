#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 10
xterm -e " rosservice call /gazebo/set_model_state '{model_state: { model_name: mobile_base, pose: { position: { x: 4.0, y: -1.0 ,z: 0.0 }, orientation: {x: 0.0, y: 0.0, z: 0.0, w: 0.0}}}}' " & 
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation_mark.launch " &
sleep 5
xterm -e " rosrun map_server map_server `rospack find pick_objects`/../world/mymap22.yaml " &
sleep 3
xterm -e " rosrun add_markers add_markers_node " &
sleep 3

