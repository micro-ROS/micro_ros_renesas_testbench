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

using namespace std::chrono_literals;

// TODO(pablogs): All the system calls should be done using a bash script in order to increase flexibility when using with other platforms.

class HardwareTestBase : public ::testing::Test
{
public:
    HardwareTestBase(TestAgent::Transport transport_, size_t domain_id = 0)
        : transport(transport_)
        , options()
        , domain_id(domain_id)
        , default_spin_timeout( std::chrono::duration<int64_t, std::milli>(5000))
    {
        char * cwd_str = get_current_dir_name();
        cwd = std::string(cwd_str);
        free(cwd_str);

        switch (transport)
        {
            case TestAgent::Transport::UDP_THREADX_TRANSPORT:
                build_path = cwd + "/src/micro_ros_renesas_testbench/e2studio_project_threadX/micro-ROS_tests";
                project_main = cwd + "/src/micro_ros_renesas_testbench/e2studio_project_threadX/src/microros_app.c";
                agent_args = "--port 8888";
                break;

            case TestAgent::Transport::UDP_FREERTOS_TRANSPORT:
                build_path = cwd + "/src/micro_ros_renesas_testbench/e2studio_project_freeRTOS/micro-ROS_tests";
                project_main = cwd + "/src/micro_ros_renesas_testbench/e2studio_project_freeRTOS/src/microros_app.c";
                agent_args = "--port 8888";
                break;

            case TestAgent::Transport::SERIAL_TRANSPORT:
            case TestAgent::Transport::USB_TRANSPORT:
                build_path = cwd + "/src/micro_ros_renesas_testbench/e2studio_project/micro-ROS_tests";
                project_main = cwd + "/src/micro_ros_renesas_testbench/e2studio_project/src/microros_app.c";
                agent_args = "--dev /dev/serial/by-id/usb-RENESAS_CDC_USB_Demonstration_0000000000001-if00";
                break;

            default:
                break;
        }
    }

    ~HardwareTestBase(){}

    void SetUp() override {
        ASSERT_TRUE(checkConnection());

        agent.reset(new TestAgent(transport, agent_args, 5));

        if (domain_id != 0)
        {
            rcl_allocator_t allocator = rcl_get_default_allocator();
            rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();

            ASSERT_EQ(rcl_init_options_init(&init_options, allocator), RCL_RET_OK);
            rmw_init_options_t* rmw_options = rcl_init_options_get_rmw_init_options(&init_options);
            rmw_options->domain_id = domain_id;

            options = rclcpp::InitOptions(init_options);
        }

        rclcpp::init(0, NULL, options);
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
        std::cout << "Building client firmware: " << filename << std::endl;
        std::string copy_command = "cp " + cwd  + "/src/micro_ros_renesas_testbench/test/micro_ros_renesas_testbench/client_tests/" + filename + ".c " + project_main;
        bool ret = 0 == system(copy_command.c_str());
        std::string build_command = "cd " + build_path + " && make clean > /dev/null 2>&1 && make -j$(nproc)"; //> /dev/null
        ret &= 0 == system(build_command.c_str());

        return ret;
    }

    bool flashClientCode(){
        std::cout << "Flashing code" << std::endl;
        std::string flash_command = "rfp-cli -device RA -tool jlink -reset -e -p '" + build_path + "/microros_testbench.hex'";
        bool ret = 0 == system(flash_command.c_str());
        return ret;
    }

    void runClientCode(std::string filename){
        ASSERT_TRUE(buildClientCode(filename));
        ASSERT_TRUE(flashClientCode());
        agent->start();
        std::this_thread::sleep_for(3000ms);
    }

protected:
    TestAgent::Transport transport;
    std::shared_ptr<TestAgent> agent;
    std::shared_ptr<rclcpp::Node> node;
    rclcpp::InitOptions options;

    std::string cwd;
    std::string build_path;
    std::string project_main;
    std::string agent_args;

    size_t domain_id;
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
