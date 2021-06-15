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
/*
TEST_F(HardwareTest, EntityCreation) {
  runClientCode("");

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

TEST_P(HardwareTest, Ping) {
    // TODO(pablogs): this test should rely on a publisher that will publish only if ping works ok
    std::string test_file = "threadx_publish_ping.c";
    std::string node_name = "renesas_publisher_ping";

    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future().share();
    
    auto callback = [&](std_msgs::msg::Int32::SharedPtr  msg ) 
    {
        promise->set_value();
    };

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::Int32>(
       node_name, 10, callback);

    switch (transport)
    {
        case Transport::UDP_IPV4_TRANSPORT:
        case Transport::UDP_IPV6_TRANSPORT:
            runClientCode(test_file);
            break;

        case Transport::SERIAL_TRANSPORT:
        case Transport::USB_TRANSPORT:
            // TODO
            break;
    }  
    
    auto spin_timeout = std::chrono::duration<int64_t, std::milli>(5000);
    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, spin_timeout), rclcpp::executor::FutureReturnCode::SUCCESS);
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
*/

TEST_P(HardwareTest, PublisherFreq) 
{
    std::vector<std::pair<std::string, int>> test_cases;

    test_cases.push_back(std::pair<std::string, int>("threadx_publish_10hz", 1));
    //test_cases.push_back(std::pair<std::string, int>("threadx_publish_50hz", 20));
    //test_cases.push_back(std::pair<std::string, int>("threadx_publish_100hz", 200));

    for (auto & element : test_cases)
    {
        auto promise = std::make_shared<std::promise<float>>();
        auto future = promise->get_future().share();
        size_t msg_count = 100;
        size_t cont = 0;
        auto clock = node->get_clock();

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

        float expected_freq = std::get<1>(element);
        auto spin_timeout = std::chrono::duration<int64_t, std::milli>((int64_t) (1.5*msg_count*1000/expected_freq)*10);

        switch (transport)
        {
            case Transport::UDP_IPV4_TRANSPORT:
            case Transport::UDP_IPV6_TRANSPORT:
                runClientCode(std::get<0>(element));
                break;

            case Transport::SERIAL_TRANSPORT:
            case Transport::USB_TRANSPORT:
                // TODO
                break;
        }  

        rclcpp::spin_until_future_complete(node, future, spin_timeout);
        std::cout << "Freq result: " << future.get() << std::endl;
        //ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, spin_timeout), rclcpp::executor::FutureReturnCode::SUCCESS);
        //ASSERT_NEAR(future.get(), expected_freq, 1.0);
    }   
}


int main(int args, char** argv)
{
    ::testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    HardwareTest,
        ::testing::Values(Transport::UDP_IPV4_TRANSPORT));