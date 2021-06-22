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

#include <unistd.h>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>
#include <std_msgs/msg/int64.hpp>
#include <std_msgs/msg/string.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>
#include <rmw/types.h>

#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <ctime>

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
          EXPECT_TRUE(it.second) << "Element not found: " << it.first;
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
      if (topics_map.find(topic.first) != topics_map.end()) {
          topics_map[topic.first] = true;
      }
      found = check_all_found(topics_map);
    }
  }

  ASSERT_TRUE(check_all_found(topics_map, true));
  timeout_thread->detach();
}

TEST_P(HardwareTest, EntityDestruction) {
  // TODO(pablogs): this test should ensure that entities can be created and destroyed correctly. It can be done using a service for stoping the micro-ROS execution.
}

TEST_P(HardwareTest, EntitiesQoS) {
  runClientCode("EntitiesQoS");

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
          EXPECT_TRUE(it.second) << "Element not found: " << it.first;
        }
        return false;
      }
    }
    return true;
  };

  // Wait for topics
  std::map<const std::string, bool> topics_map =
  {
    {"/test_pub_reliable", false},
    {"/test_pub_best_effort", false},
    {"/test_sub_reliable", false},
    {"/test_sub_best_effort", false},
  };

  timeout = false;
  found = false;
  timeout_thread.reset(new std::thread(timeout_function));

  while(!timeout && !found){
    rclcpp::spin_some(node);
    auto topics = node->get_topic_names_and_types();
    for(auto topic : topics){
      if (topics_map.find(topic.first) != topics_map.end()) {
          topics_map[topic.first] = true;
      }
      found = check_all_found(topics_map);
    }
  }

  ASSERT_TRUE(check_all_found(topics_map, true));
  timeout_thread->detach();

  std::this_thread::sleep_for(500ms);

  // Check topics QoS
  auto pub_reliable = node->get_publishers_info_by_topic("/test_pub_reliable");
  ASSERT_EQ(pub_reliable.size(), 1U);
  ASSERT_EQ(pub_reliable[0].topic_type(), "std_msgs/msg/Int32");
  ASSERT_EQ(pub_reliable[0].qos_profile().get_rmw_qos_profile().reliability, RMW_QOS_POLICY_RELIABILITY_RELIABLE);
  ASSERT_EQ(pub_reliable[0].qos_profile().get_rmw_qos_profile().history, RMW_QOS_POLICY_HISTORY_UNKNOWN);
  ASSERT_EQ(pub_reliable[0].qos_profile().get_rmw_qos_profile().durability, RMW_QOS_POLICY_DURABILITY_VOLATILE);

  auto pub_best_effort = node->get_publishers_info_by_topic("/test_pub_best_effort");
  ASSERT_EQ(pub_best_effort.size(), 1U);
  ASSERT_EQ(pub_best_effort[0].topic_type(), "std_msgs/msg/Int32");
  ASSERT_EQ(pub_best_effort[0].qos_profile().get_rmw_qos_profile().reliability, RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
  ASSERT_EQ(pub_best_effort[0].qos_profile().get_rmw_qos_profile().history, RMW_QOS_POLICY_HISTORY_UNKNOWN);
  ASSERT_EQ(pub_best_effort[0].qos_profile().get_rmw_qos_profile().durability, RMW_QOS_POLICY_DURABILITY_VOLATILE);

  auto sub_reliable = node->get_subscriptions_info_by_topic("/test_sub_reliable");
  ASSERT_EQ(sub_reliable.size(), 1U);
  ASSERT_EQ(sub_reliable[0].topic_type(), "std_msgs/msg/Int32");
  ASSERT_EQ(sub_reliable[0].qos_profile().get_rmw_qos_profile().reliability, RMW_QOS_POLICY_RELIABILITY_RELIABLE);
  ASSERT_EQ(sub_reliable[0].qos_profile().get_rmw_qos_profile().history, RMW_QOS_POLICY_HISTORY_UNKNOWN);
  ASSERT_EQ(sub_reliable[0].qos_profile().get_rmw_qos_profile().durability, RMW_QOS_POLICY_DURABILITY_VOLATILE);

  auto sub_best_effort = node->get_subscriptions_info_by_topic("/test_sub_best_effort");
  ASSERT_EQ(sub_best_effort.size(), 1U);
  ASSERT_EQ(sub_best_effort[0].topic_type(), "std_msgs/msg/Int32");
  ASSERT_EQ(sub_best_effort[0].qos_profile().get_rmw_qos_profile().reliability, RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
  ASSERT_EQ(sub_best_effort[0].qos_profile().get_rmw_qos_profile().history, RMW_QOS_POLICY_HISTORY_UNKNOWN);
  ASSERT_EQ(sub_best_effort[0].qos_profile().get_rmw_qos_profile().durability, RMW_QOS_POLICY_DURABILITY_VOLATILE);
}

TEST_P(HardwareTest, Publisher) {
  runClientCode("Publisher");

  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();

  auto subscription = node->create_subscription<std_msgs::msg::Int32>(
    "test_pub", 10,
    [&](std_msgs::msg::Int32::UniquePtr /* msg */) {
      promise->set_value();
    }
  );

  ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
}

TEST_P(HardwareTest, Subscriber) {
  runClientCode("Subscriber");

  bool received = false;

  auto out_msg = std::make_shared<std_msgs::msg::Int32>();
  out_msg->data = 10;

  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();

  auto publisher = node->create_publisher<std_msgs::msg::Int32>("test_sub", 10);
  auto subscription = node->create_subscription<std_msgs::msg::Int32>(
    "test_aux_pub", 10,
    [&](std_msgs::msg::Int32::UniquePtr msg) {
      ASSERT_EQ(msg->data, out_msg->data * 10);
      received = true;
      promise->set_value();
    }
  );

  auto publish_message = [&](){
    std::cout << "Publishing topic" << std::endl;
    publisher->publish(*out_msg);
  };

  auto timer = node->create_wall_timer(1s, publish_message);
  ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);

  ASSERT_TRUE(received);
}

#ifdef ROS_DISTRO_GALACTIC
TEST_P(HardwareTest, CustomTypeIntrospection) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should wait for a custom nested type initted with micro-ROS utilities library
  // strings
  // arrays
  // sequences
}
#endif  // ROS_DISTRO_GALACTIC

TEST_P(HardwareTest, PublisherContinousFragment) {
    // TODO: parametrize msg size
    size_t expected_size = 4095;
    runClientCode("PublisherContinousFragment");

    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future();
    size_t payload_size = 0;

    auto callback = [&](std_msgs::msg::String::SharedPtr msg)
    {
        payload_size = msg->data.size();
        promise->set_value();
    };

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::String>(
        "test_publisher_fragment", 0, callback);

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
    ASSERT_EQ(payload_size, expected_size);
}

TEST_P(HardwareTest, TimeSync) {
  runClientCode("TimeSync");

  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();

  size_t received_messages = 0;

  auto subscription = node->create_subscription<std_msgs::msg::Int64>(
    "test_epoch", 10,
    [&](std_msgs::msg::Int64::UniquePtr msg) {
        received_messages++;
        std::time_t time = std::time(nullptr); // Unix epoch in seconds
        ASSERT_NEAR(msg->data, time, 5);

        std::cout << "Client: " << msg->data << " Local: " << time << std::endl;

        if(received_messages > 5){
            promise->set_value();
        }
    }
  );
  ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
}

TEST_P(HardwareTest, Ping) {
    runClientCode("Ping");

    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future().share();

    auto callback = [&](std_msgs::msg::Int32::SharedPtr /* msg */)
    {
        promise->set_value();
    };

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::Int32>(
      "test_publisher_ping", 0, callback);

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, default_spin_timeout), rclcpp::executor::FutureReturnCode::SUCCESS);
}

TEST_P(HardwareTest, ServiceServer) {
    runClientCode("ServiceServer");

    auto client = node->create_client<example_interfaces::srv::AddTwoInts>("test_add_two_ints");

    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = 10;
    request->b = 20;

    std::this_thread::sleep_for (std::chrono::seconds(5));

    ASSERT_TRUE(client->wait_for_service(10s));

    for(size_t i = 0; i < 10; i++){
        request->b += i;

        auto result = client->async_send_request(request);

        ASSERT_EQ(rclcpp::spin_until_future_complete(node, result, default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
        ASSERT_EQ(result.get()->sum, request->a + request->b);
    }
}

TEST_P(HardwareTest, ServiceClient) {
    runClientCode("ServiceClient");

    bool received = false;
    int64_t answer = 0;

    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future();

    auto service = node->create_service<example_interfaces::srv::AddTwoInts>(
        "test_add_two_ints",
        [&] (const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
             std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
            {
                answer = request->a + request->b;
                response->sum = answer;
            }
        );

    auto subscription = node->create_subscription<std_msgs::msg::Int64>(
        "test_aux_pub", 10,
        [&](std_msgs::msg::Int64::UniquePtr msg) {
            ASSERT_EQ(msg->data, answer);
            received = true;
            promise->set_value();
        }
    );

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
    ASSERT_TRUE(received);
}

#ifdef ROS_DISTRO_GALACTIC
TEST_P(HardwareTest, Parameters) {
    runClientCode("Parameters");

    auto param_client_node = std::make_shared<rclcpp::Node>("param_aux_client");
    auto parameters_client = std::make_shared<rclcpp::SyncParametersClient>(
        param_client_node,
        "test_node");

    std::vector<std::string> param_names;
    param_names.push_back("param1");
    param_names.push_back("param2");
    param_names.push_back("param3");

    // TODO use this as previous check
    auto list_params = parameters_client->list_parameters({}, 10);
    ASSERT_EQ(list_params.names.size(), 4u);
    for (auto & name : list_params.names) {
        std::vector<std::string>::iterator it;
        it = std::find(param_names.begin(), param_names.end(), name);
        ASSERT_NE(it, param_names.end());
    }

    bool param_bool_value = parameters_client->get_parameter("param1", false);
    ASSERT_EQ(param_bool_value, true);

    // External set bool
    std::vector<rclcpp::Parameter> new_params = {rclcpp::Parameter("param1", false)};
    auto result = parameters_client->set_parameters(new_params);
    ASSERT_TRUE(result[0].successful);

    // Check set param
    param_bool_value = parameters_client->get_parameter("param1", false);
    ASSERT_EQ(param_bool_value, false);

    // External fail type
    new_params.clear();
    new_params.push_back(rclcpp::Parameter("param1", static_cast<double>(12.2)));
    result = parameters_client->set_parameters(new_params);
    ASSERT_FALSE(result[0].successful);

    // External set int
    new_params.clear();
    new_params.push_back(rclcpp::Parameter("param2", 12));
    result = parameters_client->set_parameters(new_params);
    ASSERT_TRUE(result[0].successful);

    // Check set param
    int param_int_value = parameters_client->get_parameter("param2", 0);
    ASSERT_EQ(param_int_value, 12);

    // External set double
    new_params.clear();
    new_params.push_back(rclcpp::Parameter("param3", 12.12));
    result = parameters_client->set_parameters(new_params);
    ASSERT_TRUE(result[0].successful);

    // Check set param
    double param_double_value = parameters_client->get_parameter("param3", 0.0);
    ASSERT_EQ(param_double_value, 12.12);

    // External get types
    const std::vector<std::string> types_query = {
        "param1",
        "param2",
        "param3"
    };
    auto types = parameters_client->get_parameter_types(types_query);
    ASSERT_EQ(types.size(), 3u);
    ASSERT_EQ(types[0], rclcpp::ParameterType::PARAMETER_BOOL);
    ASSERT_EQ(types[1], rclcpp::ParameterType::PARAMETER_INTEGER);
    ASSERT_EQ(types[2], rclcpp::ParameterType::PARAMETER_DOUBLE);

    // Test callback
    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future();
    size_t on_parameter_calls = 0;
    auto sub = parameters_client->on_parameter_event(
        [&](const rcl_interfaces::msg::ParameterEvent::SharedPtr event) -> void
        {
            ASSERT_EQ(event->changed_parameters.size(), 1u);
            ASSERT_EQ(event->changed_parameters[0].name, "param2");
            ASSERT_EQ(event->changed_parameters[0].value.type, 0);
            ASSERT_EQ(event->changed_parameters[0].value.integer_value, 49);

            on_parameter_calls++;
            promise->set_value();
        });

    rclc_parameter_set_bool(&param_server, "param2", 49);

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);

    ASSERT_EQ(on_parameter_calls, 1u);
}
#endif  // ROS_DISTRO_GALACTIC

class DomainTest : public HardwareTestBase, public ::testing::WithParamInterface<std::tuple<TestAgent::Transport, int>>
{
public:
    DomainTest()
        : HardwareTestBase(std::get<0>(GetParam()), std::get<1>(GetParam()))
        {
          addDefineToClient("DOMAIN_ID", std::to_string(domain_id));
        }
};

TEST_P(DomainTest, Domain) {
    runClientCode("Domain");
    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future().share();

    auto subscription_ = node->create_subscription<std_msgs::msg::Int32>(
      "test_publisher_domain", 0,
      [&](std_msgs::msg::Int32::SharedPtr /* msg */)
        {
            promise->set_value();
        }
    );

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, default_spin_timeout), rclcpp::executor::FutureReturnCode::SUCCESS);
}

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    DomainTest,
        ::testing::Combine(
        ::testing::Values(TestAgent::Transport::UDP_THREADX_TRANSPORT),
        ::testing::Values(10, 24)));

TEST_P(HardwareTest, Multithread) {
  ASSERT_TRUE(1);
  // TODO(pablogs): this test should check if pub/sub/services works from different threads
  // Rensas hardware have no threads at this moment
}

class ExecutorRateTest : public HardwareTestBase, public ::testing::WithParamInterface<std::tuple<TestAgent::Transport, int>>
{
public:
    ExecutorRateTest()
        : HardwareTestBase(std::get<0>(GetParam()))
        , expected_freq(std::get<1>(GetParam()))
        {
          addDefineToClient("PUBLISH_PERIOD_MS", std::to_string(1000/expected_freq));
        }
protected:
    int expected_freq;
};

TEST_P(ExecutorRateTest, ExecutorRate)
{
    runClientCode("ExecutorRate");
    auto promise = std::make_shared<std::promise<float>>();
    auto future = promise->get_future().share();
    auto clock = node->get_clock();
    size_t msg_count = 100;
    size_t count = 0;

    auto callback = [&](std_msgs::msg::Int32::SharedPtr /* msg */)
    {
        static rclcpp::Time begin;

        if (count == 0)
        {
            begin = clock->now();
        }
        else if(count == msg_count)
        {
            auto duration = (clock->now() - begin).nanoseconds();
            float freq = (count*1e9)/duration;
            promise->set_value(freq);
        }

        count++;
    };

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::Int32>(
      "test_publisher", 0, callback);

    auto timeout = std::chrono::duration<int64_t, std::milli>(1000U*10U*msg_count/expected_freq);

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, timeout), rclcpp::executor::FutureReturnCode::SUCCESS);
    ASSERT_NEAR(future.get(), expected_freq, 1.0);
}

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    ExecutorRateTest,
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
