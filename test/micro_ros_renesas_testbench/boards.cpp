#include "boards.hpp"

const std::vector<board> testbench_boards =
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
      TestAgent::Transport::UDP_FREERTOS_TRANSPORT
    }
  },
};