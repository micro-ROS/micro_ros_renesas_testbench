#ifndef BOARDS_HPP
#define BOARDS_HPP

#include <algorithm>
#include <string>
#include <vector>

#include "test_agent.hpp"

class Board
{
public:
    Board(std::string device_name, std::string folder, std::string serial_port, std::string usb_port, std::vector<TestAgent::Transport> transports)
        : device_name_(device_name)
        , folder_(folder)
        , serial_port_(serial_port)
        , usb_port_(usb_port)
        , transports_(transports) {}

    Board() {}

    bool check_board_transport(TestAgent::Transport test_transport) {
        return std::find(transports_.begin(), transports_.end(), test_transport) != std::end(transports_);
    };

    std::string device_name_;
    std::string folder_;
    std::string serial_port_;
    std::string usb_port_;
    std::vector<TestAgent::Transport> transports_;
};

extern const std::vector<Board> testbench_boards;

#endif //BOARDS_HPP
