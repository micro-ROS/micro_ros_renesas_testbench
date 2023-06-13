#include "boards.hpp"

const std::vector<Board> testbench_boards =
{
    {
        // device_name
        "R7FA6M5BH3CFC",
        // folder
        "EK_RA6M5",
        // serial_port
        "/dev/serial/by-id/usb-Prolific_Technology_Inc._USB-Serial_Controller-if00-port0",
        // usb_port
        "/dev/serial/by-id/usb-RENESAS_CDC_USB_Demonstration_0000000000001-if00",
        // transports
        {
            TestAgent::Transport::CAN_TRANSPORT,
            TestAgent::Transport::USB_TRANSPORT,
            TestAgent::Transport::SERIAL_TRANSPORT,
            TestAgent::Transport::UDP_THREADX_TRANSPORT,
            TestAgent::Transport::UDP_FREERTOS_TRANSPORT,
            TestAgent::Transport::TCP_FREERTOS_TRANSPORT
        },
        // skipped_tests_
        {
        }
    },
    {
        // device_name
        "R7FA6T2BD3CFP",
        // folder
        "MCK_RA6T2",
        // serial_port
        "/dev/serial/by-id/usb-Prolific_Technology_Inc._USB-Serial_Controller-if00-port0",
        // usb_port
        "",
        // transports
        {
            TestAgent::Transport::CAN_TRANSPORT,
            TestAgent::Transport::SERIAL_TRANSPORT
        },
        // skipped_tests_
        {
            "Parameters"
        }
    }
};

void Board::getDevice() {
    char * cwd_str = get_current_dir_name();
    std::string cwd = std::string(cwd_str);
    free(cwd_str);

    std::cout << "Getting device type" << std::endl;
    std::string command = "bash " + cwd + "/src/micro_ros_renesas_testbench/test/micro_ros_renesas_testbench/scripts/get_device.sh";
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    std::string result = "";
    char buffer[128];
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL) {
            // Remove new lines from buffer
            buffer[strcspn(buffer, "\r\n")] = 0;
            result += buffer;
        }
    }

    for(auto device : testbench_boards) {
        if (0 == device.device_name_.compare(result)) {
            device_name_ = device.device_name_;
            folder_ = device.folder_;
            serial_port_ = device.serial_port_;
            usb_port_ = device.usb_port_;
            transports_ = device.transports_;
            skipped_tests_ = device.skipped_tests_;
            break;
        }
    }
}