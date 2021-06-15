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

#ifndef TEST_AGENT__HPP
#define TEST_AGENT__HPP

#include <gtest/gtest.h>

#include <chrono>
#include <thread>

enum class Transport
{
    SERIAL_TRANSPORT,
    USB_TRANSPORT,
    UDP_IPV4_TRANSPORT,
    UDP_IPV6_TRANSPORT,
};

class TestAgent
{
public:
  TestAgent(Transport transport, std::string args, uint8_t verbosity);
  ~TestAgent(){};

  void start();
  void stop();

  std::shared_ptr<std::thread> agent_thread;
  std::string command;
};

TestAgent::TestAgent(Transport transport, std::string args, uint8_t verbosity = 6)
{
  std::string transport_type;

  switch (transport)
  {
      case Transport::UDP_IPV4_TRANSPORT:
          transport_type = "udp4";
          break;
      case Transport::UDP_IPV6_TRANSPORT:
          transport_type = "udp6";
          break;
      case Transport::SERIAL_TRANSPORT:
      case Transport::USB_TRANSPORT:
          transport_type = "serial";
          break;
      default:
          break;
  }

  command = "ros2 run micro_ros_agent micro_ros_agent " + transport_type + " " + args + " -v" +  std::to_string(verbosity);
}

void TestAgent::start()
{
  stop();
  agent_thread.reset(new std::thread(
    [&]() -> void {
      system(command.c_str());
    }
  ));
}

void TestAgent::stop()
{
  system("pkill micro_ros_agent");
  if(agent_thread) {
    agent_thread->join();
  }
}

#endif //TEST_AGENT__HPP
