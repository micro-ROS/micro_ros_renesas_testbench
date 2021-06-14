// Copyright (c) 2021 - for information on the respective copyright owner
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>

#include "./test_agent.hpp"

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std::chrono_literals;

// TODO(pablogs): use this for client code naming: https://github.com/google/googletest/blob/master/docs/advanced.md#getting-the-current-tests-name

class HardwareTest : public testing::Test
{
public:
    void SetUp() override {
      char * cwd_str = get_current_dir_name();
      cwd = std::string(cwd_str);
      free(cwd_str);

      ASSERT_TRUE(checkConnection());
      agent.reset(new TestAgent("/dev/serial/by-id/usb-RENESAS_CDC_USB_Demonstration_0000000000001-if00", 0));
      rclcpp::init(0, NULL);
      node = std::make_shared<rclcpp::Node>("test_node");
    }

    void TearDown() override {
      agent->stop();
      rclcpp::shutdown();
    }

    bool checkConnection(){
      std::cout << "Checking device connection ";
      bool ret = 0 == system("rfp-cli -device RA -tool jlink -reset > /dev/null 2>&1");
      std::cout << ((ret) ? "OK" : "ERROR") << std::endl;
      return ret;
    }

    bool buildClientCode(std::string filename){
      std::cout << "Building " << filename << std::endl;
      bool ret = 0 == system(("cd " + cwd + "/src/micro_ros_renesas_testbench/e2studio_project/micro-ROS_tests && make clean > /dev/null 2>&1 && make -j$(nproc) > /dev/null").c_str());
      return ret;
    }

    bool flashClientCode(){
      std::cout << "Flashing code" << std::endl;
      bool ret = 0 == system("rfp-cli -device RA -tool jlink -e -p '/project/micro-ROS_tests/microros_testbench.hex'");
      return ret;
    }

    void runClientCode(std::string filename){
      ASSERT_TRUE(buildClientCode(filename));
      // ASSERT_TRUE(flashClientCode());
      std::this_thread::sleep_for(500ms);
      agent->start();
      std::this_thread::sleep_for(1000ms);
    }

protected:
    std::unique_ptr<TestAgent> agent;
    std::shared_ptr<rclcpp::Node> node;
    std::string cwd;
};

TEST_F(HardwareTest, EntityCreation) {
  runClientCode("");

  rclcpp::spin_some(node);
  auto nodes = node->get_node_names();

  ASSERT_GT(nodes.size(), 0U);

  bool found = false;
  for(auto node : nodes){
    // std::cout << node << std::endl;
    if (node == "/renesas_node")
    {
      found = true;
    }
  }

  // TODO(pablogs): this test should wait for publishers/subscribers/services

  ASSERT_TRUE(found);
}

TEST_F(HardwareTest, EntitiesQoS) {
  // TODO(pablogs): this test should check if pub/sub/req can be created using different QoS
}

TEST_F(HardwareTest, Publisher) {
  runClientCode("");

  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();

  auto subscription = node->create_subscription<std_msgs::msg::Int32>(
    "renesas_publisher", 10,
    [&](std_msgs::msg::Int32::UniquePtr msg) {
      // std::cout << msg->data << " client data\n";
      promise->set_value();
    }
  );

  rclcpp::spin_until_future_complete(node, future.share());
}

TEST_F(HardwareTest, Subscriber) {
  // TODO(pablogs): this test should send a value and wait for the same in a subscriber
  // the client should act as a ping pong
}

TEST_F(HardwareTest, CustomTypeIntrospection) {
  // TODO(pablogs): this test should wait for a custom nested type initted with micro-ROS utilities library
  // strings
  // arrays
  // sequences
}

TEST_F(HardwareTest, PublisherContinousFragment) {
  // TODO(pablogs): this test should wait for a topic bigger than default MTU*historic
}

TEST_F(HardwareTest, TimeSync) {
  // TODO(pablogs): this test should wait for a topic with the POSIX time of a synchronized client and check if MCU epoch is ok
}

TEST_F(HardwareTest, Ping) {
  // TODO(pablogs): this test should rely on a publisher that will publish only if ping works ok
}

TEST_F(HardwareTest, ServiceServer) {
  // TODO(pablogs): this test should prepare a service server and wait for client requests
}

TEST_F(HardwareTest, ServiceClient) {
  // TODO(pablogs): this test should prepare a service client and send requests to the client
}

TEST_F(HardwareTest, Parameters) {
  // TODO(pablogs): this test should test the client's parameter server
}

TEST_F(HardwareTest, ExecutorRate) {
  // TODO(pablogs): this test should check if publication rate is ok when using a executor timer
}

TEST_F(HardwareTest, Domain) {
  // TODO(pablogs): this test should nodes from different domains are visible
}

TEST_F(HardwareTest, Multithread) {
  // TODO(pablogs): this test should check if pub/sub/services works from different threads
  // Rensas hardware have no threads at this moment
}