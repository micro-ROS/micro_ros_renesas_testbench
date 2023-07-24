![banner](.images/banner-dark-theme.png#gh-dark-mode-only)
![banner](.images/banner-light-theme.png#gh-light-mode-only)

# micro-ROS Renesas testbench

[![micro-ROS HIL tests](https://github.com/micro-ROS/micro_ros_renesas_testbench/actions/workflows/ci.yml/badge.svg)](https://github.com/micro-ROS/micro_ros_renesas_testbench/actions/workflows/ci.yml)
[![micro-ROS HIL agent](https://github.com/micro-ROS/micro_ros_renesas_testbench/actions/workflows/build_agent.yml/badge.svg)](https://github.com/micro-ROS/micro_ros_renesas_testbench/actions/workflows/build_agent.yml)

This package implements [micro-ROS](https://micro.ros.org/) testing suite as set of Hardware In the Loop test using [Renesas e<sup>2</sup> studio](https://www.renesas.com/us/en/software-tool/e-studio). This components targets [Renesas RA family](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/ra-cortex-m-mcus), an ARM Cortex-M based MCU series, enabling a full micro-ROS compatibility for developing robotics and IoT applications.

## Requirements

This testbench requires the following installed packages (Other compatible toolchain may work):

- [GNU Arm Embedded Toolchain v10.3.1.20210824](https://developer.arm.com/downloads/-/gnu-rm).
- [Renesas Flash Programmer V3.08.02.000](https://www.renesas.com/us/en/software-tool/renesas-flash-programmer-programming-gui).

## License

This repository is open-sourced under the Apache-2.0 license. See the [LICENSE](LICENSE) file for details.

For a list of other open-source components included in this repository,
see the file [3rd-party-licenses.txt](3rd-party-licenses.txt).

## Known Issues/Limitations

There are no known limitations.
