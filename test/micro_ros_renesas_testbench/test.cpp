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
  runClientCode("microros_app");

  rclcpp::spin_some(node);
  auto nodes = node->get_node_names();

  ASSERT_GT(nodes.size(), 0U);

  bool found = false;
  for(auto node : nodes){
    // std::cout << node << std::endl;
    // TODO: Set node name for each test
    if (node == "/renesas_node")
    {
      found = true;
    }
  }

  // TODO(pablogs): this test should wait for publishers/subscribers/services

  ASSERT_TRUE(found);
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
    "renesas_publisher", 10,
    [&](std_msgs::msg::Int32::UniquePtr /* msg */) {
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
  // TODO(Acuadros95): this test should rely on a publisher that will publish only if ping works ok
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

class FreqTest : public HardwareTestBase, public ::testing::WithParamInterface<std::tuple<TestAgent::Transport, int>>
{
public:
    FreqTest()
        : HardwareTestBase(std::get<0>(GetParam()))
        , expected_freq(std::get<1>(GetParam()))
        {
            filename = "threadx_publish_" + std::to_string(expected_freq) + "hz";
        }

    ~FreqTest(){}

protected:
    std::string filename;
    int expected_freq;
};

TEST_P(FreqTest, PublisherFreq) 
{
    auto promise = std::make_shared<std::promise<float>>();
    auto future = promise->get_future().share();
    auto clock = node->get_clock();
    size_t msg_count = 100;
    size_t cont = 0;

    auto callback = [&](std_msgs::msg::Int32::SharedPtr /* msg */) 
    {
        static rclcpp::Time begin;
        
        if (cont == 0)
        {
            begin = clock->now();
        }
        else if(cont == msg_count)
        {
            auto duration = (clock->now() - begin).nanoseconds();
            float freq = (cont*1e9)/duration;
            promise->set_value(freq);
        }

        cont++;
    };

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::Int32>(
      "renesas_publisher", 0, callback);

    switch (transport)
    {
        case TestAgent::Transport::UDP_IPV4_TRANSPORT:
        case TestAgent::Transport::UDP_IPV6_TRANSPORT:
            runClientCode(filename);
            break;

        case TestAgent::Transport::SERIAL_TRANSPORT:
        case TestAgent::Transport::USB_TRANSPORT:

            break;
    }

    auto spin_timeout = std::chrono::duration<int64_t, std::milli>((int64_t) (1.5*msg_count*1000/expected_freq)*10);
    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, spin_timeout), rclcpp::executor::FutureReturnCode::SUCCESS);
    ASSERT_NEAR(future.get(), expected_freq, 1.0); 
}

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    FreqTest,
        ::testing::Combine(
        ::testing::Values(TestAgent::Transport::UDP_IPV4_TRANSPORT),
        ::testing::Values(10, 50, 100)));

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    HardwareTest,
    ::testing::Values(TestAgent::Transport::USB_TRANSPORT));

int main(int args, char** argv)
{
    ::testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}
