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

#include <linux/can.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

#include <rclcpp/rclcpp.hpp>
#include "test_agent.hpp"

#include <std_msgs/msg/u_int32_multi_array.hpp>

#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <ctime>

#define ROS_MAX_DOMAIN_ID 101
#define PROFILING_FILE_NAME "profiling_out.txt"
#define BENCHMARK_FILE_NAME "benchmark_out.txt"

using namespace std::chrono_literals;

class HardwareTestBase : public ::testing::Test
{
public:
    HardwareTestBase(TestAgent::Transport transport, uint8_t agent_verbosity = 4, size_t domain_id = 0)
        : transport_(transport)
        , agent_port(8888)
        , agent_dev("")
        , agent_verbosity_(agent_verbosity)
        , default_spin_timeout( std::chrono::duration<int64_t, std::milli>(10000))
    {
        char * cwd_str = get_current_dir_name();
        cwd = std::string(cwd_str);
        free(cwd_str);

        switch (transport_)
        {
            case TestAgent::Transport::UDP_THREADX_TRANSPORT:
                project_name = "e2studio_project_threadX";
                agent.reset(new TestAgent(agent_port, agent_verbosity));
                break;

            case TestAgent::Transport::UDP_FREERTOS_TRANSPORT:
                project_name = "e2studio_project_freeRTOS";
                agent.reset(new TestAgent(agent_port, agent_verbosity));
                break;

            case TestAgent::Transport::USB_TRANSPORT:
                agent_dev = "/dev/serial/by-id/usb-RENESAS_CDC_USB_Demonstration_0000000000001-if00";
                project_name = "e2studio_project_USB";
                agent.reset(new TestAgent(agent_dev, agent_verbosity));
                break;

            case TestAgent::Transport::SERIAL_TRANSPORT:
                agent_dev = "/dev/serial/by-id/usb-Prolific_Technology_Inc._USB-Serial_Controller-if00-port0";
                project_name = "e2studio_project_serial";
                agent.reset(new TestAgent(agent_dev, agent_verbosity));
                break;

            case TestAgent::Transport::CAN_TRANSPORT:
                agent_dev = "can0";
                project_name = "e2studio_project_CAN";
                agent.reset(new TestAgent(transport_, agent_dev, agent_verbosity));
                break;

            default:
                break;
        }

        // Delete content of client config
        client_config_path = cwd + "/src/micro_ros_renesas_testbench/" + project_name + "/src/config.h";
        std::ofstream file(client_config_path, std::ios::out);

        std::string ip_address = TestAgent::getIPAddress();

        size_t sum = 0;
        for(size_t i = 0; i < ip_address.length(); i++){
            sum += ip_address.c_str()[i];
        }

        switch (transport_)
        {
            case TestAgent::Transport::UDP_THREADX_TRANSPORT:
            {
                std::replace(ip_address.begin(), ip_address.end(), '.', ',');
                addDefineToClient("AGENT_IP_ADDRESS", "IP_ADDRESS(" + ip_address+ ")");
                addDefineToClient("AGENT_IP_PORT", std::to_string(agent_port));
                break;
            }

            case TestAgent::Transport::UDP_FREERTOS_TRANSPORT:
            {
                addDefineToClient("AGENT_IP_ADDRESS", "\"" + ip_address + "\"");
                addDefineToClient("AGENT_IP_PORT", std::to_string(agent_port));
                break;
            }
            case TestAgent::Transport::SERIAL_TRANSPORT:
            case TestAgent::Transport::USB_TRANSPORT:
            case TestAgent::Transport::CAN_TRANSPORT:
            default:
                break;
        }

        size_t isolation_domain_id = (size_t)(sum % ROS_MAX_DOMAIN_ID);
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

    bool check_serial_port(std::string port) {
        return access(port.c_str(), W_OK | R_OK ) == 0;
    }

    bool is_interface_up(std::string can_interface) {
        struct ifreq ifr;
        int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
        memset(&ifr, 0, sizeof(ifr));
        strcpy(ifr.ifr_name, can_interface.c_str());
        ioctl(sock, SIOCGIFFLAGS, &ifr);
        close(sock);
        return (ifr.ifr_flags & IFF_UP);
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

        // Check transport interface
        switch (transport_)
        {
            case TestAgent::Transport::SERIAL_TRANSPORT:
            case TestAgent::Transport::USB_TRANSPORT:
                if (!check_serial_port(agent_dev)) {
                    std::cout << transport_ << " serial port not available" << std::endl;
                    GTEST_SKIP();
                }
                break;

            case TestAgent::Transport::CAN_TRANSPORT:
                if (!is_interface_up(agent_dev)) {
                    std::cout << agent_dev << " interface not available" << std::endl;
                    GTEST_SKIP();
                }
                break;

            case TestAgent::Transport::UDP_THREADX_TRANSPORT:
            case TestAgent::Transport::UDP_FREERTOS_TRANSPORT:
            default:
                // Do nothing
                break;
        }

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
    std::string agent_dev;
    uint8_t agent_verbosity_;
    std::chrono::duration<int64_t, std::milli> default_spin_timeout;
};

class HardwareTestAllTransports : public HardwareTestBase, public ::testing::WithParamInterface<TestAgent::Transport>
{
public:
    HardwareTestAllTransports()
        : HardwareTestBase(GetParam()){}

    ~HardwareTestAllTransports(){}
};

class HardwareTestOneTransport : public HardwareTestBase
{
public:
    HardwareTestOneTransport()
        : HardwareTestBase(TestAgent::Transport::USB_TRANSPORT){}

    ~HardwareTestOneTransport(){}
};

class HardwareTestMemoryProfiling : public HardwareTestBase
{
public:
    std::ofstream log_file;

    HardwareTestMemoryProfiling()
        : HardwareTestBase(TestAgent::Transport::UDP_FREERTOS_TRANSPORT)
        {
            addDefineToClient("MICROROS_PROFILING", "1");

            log_file.open(PROFILING_FILE_NAME, std::ios_base::app);
        }

    ~HardwareTestMemoryProfiling(){
        log_file.close();
    }

    void SetUp() override {
        HardwareTestBase::SetUp();

        log_file << ::testing::UnitTest::GetInstance()->current_test_info()->name() << std::endl;

        auto sizes = get_library_size();
        log_file << "\tused static: " << std::to_string(sizes[0]) << " B" << std::endl;
        log_file << "\t.text: " << std::to_string(sizes[1]) << " B" << std::endl;
        log_file << "\t.data: " << std::to_string(sizes[2]) << " B" << std::endl;
        log_file << "\t.bss:  " << std::to_string(sizes[3]) << " B" << std::endl;

        auto board_sizes = get_board_size();
        if (board_sizes.size() == 3){
            log_file << "\tmax stack: "    << std::to_string(board_sizes[0]) << " B" << std::endl;
            log_file << "\tabsolute dyn: " << std::to_string(board_sizes[1]) << " B" << std::endl;
            log_file << "\tdyn: "          << std::to_string(board_sizes[2]) << " B" << std::endl;
        } else {
            log_file << "\tFAILED to retrieve board data" << std::endl;
        }

        log_file << std::endl;

        // Dynamic memory usage should be zero when micro-ROS app ends.
        ASSERT_EQ(board_sizes[2], 0U);
    }

    std::vector<size_t> get_library_size(){
        std::string command = "bash " + cwd + "/src/micro_ros_renesas_testbench/test/micro_ros_renesas_testbench/scripts/size.sh " + project_name;

        std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
        char buffer[128];
        std::string result = "";
        while (!feof(pipe.get())) {
            if (fgets(buffer, 128, pipe.get()) != NULL)
                result += buffer;
        }

        // Vector of string to save tokens
        std::vector<size_t> sizes;
        std::stringstream result_stream(result);
        std::string aux;
        while(getline(result_stream, aux, ' ')){
            sizes.push_back(std::stoi(aux)); // Order: used RAM, .text, .data, .bss
            if (sizes.size() >= 4){
                break;
            }
        }

        return sizes;
    }

    std::vector<size_t> get_board_size(){
        auto promise = std::make_shared<std::promise<void>>();
        auto future = promise->get_future().share();

        std::vector<size_t> out;
        auto subscription = node->create_subscription<std_msgs::msg::UInt32MultiArray>(
            "/profiling_output", 1,
            [&](std_msgs::msg::UInt32MultiArray::UniquePtr msg) {
                ASSERT_EQ(msg->data.size(), 3U);
                out.push_back(msg->data[0]);
                out.push_back(msg->data[1]);
                out.push_back(msg->data[2]);
                promise->set_value();
            }
        );

        std::chrono::duration<int64_t, std::milli> timeout = std::chrono::duration<int64_t, std::milli>(20000);
        rclcpp::spin_until_future_complete(node, future, timeout);

        return(out);
    }
};


#endif //IN_TEST_HPP
