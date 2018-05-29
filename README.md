# Home Service Robot Project #
### Autor: Carlos R. Lacerda

## The goal of this project is to program a robot that can autonomously map an environment and navigate to pick up and drop virtual objects.

Steps to follow:

1. Create a directory tree to store all files

```sh
├──                                # Official ROS packages
    |
    ├── slam_gmapping                  # gmapping_demo.launch file                   
    │   ├── gmapping
    │   ├── ...
    ├── turtlebot                      # keyboard_teleop.launch file
    │   ├── turtlebot_teleop
    │   ├── ...
    ├── turtlebot_interactions         # view_navigation.launch file      
    │   ├── turtlebot_rviz_launchers
    │   ├── ...
    ├── turtlebot_simulator            # turtlebot_world.launch file 
    │   ├── turtlebot_gazebo
    │   ├── ...
    ├──                                # Your packages and direcotries
    |
    ├── World                          # world files
    │   ├── ...
    ├── ShellScripts                   # shell scripts files
    │   ├── ...
    ├──RvizConfig                      # rviz configuration files
    │   ├── ...
    ├──wall_follower                   # wall_follower C++ node
    │   ├── src/wall_follower.cpp
    │   ├── ...
    ├──pick_objects                    # pick_objects C++ node
    │   ├── src/pick_objects.cpp
    │   ├── ...
    ├──add_markers                     # add_marker C++ node
    │   ├── src/add_markers.cpp
    │   ├── ...
    └──

```
2. Download the following ROS packages
- gmapping
- turtlebot_teleop
- turtlebot_rviz_launches
- turtlebot_gazebo

3. Create the following shell script files
- test_navigation.sh: use to test the ROS navigation stack
- test_slam.sh: test the slam package using teleop package
- wall_follower.sh: implement a C++ wall follower node used to map the environment
- add_marker.sh: implement a C++ node to add virtual objects to the map
- pick_objects.sh: implement a C++ node to pick up and drop a virtual object in pre-defined locations.
- home_services.sh: putting all together, the robot, autonomously, drive to pick up location to pick the object and move it to drop location.

The video with complete task can be seen [here](https://youtu.be/TwfmYsqqbQQ)

