#!/bin/sh
xterm -e " roslaunch pick_objects turtlebot_world.launch " &
sleep 10
xterm -e " rosservice call /gazebo/set_model_state '{model_state: { model_name: mobile_base, pose: { position: { x: 0.0, y: -9.0 ,z: 0.0 }}}}' " &  
sleep 5
xterm -e " roslaunch pick_objects amcl.launch " &
sleep 10
#xterm -e " roslaunch turtlebot_rviz_launchers view_navigation_mark.launch " &
#sleep 10
#xterm -e " rosrun map_server map_server `rospack find pick_objects`/../world/mymap22.yaml " &
#sleep 3
#rosparam set /move_base/local_costmap/inflation_layer/parameter_updates
xterm -e " rosrun add_markers add_markers_node " &
sleep 15
xterm -e " rosrun pick_objects pick_objects_node " &

