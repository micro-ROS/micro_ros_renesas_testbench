cmake_minimum_required(VERSION 3.5)
project(micro_ros_renesas_testbench)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

option(UBUILD_TEST_BENCHMARK "Build benchmark tests cases." ON)

#################################################
# package dependencies
#################################################
find_package(ament_cmake REQUIRED)

#################################################
# testing
#################################################
if(BUILD_TESTING)
  # find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE) # No copyright header check since link to NOTICE file is not recognized properly.

  find_package(fastcdr REQUIRED)
  find_package(fastrtps REQUIRED)
  find_package(fastrtps_cmake_module REQUIRED)
  find_package(microxrcedds_agent REQUIRED)
  find_package(rclcpp REQUIRED)
  find_package(rmw REQUIRED)
  find_package(std_msgs REQUIRED)
  find_package(sensor_msgs REQUIRED)
  find_package(example_interfaces REQUIRED)

  # ament_lint_auto_find_test_dependencies()

  ament_add_gtest(${PROJECT_NAME}_test
    test/micro_ros_renesas_testbench/test.cpp
    test/micro_ros_renesas_testbench/test_agent.cpp
    test/micro_ros_renesas_testbench/test_regressions.cpp
    $<$<BOOL:${UBUILD_TEST_BENCHMARK}>:test/micro_ros_renesas_testbench/test_benchmark.cpp>
  )

  string(TOUPPER $ENV{ROS_DISTRO} ROS_DISTRO)
  target_compile_options(${PROJECT_NAME}_test PRIVATE -DROS_DISTRO_${ROS_DISTRO})
  target_include_directories(${PROJECT_NAME}_test PRIVATE include src test)

  target_link_libraries(${PROJECT_NAME}_test
    fastcdr
    fastrtps
    microxrcedds_agent)

  ament_target_dependencies(${PROJECT_NAME}_test
    fastcdr
    fastrtps
    microxrcedds_agent
    rclcpp
    rmw
    std_msgs
    sensor_msgs
    example_interfaces
  )
endif()

ament_package()
