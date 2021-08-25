// Copyright (c) 2021 - for information on the respective copyright owner
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <std_msgs/msg/int64.hpp>
#include <std_msgs/msg/string.hpp>

#include "test.hpp"

class BenchmarkHardwareTest : public HardwareTestBase
{
public:
    std::ofstream log_file;

    BenchmarkHardwareTest(TestAgent::Transport transport)
        : HardwareTestBase(transport)
        {
            log_file.open(BENCHMARK_FILE_NAME, std::ios_base::app);
            log_file << ::testing::UnitTest::GetInstance()->current_test_info()->name() << ": " << transport_ << std::endl;
        }

    ~BenchmarkHardwareTest(){
        log_file.close();
    }
};

class BenchmarkTestAllTransports : public BenchmarkHardwareTest, public ::testing::WithParamInterface<TestAgent::Transport>
{
public:
    BenchmarkTestAllTransports()
        : BenchmarkHardwareTest(GetParam()){}

    ~BenchmarkTestAllTransports(){}
};

class ThroughputTest: public BenchmarkHardwareTest, public ::testing::WithParamInterface<std::tuple<TestAgent::Transport, int>>
{
public:
    ThroughputTest()
        : BenchmarkHardwareTest(std::get<0>(GetParam()))
        , msg_size(std::get<1>(GetParam()))
        {
            addDefineToClient("TOPIC_LEN", std::to_string(msg_size));
        }

    ~ThroughputTest(){}

protected:
  size_t msg_size;
};

TEST_P(ThroughputTest, Throughput)
{
    auto promise = std::make_shared<std::promise<float>>();
    auto future = promise->get_future().share();
    auto read_time = std::chrono::duration<int64_t, std::milli>(5000);
    size_t count = 0;

    std::chrono::steady_clock::time_point begin;

    auto callback = [&](std_msgs::msg::String::SharedPtr /* msg */)
    {
        if (count == 0)
        {
            begin = std::chrono::steady_clock::now();
        }
        else if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin) >= read_time)
        {
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - begin).count();
            float freq = (count*1e9)/duration;
            promise->set_value(freq);
        }

        count++;
    };

    auto qos = rclcpp::SensorDataQoS();
    qos.keep_last(0);

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::String>(
      "test_throughput", qos, callback);

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);

    int rate = (int) future.get();
    log_file << "\tTopic size: " << msg_size << " B" << std::endl;
    log_file << "\tRate: " << rate << " Hz" << std::endl;
    log_file << std::fixed << std::setprecision(2) << "\tThroughput: " << rate * msg_size << " Bps" << std::endl;
}

TEST_P(BenchmarkTestAllTransports, RTT)
{
    auto promise = std::make_shared<std::promise<void>>();
    auto future = promise->get_future().share();

    int64_t client_time = 0, agent_time = 0, total_time = 0, now;

    auto publisher = node->create_publisher<std_msgs::msg::Int64>("test_RTT_sub", 0);

    auto callback = [&](std_msgs::msg::Int64::SharedPtr  msg)
    {
        if (client_time == 0)
        {
            // Get elapsed time
            now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            client_time = now - msg->data;

            // Send response
            auto out_msg = std::make_shared<std_msgs::msg::Int64>();
            publisher->publish(*out_msg);
        }
        else if (agent_time == 0)
        {
            agent_time = msg->data - client_time;
            total_time = msg->data;
            promise->set_value();
        }
    };

    auto qos = rclcpp::SensorDataQoS();
    qos.keep_last(0);

    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_ = node->create_subscription<std_msgs::msg::Int64>(
      "test_RTT_pub", qos, callback);

    ASSERT_EQ(rclcpp::spin_until_future_complete(node, future, default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
    ASSERT_NE(agent_time, 0L);

    log_file << std::fixed << std::setprecision(2) << "\tClient publish time: " << client_time/1e6 << " ms" << std::endl;
    log_file << std::fixed << std::setprecision(2) << "\tAgent publish time: " << agent_time/1e6 << " ms" << std::endl;
    log_file << std::fixed << std::setprecision(2) << "\tRTT: " << total_time/1e6 << " ms" << std::endl;
}

INSTANTIATE_TEST_CASE_P(
    RenesasTest,
    BenchmarkTestAllTransports,
    ::testing::Values(TestAgent::Transport::USB_TRANSPORT, TestAgent::Transport::SERIAL_TRANSPORT, TestAgent::Transport::UDP_THREADX_TRANSPORT, TestAgent::Transport::UDP_FREERTOS_TRANSPORT));

INSTANTIATE_TEST_CASE_P(
    BenchmarkTest,
    ThroughputTest,
        ::testing::Combine(
        ::testing::Values(TestAgent::Transport::USB_TRANSPORT, TestAgent::Transport::SERIAL_TRANSPORT, TestAgent::Transport::UDP_THREADX_TRANSPORT, TestAgent::Transport::UDP_FREERTOS_TRANSPORT),
        ::testing::Values(10, 100, 200, 400)));