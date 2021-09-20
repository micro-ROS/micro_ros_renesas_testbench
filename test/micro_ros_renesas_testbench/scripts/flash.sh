#!/bin/bash

PROJECT_NAME=$1
binary_path=$PWD/src/micro_ros_renesas_testbench/$PROJECT_NAME/micro-ROS_tests/microros_testbench.hex

rfp-cli -device RA -tool e2 -s 6000000 -noprogress -run -p $binary_path > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "E2 emulator failed, trying with Jlink"
    rfp-cli -device RA -tool jlink -noprogress -run -p $binary_path > /dev/null 2>&1
fi

exit $?