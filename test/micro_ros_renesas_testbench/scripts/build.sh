#!/bin/bash

FILENAME=$1
PROJECT_NAME=$2

source_code=$PWD/src/micro_ros_renesas_testbench/test/micro_ros_renesas_testbench/client_tests/$FILENAME.c
project_main=$PWD/src/micro_ros_renesas_testbench/$PROJECT_NAME/src/microros_app.c
build_path=$PWD/src/micro_ros_renesas_testbench/$PROJECT_NAME/micro-ROS_tests

cp $source_code $project_main > /dev/null 2>&1
make -C $build_path -j$(nproc) pre-build > /dev/null 2>&1
make -C $build_path -j$(nproc) microros_testbench.hex > /dev/null 2>&1
exit $?