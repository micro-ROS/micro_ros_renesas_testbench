#!/bin/bash

SCRIPTS_DIR=$(dirname -- "${BASH_SOURCE[0]}")
RA6M5_DEVICE="R7FA6M5BH3CFC"
RA6M5_FOLDER="EK_RA6M5"

RA6T2_DEVICE="R7FA6T2BD3CFP"
RA6T2_FOLDER="MCK_RA6T2"

# Delete all microros libraries folders
find . -name "libmicroros" -type d -exec rm -rf "{}" \;

# Delete all makefile.init files
find . -name "makefile.init" -type f -exec rm -rf "{}" \;

# Exit when any command fails
set -e

# Get connected device
DEVICE=$(bash ${SCRIPTS_DIR}/get_device.sh)

if [[ ${DEVICE} = ${RA6M5_DEVICE} ]]; then
    BOARD_FOLDER=${RA6M5_FOLDER}
elif [[ ${DEVICE} = ${RA6T2_DEVICE} ]]; then
    BOARD_FOLDER=${RA6T2_FOLDER}
else
    echo "Incompatible device: ${DEVICE}"
fi

echo "Device connected: ${BOARD_FOLDER}."
PROJECTS_PATH=ros_ws/src/micro_ros_renesas_testbench/boards/${BOARD_FOLDER}

# Temporal fix, remove when CAN project is added to RA6T2
if [[ ${DEVICE} == ${RA6M5_DEVICE} ]]; then
    # Compile CAN library
    pushd ${PROJECTS_PATH}/e2studio_project_CAN/micro-ROS_tests
        echo "Building microros for: ${PROJECTS_PATH}/e2studio_project_CAN/micro-ROS_tests"
        make clean && make -j$(nproc)
    popd
fi

# Compile serial library
pushd ${PROJECTS_PATH}/e2studio_project_serial/micro-ROS_tests
    echo "Building microros for: ${PROJECTS_PATH}/e2studio_project_serial/micro-ROS_tests"
    make clean && make -j$(nproc)
popd

# Copying library to speed up tests
if [[ ${DEVICE} == ${RA6M5_DEVICE} ]]; then
    for PROJECT in "e2studio_project_USB" "e2studio_project_freeRTOS" "e2studio_project_threadX" "e2studio_project_wifi"
    do
        ## e2studio_project_USB
        cp -r -n ${PROJECTS_PATH}/e2studio_project_serial/micro_ros_renesas2estudio_component/libmicroros/ ${PROJECTS_PATH}/${PROJECT}/micro_ros_renesas2estudio_component/
        pushd ${PROJECTS_PATH}/${PROJECT}/micro-ROS_tests
            make clean && make -j$(nproc)
        popd
    done
fi
