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
#include <rmw/types.h>

#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <fstream>

using namespace std::chrono_literals;

// TODO(pablogs): use this for client code naming: https://github.com/google/googletest/blob/master/docs/advanced.md#getting-the-current-tests-name

// TEST_P(HardwareTest, EntityCreation) {
//   runClientCode("EntityCreation");

//   bool timeout, found;
//   std::shared_ptr<std::thread> timeout_thread;

//   // Utilities
//   auto timeout_function = [&](){
//     std::this_thread::sleep_for (std::chrono::seconds(5));
//     timeout = true;
//   };

//   auto check_all_found = [&](std::map<const std::string, bool> & map, bool assert = false) -> bool{
//     for(auto const& it : map){
//       if(!it.second) {
//         if(assert) {
//           EXPECT_TRUE(it.second) << "Element not found: " << it.first;
//         }
//         return false;
//       }
//     }
//     return true;
//   };

//   // Look for created nodes
//   std::map<const std::string, bool> node_map =
//   {
//     {"/test_node_0", false},
//     {"/test_node_1", false},
//     {"/test_node_2", false},
//     {"/test_node_3", false},
//     {"/test_node_4", false},
//   };

//   timeout = false;
//   found = false;
//   timeout_thread.reset(new std::thread(timeout_function));

//   while(!timeout && !found){
//     rclcpp::spin_some(node);
//     auto nodes = node->get_node_names();
//     for(auto node : nodes){
//       if (node_map.find(node) != node_map.end()) {
//           node_map[node] = true;
//       }
//       found = check_all_found(node_map);
//     }
//   }

//   ASSERT_TRUE(check_all_found(node_map, true));
//   timeout_thread->detach();

//   // Look for created publishers and subscribers
//   std::map<const std::string, bool> topics_map =
//   {
//     {"/ns_0/test_pub_0", false},
//     {"/ns_1/test_pub_1", false},
//     {"/ns_2/test_pub_2", false},
//     {"/ns_3/test_pub_3", false},
//     {"/ns_4/test_pub_4", false},
//     {"/ns_0/test_sub_0", false},
//     {"/ns_1/test_sub_1", false},
//     {"/ns_2/test_sub_2", false},
//     {"/ns_3/test_sub_3", false},
//     {"/ns_4/test_sub_4", false},
//     {"/ns_0/test_pub_0_extra", false},
//     {"/ns_0/test_sub_0_extra", false},
//   };

//   timeout = false;
//   found = false;
//   timeout_thread.reset(new std::thread(timeout_function));

//   while(!timeout && !found){
//     rclcpp::spin_some(node);
//     auto topics = node->get_topic_names_and_types();
//     for(auto topic : topics){
//       if (topics_map.find(topic.first) != topics_map.end()) {
//           topics_map[topic.first] = true;
//       }
//       found = check_all_found(topics_map);
//     }
//   }

//   ASSERT_TRUE(check_all_found(topics_map, true));
//   timeout_thread->detach();
// }

// TEST_P(HardwareTest, EntitiesQoS) {
//   runClientCode("EntitiesQoS");

//   bool timeout, found;
//   std::shared_ptr<std::thread> timeout_thread;

//   // Utilities
//   auto timeout_function = [&](){
//     std::this_thread::sleep_for (std::chrono::seconds(5));
//     timeout = true;
//   };

//   auto check_all_found = [&](std::map<const std::string, bool> & map, bool assert = false) -> bool{
//     for(auto const& it : map){
//       if(!it.second) {
//         if(assert) {
//           EXPECT_TRUE(it.second) << "Element not found: " << it.first;
//         }
//         return false;
//       }
//     }
//     return true;
//   };

//   // Wait for topics
//   std::map<const std::string, bool> topics_map =
//   {
//     {"/test_pub_reliable", false},
//     {"/test_pub_best_effort", false},
//     {"/test_sub_reliable", false},
//     {"/test_sub_best_effort", false},
//   };

//   timeout = false;
//   found = false;
//   timeout_thread.reset(new std::thread(timeout_function));

//   while(!timeout && !found){
//     rclcpp::spin_some(node);
//     auto topics = node->get_topic_names_and_types();
//     for(auto topic : topics){
//       if (topics_map.find(topic.first) != topics_map.end()) {
//           topics_map[topic.first] = true;
//       }
//       found = check_all_found(topics_map);
//     }
//   }

//   ASSERT_TRUE(check_all_found(topics_map, true));
//   timeout_thread->detach();

//   std::this_thread::sleep_for(500ms);

//   // Check topics QoS
//   auto pub_reliable = node->get_publishers_info_by_topic("/test_pub_reliable");
//   ASSERT_EQ(pub_reliable.size(), 1U);
//   ASSERT_EQ(pub_reliable[0].topic_type(), "std_msgs/msg/Int32");
//   ASSERT_EQ(pub_reliable[0].qos_profile().get_rmw_qos_profile().reliability, RMW_QOS_POLICY_RELIABILITY_RELIABLE);
//   ASSERT_EQ(pub_reliable[0].qos_profile().get_rmw_qos_profile().history, RMW_QOS_POLICY_HISTORY_UNKNOWN);
//   ASSERT_EQ(pub_reliable[0].qos_profile().get_rmw_qos_profile().durability, RMW_QOS_POLICY_DURABILITY_VOLATILE);

//   auto pub_best_effort = node->get_publishers_info_by_topic("/test_pub_best_effort");
//   ASSERT_EQ(pub_best_effort.size(), 1U);
//   ASSERT_EQ(pub_best_effort[0].topic_type(), "std_msgs/msg/Int32");
//   ASSERT_EQ(pub_best_effort[0].qos_profile().get_rmw_qos_profile().reliability, RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
//   ASSERT_EQ(pub_best_effort[0].qos_profile().get_rmw_qos_profile().history, RMW_QOS_POLICY_HISTORY_UNKNOWN);
//   ASSERT_EQ(pub_best_effort[0].qos_profile().get_rmw_qos_profile().durability, RMW_QOS_POLICY_DURABILITY_VOLATILE);

//   auto sub_reliable = node->get_subscriptions_info_by_topic("/test_sub_reliable");
//   ASSERT_EQ(sub_reliable.size(), 1U);
//   ASSERT_EQ(sub_reliable[0].topic_type(), "std_msgs/msg/Int32");
//   ASSERT_EQ(sub_reliable[0].qos_profile().get_rmw_qos_profile().reliability, RMW_QOS_POLICY_RELIABILITY_RELIABLE);
//   ASSERT_EQ(sub_reliable[0].qos_profile().get_rmw_qos_profile().history, RMW_QOS_POLICY_HISTORY_UNKNOWN);
//   ASSERT_EQ(sub_reliable[0].qos_profile().get_rmw_qos_profile().durability, RMW_QOS_POLICY_DURABILITY_VOLATILE);

//   auto sub_best_effort = node->get_subscriptions_info_by_topic("/test_sub_best_effort");
//   ASSERT_EQ(sub_best_effort.size(), 1U);
//   ASSERT_EQ(sub_best_effort[0].topic_type(), "std_msgs/msg/Int32");
//   ASSERT_EQ(sub_best_effort[0].qos_profile().get_rmw_qos_profile().reliability, RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
//   ASSERT_EQ(sub_best_effort[0].qos_profile().get_rmw_qos_profile().history, RMW_QOS_POLICY_HISTORY_UNKNOWN);
//   ASSERT_EQ(sub_best_effort[0].qos_profile().get_rmw_qos_profile().durability, RMW_QOS_POLICY_DURABILITY_VOLATILE);
// }

// TEST_P(HardwareTest, Publisher) {
//   runClientCode("Publisher");

//   auto promise = std::make_shared<std::promise<void>>();
//   auto future = promise->get_future();

//   auto subscription = node->create_subscription<std_msgs::msg::Int32>(
//     "test_pub", 10,
//     [&](std_msgs::msg::Int32::UniquePtr /* msg */) {
//       promise->set_value();
//     }
//   );

//   rclcpp::spin_until_future_complete(node, future.share());
// }

// TEST_P(HardwareTest, Subscriber) {
//   runClientCode("Subscriber");

//   bool received = false;

//   auto out_msg = std::make_shared<std_msgs::msg::Int32>();
//   out_msg->data = 10;

//   auto promise = std::make_shared<std::promise<void>>();
//   auto future = promise->get_future();

//   auto publisher = node->create_publisher<std_msgs::msg::Int32>("test_sub", 10);
//   auto subscription = node->create_subscription<std_msgs::msg::Int32>(
//     "test_aux_pub", 10,
//     [&](std_msgs::msg::Int32::UniquePtr msg) {
//       ASSERT_EQ(msg->data, out_msg->data * 10);
//       received = true;
//       promise->set_value();
//     }
//   );

//   auto publish_message = [&](){
//     std::cout << "Publishing topic" << std::endl;
//     publisher->publish(*out_msg);
//   };

//   auto timer = node->create_wall_timer(1s, publish_message);
//   rclcpp::spin_until_future_complete(node, future.share());

//   ASSERT_TRUE(received);
// }

// TEST_P(HardwareTest, CustomTypeIntrospection) {
//   ASSERT_TRUE(1);
//   // TODO(pablogs): this test should wait for a custom nested type initted with micro-ROS utilities library
//   // strings
//   // arrays
//   // sequences
// }

// TEST_P(HardwareTest, PublisherContinousFragment) {
//   ASSERT_TRUE(1);
//   // TODO(pablogs): this test should wait for a topic bigger than default MTU*historic
// }

// TEST_P(HardwareTest, TimeSync) {
//   ASSERT_TRUE(1);
//   // TODO(pablogs): this test should wait for a topic with the POSIX time of a synchronized client and check if MCU epoch is ok
// }

// TEST_P(HardwareTest, Ping) {
//   ASSERT_TRUE(1);
//   // TODO(Acuadros95): this test should rely on a publisher that will publish only if ping works ok
// }

// TEST_P(HardwareTest, ServiceServer) {
//   ASSERT_TRUE(1);
//   // TODO(pablogs): this test should prepare a service server and wait for client requests
// }

// TEST_P(HardwareTest, ServiceClient) {
//   ASSERT_TRUE(1);
//   // TODO(pablogs): this test should prepare a service client and send requests to the client
// }

// TEST_P(HardwareTest, Parameters) {
//   ASSERT_TRUE(1);
//   // TODO(pablogs): this test should test the client's parameter server
// }

// TEST_P(HardwareTest, ExecutorRate) {
//   ASSERT_TRUE(1);
//   // TODO(pablogs): this test should check if publication rate is ok when using a executor timer
// }

// TEST_P(HardwareTest, Domain) {
//   ASSERT_TRUE(1);
//   // TODO(pablogs): this test should nodes from different domains are visible
// }

// TEST_P(HardwareTest, Multithread) {
//   ASSERT_TRUE(1);
//   // TODO(pablogs): this test should check if pub/sub/services works from different threads
//   // Rensas hardware have no threads at this moment
// }

class FreqTest : public HardwareTestBase, public ::testing::WithParamInterface<std::tuple<TestAgent::Transport, int>>
{
public:
    FreqTest()
        : HardwareTestBase(std::get<0>(GetParam()))
        , expected_freq(std::get<1>(GetParam()))
        {
            std::string setFreq = "#define PUBLISH_PERIOD_MS " + std::to_string(1000/expected_freq);
            std::filebuf fb;

            configPath = build_path + "/../src/config.h";
            fb.open (configPath, std::ios::out);
            std::ostream confFile(&fb);
            confFile << setFreq << '\n';
        }

    ~FreqTest(){
        remove(configPath.c_str());
    }

protected:
    std::string configPath;
    int expected_freq;
};

TEST_P(FreqTest, PublisherFreq)
{
    // TODO: Add test file for USB/Serial
    std::string filename = "threadx_publish_hz";

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
            runClientCode(filename);
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
        ::testing::Values(TestAgent::Transport::USB_TRANSPORT),
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
