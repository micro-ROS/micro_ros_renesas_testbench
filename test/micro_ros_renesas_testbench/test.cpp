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

#include "./test.hpp"

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

TEST_P(HardwareTest, EntityCreation) {
  runClientCode("EntityCreation");

  bool timeout, found;
  std::shared_ptr<std::thread> timeout_thread;

  // Utilities
  auto timeout_function = [&](){
    std::this_thread::sleep_for (std::chrono::seconds(5));
    timeout = true;
  };

  auto check_all_found = [&](std::map<const std::string, bool> & map, bool assert = false) -> bool{
    for(auto const& it : map){
      if(!it.second) {
        if(assert) {
          EXPECT_TRUE(it.second) << "Transport type not supported";
        }
        return false;
      }
    }
    return true;
  };

  // Look for created nodes
  std::map<const std::string, bool> node_map =
  {
    {"/test_node_0", false},
    {"/test_node_1", false},
    {"/test_node_2", false},
    {"/test_node_3", false},
    {"/test_node_4", false},
  };

  timeout = false;
  found = false;
  timeout_thread.reset(new std::thread(timeout_function));

  while(!timeout && !found){
    rclcpp::spin_some(node);
    auto nodes = node->get_node_names();
    for(auto node : nodes){
      if (node_map.find(node) != node_map.end()) {
          node_map[node] = true;
      }
      found = check_all_found(node_map);
    }
  }

  ASSERT_TRUE(check_all_found(node_map, true));
  timeout_thread->detach();

  // Look for created publishers and subscribers
  std::map<const std::string, bool> topics_map =
  {
    {"/ns_0/test_pub_0", false},
    {"/ns_1/test_pub_1", false},
    {"/ns_2/test_pub_2", false},
    {"/ns_3/test_pub_3", false},
    {"/ns_4/test_pub_4", false},
    {"/ns_0/test_sub_0", false},
    {"/ns_1/test_sub_1", false},
    {"/ns_2/test_sub_2", false},
    {"/ns_3/test_sub_3", false},
    {"/ns_4/test_sub_4", false},
    {"/ns_0/test_pub_0_extra", false},
    {"/ns_0/test_sub_0_extra", false},
  };

  timeout = false;
  found = false;
  timeout_thread.reset(new std::thread(timeout_function));

  while(!timeout && !found){
    rclcpp::spin_some(node);
    auto topics = node->get_topic_names_and_types();
    for(auto topic : topics){
      std::cout << "Found " << topic.first << std::endl;

      if (topics_map.find(topic.first) != topics_map.end()) {
          topics_map[topic.first] = true;
      }
      found = check_all_found(topics_map);
    }
  }

  ASSERT_TRUE(check_all_found(topics_map, true));
  timeout_thread->detach();
}

TEST_P(HardwareTest, EntitiesQoS) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should check if pub/sub/req can be created using different QoS
}

TEST_P(HardwareTest, Publisher) {
  runClientCode("");

  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();

  auto subscription = node->create_subscription<std_msgs::msg::Int32>(
    "test_publisher", 10,
    [&](std_msgs::msg::Int32::UniquePtr msg) {
      // std::cout << msg->data << " client data\n";
      promise->set_value();
    }
  );

  rclcpp::spin_until_future_complete(node, future.share());
}

TEST_P(HardwareTest, Subscriber) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should send a value and wait for the same in a subscriber
  // the client should act as a ping pong
}

TEST_P(HardwareTest, CustomTypeIntrospection) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should wait for a custom nested type initted with micro-ROS utilities library
  // strings
  // arrays
  // sequences
}

TEST_P(HardwareTest, PublisherContinousFragment) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should wait for a topic bigger than default MTU*historic
}

TEST_P(HardwareTest, TimeSync) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should wait for a topic with the POSIX time of a synchronized client and check if MCU epoch is ok
}

TEST_P(HardwareTest, Ping) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should rely on a publisher that will publish only if ping works ok
}

TEST_P(HardwareTest, ServiceServer) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should prepare a service server and wait for client requests
}

TEST_P(HardwareTest, ServiceClient) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should prepare a service client and send requests to the client
}

TEST_P(HardwareTest, Parameters) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should test the client's parameter server
}

TEST_P(HardwareTest, ExecutorRate) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should check if publication rate is ok when using a executor timer
}

TEST_P(HardwareTest, Domain) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should nodes from different domains are visible
}

TEST_P(HardwareTest, Multithread) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should check if pub/sub/services works from different threads
  // Rensas hardware have no threads at this moment
}

TEST_P(HardwareTest, PublisherFreq) {


    // manually enable topic statistics via options
    auto options = rclcpp::SubscriptionOptions();
    options.topic_stats_options.state = rclcpp::TopicStatisticsState::Enable;

    // configure the collection window and publish period (default 1s)
    //options.topic_stats_options.publish_period = std::chrono::seconds(10);

    // configure the topic name (default '/statistics')
    //options.topic_stats_options.publish_topic = "/test_publisher"

    auto callback = [this](std_msgs::msg::Int32::SharedPtr msg) {

      };
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::Int32>(
      "test_publisher", 10, callback, options);


    switch (transport)
    {
        case TestAgent::Transport::UDP_IPV4_TRANSPORT:
        case TestAgent::Transport::UDP_IPV6_TRANSPORT:
            runClientCode("threadx_publish_1hz");
            // TODO: Check publish frequency

            runClientCode("threadx_publish_20hz");
            // TODO: Check publish frequency

            break;

        case TestAgent::Transport::SERIAL_TRANSPORT:
        case TestAgent::Transport::USB_TRANSPORT:

            break;
    }
}

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    HardwareTest,
    ::testing::Values(TestAgent::Transport::USB_TRANSPORT));

int main(int args, char** argv)
{
    ::testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}
