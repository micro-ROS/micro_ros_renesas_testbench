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

#include "./test.hpp"

#include <std_msgs/msg/int32.hpp>
#include <std_msgs/msg/float64.hpp>
#include <std_msgs/msg/int64.hpp>
#include <std_msgs/msg/string.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>
#include <sensor_msgs/msg/camera_info.hpp>

#include <rmw/types.h>

using namespace std::chrono_literals;

Board HardwareTestBase::connected_board;

TEST_P(HardwareTestAllTransports, EntityCreation) {
  std::vector<std::string> node_list =
  {
    "/ns_0/test_node_0",
    "/ns_1/test_node_1",
    "/ns_2/test_node_2",
    "/ns_3/test_node_3",
    "/ns_4/test_node_4"
  };

  std::vector<std::string> topic_list =
  {
    "/ns_0/test_pub_0",
    "/ns_1/test_pub_1",
    "/ns_2/test_pub_2",
    "/ns_3/test_pub_3",
    "/ns_4/test_pub_4",
    "/ns_0/test_sub_0",
    "/ns_1/test_sub_1",
    "/ns_2/test_sub_2",
    "/ns_3/test_sub_3",
    "/ns_4/test_sub_4",
    "/ns_0/test_pub_0_extra",
    "/ns_0/test_sub_0_extra"
  };

  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();
  size_t nodes_found = 0;
  size_t topics_found = 0;

  auto timer_found = node->create_wall_timer(std::chrono::milliseconds(200), [&]() {
        nodes_found = check_string_vector(node->get_node_names(), node_list);
        topics_found = check_string_vector(node->get_topic_names_and_types(), topic_list);

        if (nodes_found == node_list.size() && topics_found == topic_list.size())
        {
            promise->set_value();
        }
  });

  rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout);
  ASSERT_EQ(nodes_found, node_list.size()) << "Node creation failed, found " << check_string_vector(node->get_node_names(), node_list, true) << " nodes";
  ASSERT_EQ(topics_found, topic_list.size()) << "Topic creation failed, found " << check_string_vector(node->get_topic_names_and_types(), topic_list, true) << " topics";
}

TEST_P(HardwareTestAllTransports, EntityDestruction) {

  // Look for created nodes
  std::vector<std::string> node_list =
  {
      "/ns_0/test_node_0",
      "/ns_1/test_node_1",
      "/ns_2/test_node_2",
      "/ns_3/test_node_3",
      "/ns_4/test_node_4"
  };

  // Look for created publishers and subscribers
  std::vector<std::string> topic_list =
  {
      "/ns_0/test_pub_0",
      "/ns_1/test_pub_1",
      "/ns_2/test_pub_2",
      "/ns_3/test_pub_3",
      "/ns_4/test_pub_4",
      "/ns_0/test_sub_0",
      "/ns_1/test_sub_1",
      "/ns_2/test_sub_2",
      "/ns_3/test_sub_3",
      "/ns_4/test_sub_4"
  };

  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();
  bool created = false;
  size_t nodes_found = 0;
  size_t topics_found = 0;

  auto publisher = node->create_publisher<std_msgs::msg::Int32>("ns_0/test_subscriber_delete", 10);

  auto timer_found = node->create_wall_timer(std::chrono::milliseconds(200), [&]() {
        nodes_found = check_string_vector(node->get_node_names(), node_list);
        topics_found = check_string_vector(node->get_topic_names_and_types(), topic_list);

        if (!created && nodes_found == node_list.size() && topics_found == topic_list.size())
        {
            promise->set_value();
            created = true;
        }
        else if (created && nodes_found == 0 && topics_found == 0)
        {
            promise->set_value();
        }
  });

  auto timer_notify_destruction= node->create_wall_timer(std::chrono::milliseconds(1000), [&]() {
        if (created)
        {
          // Trigger entity destruction
          auto out_msg = std::make_shared<std_msgs::msg::Int32>();
          publisher->publish(*out_msg);
        }
  });

  std::chrono::duration<int64_t, std::milli> timeout = std::chrono::duration<int64_t, std::milli>(50000);

  ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), timeout), rclcpp::FutureReturnCode::SUCCESS);

  // Check destruction
  promise = std::make_shared<std::promise<void>>();
  future = promise->get_future();
  ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), timeout), rclcpp::FutureReturnCode::SUCCESS);
  ASSERT_EQ(nodes_found, 0U) << "Node destruction failed";
  ASSERT_EQ(topics_found, 0U)  << "Topic destruction failed";
}

TEST_F(HardwareTestOneTransport, EntitiesQoS) {
  std::vector<std::string> topic_list =
  {
    "/test_pub_reliable",
    "/test_pub_best_effort",
    "/test_sub_reliable",
    "/test_sub_best_effort"
  };

  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();
  size_t topics_found = 0;

  auto timer_found = node->create_wall_timer(std::chrono::milliseconds(200), [&]() {
        topics_found = check_string_vector(node->get_topic_names_and_types(), topic_list);

        if (topics_found == topic_list.size())
        {
            promise->set_value();
        }
  });

  // Wait for topics
  ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS)
  << "Topic creation failed, missing " << check_string_vector(node->get_topic_names_and_types(), topic_list, true) << " topics";
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

TEST_P(HardwareTestAllTransports, Publisher) {

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

TEST_P(HardwareTestAllTransports, Subscriber) {
  auto out_msg = std::make_shared<std_msgs::msg::Int32>();
  out_msg->data = 10;

  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();

  auto publisher = node->create_publisher<std_msgs::msg::Int32>("test_sub", 10);
  auto subscription = node->create_subscription<std_msgs::msg::Int32>(
    "test_aux_pub", 10,
    [&](std_msgs::msg::Int32::UniquePtr msg) {
      ASSERT_EQ(msg->data, out_msg->data * 10);
      promise->set_value();
    }
  );

  auto publish_message = [&](){
    std::cout << "Publishing topic" << std::endl;
    publisher->publish(*out_msg);
  };

  auto timer = node->create_wall_timer(1s, publish_message);
  ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
}

#ifndef ROS_DISTRO_FOXY
TEST_P(HardwareTestAllTransports, ComplexSubscriber) {
  if (transport_ == TestAgent::Transport::CAN_TRANSPORT)
  {
      GTEST_SKIP();
  }

  auto out_msg = std::make_shared<sensor_msgs::msg::CameraInfo>();
  out_msg->distortion_model = "string_1";
  out_msg->header.frame_id = "string_2";

  float out_sum = 0;
  for(size_t i = 0; i < 200; i++){
    float data = (float) std::rand() / (float) RAND_MAX;
    out_msg->d.push_back(data);
    out_sum += data;
  }

  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();

  auto publisher = node->create_publisher<sensor_msgs::msg::CameraInfo>("test_sub", 10);
  auto subscription = node->create_subscription<std_msgs::msg::Float64>(
    "test_aux_pub", 10,
    [&](std_msgs::msg::Float64::UniquePtr msg) {
      ASSERT_NEAR(msg->data, out_sum, 0.01);
      promise->set_value();
    }
  );

  auto publish_message = [&](){
    std::cout << "Publishing topic" << std::endl;
    publisher->publish(*out_msg);
  };

  auto timer = node->create_wall_timer(1s, publish_message);
  ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
}
#endif  // !ROS_DISTRO_FOXY

#ifndef ROS_DISTRO_FOXY
TEST_P(HardwareTestAllTransports, CustomTypeIntrospection) {
  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();

  auto subscription = node->create_subscription<sensor_msgs::msg::CameraInfo>(
    "test_pub", 10,
    [&](sensor_msgs::msg::CameraInfo msg) {
      ASSERT_EQ(msg.distortion_model, "string_1");
      ASSERT_EQ(msg.header.frame_id, "string_2");
      ASSERT_EQ(msg.d.size(), 30U);
      for(size_t i = 0; i < msg.d.size(); i++){
        ASSERT_EQ(msg.d[i], static_cast<double>(i));
      }
      promise->set_value();
    }
  );

  ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
}
#endif  // !ROS_DISTRO_FOXY

class ContinousFragment: public HardwareTestBase, public ::testing::WithParamInterface<std::tuple<TestAgent::Transport, int>>
{
public:
    ContinousFragment()
        : HardwareTestBase(std::get<0>(GetParam()), 4)
        , msg_size(std::get<1>(GetParam())) {}

    void configureTest() override {
        addDefineToClient("ARRAY_LEN", std::to_string(msg_size));
    }

    bool isValidTest() override {
        // Check RAM overflow on RA6T2
        return !(0 == connected_board.folder_.compare("MCK_RA6T2") && msg_size > 10000);
    }

protected:
  size_t msg_size;
};

TEST_P(ContinousFragment, PublisherContinousFragment) {
    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future();
    size_t payload_size = 0;

    std::chrono::duration<int64_t, std::milli> timeout = std::chrono::duration<int64_t, std::milli>(msg_size/2);

    auto callback = [&](std_msgs::msg::String::SharedPtr msg)
    {
        payload_size = msg->data.size();
        promise->set_value();
    };

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::String>(
        "test_publisher_fragment", 0, callback);

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), timeout), rclcpp::FutureReturnCode::SUCCESS);
    ASSERT_EQ(payload_size, msg_size-1);
}

TEST_P(HardwareTestAllTransports, TimeSync) {
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

TEST_P(HardwareTestAllTransports, Ping) {
    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future().share();

    auto callback = [&](std_msgs::msg::Int32::SharedPtr /* msg */)
    {
        promise->set_value();
    };

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::Int32>(
      "test_publisher_ping", 0, callback);

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
}

TEST_P(HardwareTestAllTransports, ServiceServer) {
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

TEST_P(HardwareTestAllTransports, ServiceClient) {
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

    auto timeout = std::chrono::duration<int64_t, std::milli>(10000);
    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), timeout), rclcpp::FutureReturnCode::SUCCESS);
    ASSERT_TRUE(received);
}

#ifndef ROS_DISTRO_FOXY
TEST_P(HardwareTestAllTransports, Parameters) {
    auto param_client_node = std::make_shared<rclcpp::Node>("param_aux_client");
    auto parameters_client = std::make_shared<rclcpp::SyncParametersClient>(
        param_client_node,
        "test_node");

    std::vector<std::string> param_names;
    param_names.push_back("param1");
    param_names.push_back("param2");
    param_names.push_back("param3");


    // List parameters multiple times until parameter server is available
    for(size_t i = 0; i < 10; i++)
    {
      rcl_interfaces::msg::ListParametersResult list_params;
      try {
        std::cout << "Listing parameters" << std::endl;
        list_params = parameters_client->list_parameters({}, 10, std::chrono::duration<int64_t, std::milli>(2000));
      } catch(...) {
        continue;
      }
      check_string_vector(list_params.names, param_names, true);
      break;
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
            ASSERT_EQ(event->changed_parameters[0].value.type, rclcpp::ParameterType::PARAMETER_INTEGER);
            ASSERT_EQ(event->changed_parameters[0].value.integer_value, 49);

            on_parameter_calls++;
            promise->set_value();
        });

    // External set double
    new_params.clear();
    new_params.push_back(rclcpp::Parameter("param2", 49));
    result = parameters_client->set_parameters(new_params);
    ASSERT_TRUE(result[0].successful);

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);

    ASSERT_EQ(on_parameter_calls, 1u);
}
#endif  // !ROS_DISTRO_FOXY

class DomainTest : public HardwareTestBase, public ::testing::WithParamInterface<std::tuple<TestAgent::Transport, int>>
{
public:
    DomainTest()
        : HardwareTestBase(std::get<0>(GetParam()), 4, std::get<1>(GetParam())) {}
};

TEST_P(DomainTest, Domain) {
    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future().share();

    auto subscription_ = node->create_subscription<std_msgs::msg::Int32>(
      "test_publisher_domain", 0,
      [&](std_msgs::msg::Int32::SharedPtr /* msg */)
        {
            promise->set_value();
        }
    );

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
}
class PublisherRateTest : public HardwareTestBase, public ::testing::WithParamInterface<std::tuple<TestAgent::Transport, int>>
{
public:
    PublisherRateTest()
        : HardwareTestBase(std::get<0>(GetParam()))
        , expected_freq(std::get<1>(GetParam())) {}

    void configureTest() override {
        addDefineToClient("PUBLISH_PERIOD_MS", std::to_string(1000/expected_freq));
    }

protected:
    int expected_freq;
};

TEST_P(PublisherRateTest, PublisherRate)
{
    if (transport_ == TestAgent::Transport::SERIAL_TRANSPORT && expected_freq == 100)
    {
        GTEST_SKIP();
    }

    auto promise = std::make_shared<std::promise<float>>();
    auto future = promise->get_future().share();
    auto clock = node->get_clock();
    size_t msg_count = 100;
    size_t skip_initial_messages = 50;
    size_t count = 0;

    auto callback = [&](std_msgs::msg::Int32::SharedPtr /* msg */)
    {
        static rclcpp::Time begin;

        if (count == skip_initial_messages)
        {
            begin = clock->now();
        }
        else if(count == msg_count + skip_initial_messages)
        {
            count -= skip_initial_messages;
            auto duration = (clock->now() - begin).nanoseconds();
            float freq = (count*1e9)/duration;
            promise->set_value(freq);
        }

        count++;
    };

    auto qos = rclcpp::SensorDataQoS();
    qos.keep_last(0);

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::Int32>(
      "test_publisher", qos, callback);

    auto timeout = std::chrono::duration<int64_t, std::milli>(1000U*10U*msg_count/expected_freq);
    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, timeout), rclcpp::FutureReturnCode::SUCCESS);
    ASSERT_NEAR(future.get(), expected_freq, expected_freq*0.10);
}

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    PublisherRateTest,
        ::testing::Combine(
        ::testing::Values(
            TestAgent::Transport::CAN_TRANSPORT, 
            TestAgent::Transport::USB_TRANSPORT, 
            TestAgent::Transport::SERIAL_TRANSPORT, 
            TestAgent::Transport::UDP_THREADX_TRANSPORT, 
            TestAgent::Transport::UDP_FREERTOS_TRANSPORT,
            TestAgent::Transport::TCP_FREERTOS_TRANSPORT),
        ::testing::Values(10, 50, 100)));

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    HardwareTestAllTransports,
    ::testing::Values(
        TestAgent::Transport::CAN_TRANSPORT, 
        TestAgent::Transport::USB_TRANSPORT, 
        TestAgent::Transport::SERIAL_TRANSPORT, 
        TestAgent::Transport::UDP_THREADX_TRANSPORT, 
        TestAgent::Transport::UDP_FREERTOS_TRANSPORT,
        TestAgent::Transport::TCP_FREERTOS_TRANSPORT));

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    DomainTest,
        ::testing::Combine(
        ::testing::Values(TestAgent::Transport::SERIAL_TRANSPORT),
        ::testing::Values(10, 24)));

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    ContinousFragment,
        ::testing::Combine(
        ::testing::Values(
            TestAgent::Transport::CAN_TRANSPORT, 
            TestAgent::Transport::USB_TRANSPORT, 
            TestAgent::Transport::SERIAL_TRANSPORT, 
            TestAgent::Transport::UDP_THREADX_TRANSPORT, 
            TestAgent::Transport::UDP_FREERTOS_TRANSPORT,
            TestAgent::Transport::TCP_FREERTOS_TRANSPORT),
        ::testing::Values(4095, 30000, 100000)));

// Profiling tests
TEST_F(HardwareTestMemoryProfiling, SinglePublisherProfiling) {}
TEST_F(HardwareTestMemoryProfiling, MultiplePublisherProfiling) {}

int main(int args, char** argv)
{
    ::testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}
