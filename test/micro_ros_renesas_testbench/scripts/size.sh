#!/bin/bash

PROJECT_NAME=$1

library=$PWD/src/micro_ros_renesas_testbench/$PROJECT_NAME/micro_ros_renesas2estudio_component/libmicroros/libmicroros.a
mapfile=$PWD/src/micro_ros_renesas_testbench/$PROJECT_NAME/micro-ROS_tests/microros_testbench.map

echo -n $(fpvgcc $mapfile --sar | grep libmicroros.a | awk -F  "|" '/1/ {print $(NF-1)}' | tr -d " \t\n\r")
echo -n " "
echo $(arm-none-eabi-size --format=berkeley $library --totals | tail -1)