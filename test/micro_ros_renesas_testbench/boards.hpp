#include <string>
#include <vector>

#include "test_agent.hpp"

struct board
{
    std::string device_name;
    std::string folder;
    std::string serial_port;
    std::string usb_port;
    std::vector<TestAgent::Transport> transports;
};

extern const std::vector<board> testbench_boards;