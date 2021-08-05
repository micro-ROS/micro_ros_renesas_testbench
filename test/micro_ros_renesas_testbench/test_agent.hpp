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

#endif //TEST_AGENT__HPP
