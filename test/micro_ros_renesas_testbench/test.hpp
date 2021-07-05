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

#ifndef IN_TEST_HPP
#define IN_TEST_HPP

#include <gtest/gtest.h>

#include <rclcpp/rclcpp.hpp>
#include "test_agent.hpp"

#include <fstream>

#define ROS_MAX_DOMAIN_ID 101

using namespace std::chrono_literals;

class HardwareTestBase : public ::testing::Test
{
public:
    HardwareTestBase(TestAgent::Transport transport, uint8_t agent_serial_verbosity = 4, size_t domain_id = 0)
        : transport_(transport)
        , agent_port(8888)
        , agent_serial_dev("")
        , agent_serial_verbosity_(agent_serial_verbosity)
        , default_spin_timeout( std::chrono::duration<int64_t, std::milli>(10000))
    {
        char * cwd_str = get_current_dir_name();
        cwd = std::string(cwd_str);
        free(cwd_str);

        switch (transport_)
        {
            case TestAgent::Transport::UDP_THREADX_TRANSPORT:
                project_name = "e2studio_project_threadX";
                agent.reset(new TestAgent(agent_port, agent_serial_verbosity));
                break;

            case TestAgent::Transport::UDP_FREERTOS_TRANSPORT:
                project_name = "e2studio_project_freeRTOS";
                agent.reset(new TestAgent(agent_port, agent_serial_verbosity));
                break;

            case TestAgent::Transport::USB_TRANSPORT:
                agent_serial_dev = "/dev/serial/by-id/usb-RENESAS_CDC_USB_Demonstration_0000000000001-if00";
                project_name = "e2studio_project_USB";
                agent.reset(new TestAgent(agent_serial_dev, agent_serial_verbosity));
                break;

            case TestAgent::Transport::SERIAL_TRANSPORT:
                agent_serial_dev = "/dev/serial/by-id/usb-Prolific_Technology_Inc._USB-Serial_Controller-if00-port0";
                project_name = "e2studio_project_serial";
                agent.reset(new TestAgent(agent_serial_dev, agent_serial_verbosity));
                break;

            default:
                break;
        }

        // Delete content of client config
        client_config_path = cwd + "/src/micro_ros_renesas_testbench/" + project_name + "/src/config.h";
        std::ofstream file(client_config_path, std::ios::out);

        switch (transport_)
        {
            case TestAgent::Transport::UDP_THREADX_TRANSPORT:
            {
                std::string ip_address = TestAgent::getIPAddress();
                std::replace(ip_address.begin(), ip_address.end(), '.', ',');
                addDefineToClient("AGENT_IP_ADDRESS", "IP_ADDRESS(" + ip_address+ ")");
                addDefineToClient("AGENT_IP_PORT", std::to_string(agent_port));
                break;
            }

            case TestAgent::Transport::UDP_FREERTOS_TRANSPORT:
            {
                std::string ip_address = TestAgent::getIPAddress();
                addDefineToClient("AGENT_IP_ADDRESS", "\"" + ip_address + "\"");
                addDefineToClient("AGENT_IP_PORT", std::to_string(agent_port));
                break;
            }
            case TestAgent::Transport::SERIAL_TRANSPORT:
            case TestAgent::Transport::USB_TRANSPORT:
            default:
                break;
        }

        std::srand(std::time(nullptr));
        size_t isolation_domain_id = (size_t)(ROS_MAX_DOMAIN_ID * ((float) std::rand()) / ((float) RAND_MAX));
        domain_id_ = (domain_id + isolation_domain_id) % ROS_MAX_DOMAIN_ID;
        addDefineToClient("DOMAIN_ID", std::to_string(domain_id_));
    }

    ~HardwareTestBase(){}

    void SetUp() override {
        ASSERT_TRUE(checkConnection());

        // Set domain id
        rcl_allocator_t allocator = rcl_get_default_allocator();
        rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();

        ASSERT_EQ(rcl_init_options_init(&init_options, allocator), RCL_RET_OK);
        rmw_init_options_t* rmw_options = rcl_init_options_get_rmw_init_options(&init_options);
        rmw_options->domain_id = domain_id_;

        options = rclcpp::InitOptions(init_options);

        rclcpp::init(0, NULL, options);
        node = std::make_shared<rclcpp::Node>("test_node");

        runClientCode();
    }

    void TearDown() override {
        agent->stop();
        rclcpp::shutdown();
    }

    bool checkConnection(){
        std::cout << "Checking device connection ";
        std::string command = "bash " + cwd + "/src/micro_ros_renesas_testbench/test/micro_ros_renesas_testbench/scripts/check.sh";
        bool ret = 0 == system(command.c_str());
        std::cout << ((ret) ? "OK" : "ERROR") << std::endl;
        return ret;
    }

    bool buildClientCode(){
        // Get test name
        std::string filename;
        std::stringstream testname(::testing::UnitTest::GetInstance()->current_test_info()->name());
        std::getline(testname, filename, '/');

        std::cout << "Building client firmware: " << filename << std::endl;
        std::string command = "bash " + cwd + "/src/micro_ros_renesas_testbench/test/micro_ros_renesas_testbench/scripts/build.sh " + filename + " " + project_name;
        return 0 == system(command.c_str());
    }

    bool flashClientCode(){
        std::string command = "bash " + cwd + "/src/micro_ros_renesas_testbench/test/micro_ros_renesas_testbench/scripts/flash.sh " + project_name;
        return 0 == system(command.c_str());
    }

    void runClientCode(){
        ASSERT_TRUE(buildClientCode());
        ASSERT_TRUE(flashClientCode());
        agent->start();
        std::this_thread::sleep_for(3000ms);
    }

    void addDefineToClient(std::string name, std::string value){
        std::string define_string = "#define " + name + " " + value;

        std::ofstream file(client_config_path, std::ios::app);
        file << define_string << '\n';
    }

    size_t check_string_vector(std::vector<std::string> sample, std::vector<std::string> required, bool assert = false)
    {
        size_t matches = 0;

        for(auto element : required)
        {
            if (std::find(sample.begin(), sample.end(), element) != sample.end())
            {
                matches++;
            }
            else if (assert)
            {
                EXPECT_TRUE(false) << "Element not found: " << element;
            }
        }

        return matches;
    }

    template<typename T>
    size_t check_string_vector(std::map<std::string, T> sample, std::vector<std::string> required, bool assert = false)
    {
        std::vector<std::string> result;
        result.reserve(sample.size());
        std::transform(sample.cbegin(), sample.cend(), std::back_inserter(result),
            [](typename std::map<std::string, T>::const_reference kvpair) {
                return kvpair.first;
            }
        );

        return check_string_vector(result, required, assert);
    }

protected:
    TestAgent::Transport transport_;
    std::shared_ptr<TestAgent> agent;
    std::shared_ptr<rclcpp::Node> node;
    rclcpp::InitOptions options;

    std::string cwd;
    std::string project_name;
    std::string client_config_path;

    size_t domain_id_;
    uint16_t agent_port;
    std::string agent_serial_dev;
    uint8_t agent_serial_verbosity_;
    std::chrono::duration<int64_t, std::milli> default_spin_timeout;
};

class HardwareTest : public HardwareTestBase, public ::testing::WithParamInterface<TestAgent::Transport>
{
public:
    HardwareTest()
        : HardwareTestBase(GetParam()){}

    ~HardwareTest(){}
};

#endif //IN_TEST_HPP
