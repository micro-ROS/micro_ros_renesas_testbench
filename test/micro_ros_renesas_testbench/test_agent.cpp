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

#include "test_agent.hpp"

TestAgent::TestAgent(Transport transport, uint16_t port, uint8_t verbosity = 6)
{
  std::string transport_type = "";
  switch (transport)
  {
      case Transport::TCP_FREERTOS_TRANSPORT:
          transport_type = "tcp4";
          break;
      case Transport::UDP_THREADX_TRANSPORT:
      case Transport::UDP_FREERTOS_TRANSPORT:
          transport_type = "udp4";
          break;
      default:
          break;
  }

  port_ = port;
  command_ = "ros2 run micro_ros_agent micro_ros_agent " + transport_type + " --port " + std::to_string(port_) + " -v" +  std::to_string(verbosity);
}

TestAgent::TestAgent(std::string dev, uint8_t verbosity = 6)
{
  dev_ = dev;
  command_ = "ros2 run micro_ros_agent micro_ros_agent serial --dev " + dev_ + " -v" +  std::to_string(verbosity);
}

TestAgent::TestAgent(Transport transport, std::string args, uint8_t verbosity = 6)
{
  std::string transport_type = "";
  std::string aux_args = "";

  switch (transport)
  {
      case Transport::TCP_FREERTOS_TRANSPORT:
          transport_type = "tcp4";
          aux_args = "--port " + args;
          break;
      case Transport::UDP_THREADX_TRANSPORT:
      case Transport::UDP_FREERTOS_TRANSPORT:
          transport_type = "udp4";
          aux_args = "--port " + args;
          break;
      case Transport::SERIAL_TRANSPORT:
      case Transport::USB_TRANSPORT:
          transport_type = "serial";
          aux_args = "--dev " + args;
          break;
      case Transport::CAN_TRANSPORT:
          transport_type = "canfd";
          aux_args = "--dev " + args;
          break;
      default:
          break;
  }

  command_ = "ros2 run micro_ros_agent micro_ros_agent " + transport_type + " " + aux_args + " -v" +  std::to_string(verbosity);
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