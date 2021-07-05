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
  std::shared_ptr<std::thread> agent_thread_;
  uint16_t port_;
  std::string dev_;
  std::string command_;
};

TestAgent::TestAgent(uint16_t port, uint8_t verbosity = 6)
{
  port_ = port;
  command_ = "ros2 run micro_ros_agent micro_ros_agent udp4 --port " + std::to_string(port_) + " -v" +  std::to_string(verbosity);
}

TestAgent::TestAgent(std::string dev, uint8_t verbosity = 6)
{
  dev_ = dev;
  command_ = "ros2 run micro_ros_agent micro_ros_agent serial --dev " + dev_ + " -v" +  std::to_string(verbosity);
}

TestAgent::TestAgent(Transport transport, std::string args, uint8_t verbosity = 6)
{
  std::string transport_type;

  switch (transport)
  {
      case Transport::UDP_THREADX_TRANSPORT:
      case Transport::UDP_FREERTOS_TRANSPORT:
          transport_type = "udp4";
          break;
      case Transport::SERIAL_TRANSPORT:
      case Transport::USB_TRANSPORT:
          transport_type = "serial";
          break;
      default:
          break;
  }

  command_ = "ros2 run micro_ros_agent micro_ros_agent " + transport_type + " " + args + " -v" +  std::to_string(verbosity);
}

void TestAgent::start()
{
  stop();
  agent_thread_.reset(new std::thread(
    [&]() -> void {
      system(command_.c_str());
    }
  ));
}

void TestAgent::stop()
{
  system("pkill micro_ros_agent");
  if(agent_thread_) {
    agent_thread_->join();
  }
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
