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

#ifndef TEST_AGENT__HPP
#define TEST_AGENT__HPP

#include <gtest/gtest.h>

#include <uxr/agent/transport/serial/TermiosAgentLinux.hpp>
#include <uxr/agent/middleware/utils/Callbacks.hpp>

#include <termios.h>
#include <fcntl.h>

#include <thread>

class TestAgent
{
private:
    std::unique_ptr<eprosima::uxr::TermiosAgent> agent;
    struct termios getAttibutes();

public:
    TestAgent(std::string serial_dev, uint8_t verbosity);
    ~TestAgent(){};

    void start();
    void stop();

    std::unique_ptr<std::thread> agent_thread;
    std::string command;
};

TestAgent::TestAgent(std::string serial_dev, uint8_t verbosity = 6)
{
    command = "ros2 run micro_ros_agent micro_ros_agent serial --dev " + serial_dev + " -v" +  std::to_string(verbosity);
}

void TestAgent::start()
{
    agent_thread.reset(new std::thread(
        [&]() -> void {
            system(command.c_str());
        }
    ));
}


void TestAgent::stop()
{
    system("pkill micro_ros_agent");
    agent_thread->join();
}

#endif //TEST_AGENT__HPP
