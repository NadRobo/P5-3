#!/bin/sh
xterm  -e  "roslaunch my_robot world.launch" & 
sleep 10
xterm  -e  "roslaunch map nad_mapping.launch" &
sleep 10
xterm  -e  "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 10
xterm  -e  "rosrun teleop_twist_keyboard teleop_twist_keyboard.py" 
