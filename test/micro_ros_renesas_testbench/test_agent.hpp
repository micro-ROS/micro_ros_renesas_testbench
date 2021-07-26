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

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include <agent/Agent.hpp>

class TestAgent
{
public:

  enum class Transport
  {
      SERIAL_TRANSPORT,
      USB_TRANSPORT,
      UDP_THREADX_TRANSPORT,
      UDP_FREERTOS_TRANSPORT,
  };

  friend std::ostream& operator<<(std::ostream& os, const Transport& transport) {
    std::string text;
    switch (transport)
    {
        case Transport::UDP_THREADX_TRANSPORT:
          text = "UDP_THREADX_TRANSPORT";
          break;
        case Transport::UDP_FREERTOS_TRANSPORT:
          text = "UDP_FREERTOS_TRANSPORT";
          break;
        case Transport::SERIAL_TRANSPORT:
          text = "SERIAL_TRANSPORT";
          break;
        case Transport::USB_TRANSPORT:
          text = "USB_TRANSPORT";
          break;
        default:
          text = "Unknown transport";
          break;
    }
    return os << text;
  }

  TestAgent(Transport transport, std::string args, uint8_t verbosity);
  TestAgent(uint16_t port, uint8_t verbosity);
  TestAgent(std::string dev, uint8_t verbosity);

  ~TestAgent(){};

  void start();
  void stop();
  static std::string getIPAddress();

private:
  uros::agent::Agent& micro_ros_agent;
  std::vector<const char*> agent_args;
  std::string port_;
  std::string dev_;
  std::string verbosity_;
};

TestAgent::TestAgent(uint16_t port, uint8_t verbosity = 6)
: micro_ros_agent(micro_ros_agent.getInstance())
{
  verbosity_ = "-v" + std::to_string(verbosity);
  port_ = std::to_string(port);

  agent_args.push_back("");
  agent_args.push_back("udp4");
  agent_args.push_back("--port");
  agent_args.push_back(port_.c_str());
  agent_args.push_back(verbosity_.c_str());
}

TestAgent::TestAgent(std::string dev, uint8_t verbosity = 6)
: micro_ros_agent(micro_ros_agent.getInstance())
{
  verbosity_ = "-v" + std::to_string(verbosity);
  dev_ = dev;

  agent_args.push_back("");
  agent_args.push_back("serial");
  agent_args.push_back("--dev");
  agent_args.push_back(dev_.c_str());
  agent_args.push_back(verbosity_.c_str());
}

TestAgent::TestAgent(Transport transport, std::string args, uint8_t verbosity = 6)
: micro_ros_agent(micro_ros_agent.getInstance())
{
  verbosity_ = "-v" + std::to_string(verbosity);
  agent_args.push_back("");
  
  switch (transport)
  {
      case Transport::UDP_THREADX_TRANSPORT:
      case Transport::UDP_FREERTOS_TRANSPORT:
          port_ = args;
          agent_args.push_back("udp4");
          agent_args.push_back("--port");
          agent_args.push_back(port_.c_str());
          break;
      case Transport::SERIAL_TRANSPORT:
      case Transport::USB_TRANSPORT:
          dev_ = args;
          agent_args.push_back("serial");
          agent_args.push_back("--dev");
          agent_args.push_back(dev_.c_str());
          break;
      default:
          break;
  }

  agent_args.push_back(verbosity_.c_str());
}

void TestAgent::start()
{
  micro_ros_agent.create(agent_args.size(), const_cast<char**> (agent_args.data()));
  agent_args.clear();
}

void TestAgent::stop()
{
  micro_ros_agent.stop();
}

std::string TestAgent::getIPAddress(){
    struct ifaddrs * addr_struct=NULL;
    std::string ip_address;

    getifaddrs(&addr_struct);

    for (struct ifaddrs * ifa = addr_struct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IPv4
            void * tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            ip_address = std::string(addressBuffer);
        }
    }
    if (addr_struct!=NULL) freeifaddrs(addr_struct);

    return ip_address;
}

#endif //TEST_AGENT__HPP
