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

class HardwareTest : public ::testing::TestWithParam<Transport>
{
public:
    HardwareTest()
        : transport(GetParam())
        , cwd("")
        , build_path("")
        , project_main("")
    {        
    }

    ~HardwareTest()
    {}

    void SetUp() override 
    {
        char * cwd_str = get_current_dir_name();
        //cwd = std::string(cwd_str);
        // TODO: fix path
        cwd = "/home/micro_ros_renesas_testbench";
        
        std::cout << cwd << std::endl;
        free(cwd_str);

        switch (transport)
        {
            case Transport::UDP_IPV4_TRANSPORT:
            case Transport::UDP_IPV6_TRANSPORT:
                build_path = cwd + "/e2studio_project_threadX/micro-ROS_tests";
                project_main = cwd + "/e2studio_project_threadX/src/thread_microros_entry.c";
                agent_args = "--port 8888";
                break;

            case Transport::SERIAL_TRANSPORT:
            case Transport::USB_TRANSPORT:
                build_path = cwd + "/e2studio_project/micro-ROS_tests";
                project_main = cwd + "/e2studio_project/src/hal_entry.c";
                agent_args = "--dev /dev/serial/by-id/usb-RENESAS_CDC_USB_Demonstration_0000000000001-if00";
                break;

            default:
                FAIL() << "Transport type not supported";
                break;
        }

        ASSERT_TRUE(checkConnection());
        agent.reset(new TestAgent(transport, agent_args, 0));

        rclcpp::init(0, NULL);
        node = std::make_shared<rclcpp::Node>("test_node");
    }

    void TearDown() override 
    {
        agent->stop();
    }

    bool checkConnection()
    {
        std::cout << "Checking device connection ";
        bool ret = 0 == system("/home/micro_ros_renesas_testbench/utils/renesas_programmer_x86/rfp-cli -device RA -tool jlink -reset > /dev/null 2>&1");
        std::cout << ((ret) ? "OK" : "ERROR") << std::endl;
        return ret;
    }

    bool buildClientCode(std::string filename)
    {
        std::cout << "Building " << filename << std::endl;
        //std::string copy_command = "cp " + cwd  + "/test/micro_ros_renesas_testbench/src/" + filename + ".c " + project_main;
        std::string copy_command = "cp " + cwd  + "/test/micro_ros_renesas_testbench/src/" + filename + ".c " + project_main;
        //bool ret = 0 == system("cd e2studio_project/micro-ROS_tests && mv makefile.init makefile.init.backup");
        bool ret = 0 == system(copy_command.c_str());
        //std::string build_command = "cd " + build_path + " && make clean > /dev/null 2>&1 && make -DPUBLISH_PERIOD_MS=100 -j$(nproc) > /dev/null 2>&1";
        std::string build_command = "cd " + build_path + " && make clean && make  -j$(nproc)";
        ret = 0 == system(build_command.c_str());
        //ret &= 0 == system("cd e2studio_project/micro-ROS_tests && mv makefile.init.backup makefile.init");
        return ret;
    }

    bool flashClientCode()
    {
        std::cout << "Flashing code" << std::endl;
        //bool ret = 0 == system("/home/username/Downloads/renesas/linux-x64/rfp-cli -device RA -tool jlink -reset > /dev/null 2>&1");
        // TODO: delete -noverify-fo flag
        std::string flash_command = "/home/micro_ros_renesas_testbench/utils/renesas_programmer_x86/rfp-cli -device RA -tool jlink -reset -noverify-fo -e -p '" + build_path + "/microros_testbench.hex' > /dev/null 2>&1";
        bool ret = 0 == system(flash_command.c_str());
        return ret;
    }

    void runClientCode(std::string filename)
    {
        //checkConnection();
        ASSERT_TRUE(buildClientCode(filename));
        ASSERT_TRUE(flashClientCode());
        //std::this_thread::sleep_for(500ms);
        agent->start();
        std::this_thread::sleep_for(1000ms);
    }

protected:
    std::unique_ptr<TestAgent> agent;
    std::shared_ptr<rclcpp::Node> node;
    std::string agent_args;
    Transport transport;

    std::string cwd;
    std::string build_path;
    std::string project_main;    
};

#endif //IN_TEST_HPP
