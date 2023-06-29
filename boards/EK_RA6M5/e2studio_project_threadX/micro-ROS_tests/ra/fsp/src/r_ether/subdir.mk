################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_ether/r_ether.c 

C_DEPS += \
./ra/fsp/src/r_ether/r_ether.d 

OBJS += \
./ra/fsp/src/r_ether/r_ether.o 

SREC += \
microros_testbench.srec 

MAP += \
microros_testbench.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_ether/%.o: ../ra/fsp/src/r_ether/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -I"../src" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra/fsp/src/rm_threadx_port" -I"../ra/microsoft/azure-rtos/threadx/common/inc" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/fsp_cfg/azure/tx" -I"../ra/microsoft/azure-rtos/netxduo/addons/pop3" -I"../ra/microsoft/azure-rtos/netxduo/addons/snmp" -I"../ra/microsoft/azure-rtos/netxduo/addons/nat" -I"../ra/microsoft/azure-rtos/netxduo/addons/mqtt" -I"../ra/microsoft/azure-rtos/netxduo/addons/ftp" -I"../ra/microsoft/azure-rtos/netxduo/addons/tftp" -I"../ra/microsoft/azure-rtos/netxduo/addons/sntp" -I"../ra/microsoft/azure-rtos/netxduo/addons/smtp" -I"../ra/microsoft/azure-rtos/netxduo/addons/web" -I"../ra/microsoft/azure-rtos/netxduo/addons/auto_ip" -I"../ra/microsoft/azure-rtos/netxduo/addons/telnet" -I"../ra/microsoft/azure-rtos/netxduo/addons/dns" -I"../ra/microsoft/azure-rtos/netxduo/addons/dhcp" -I"../ra/microsoft/azure-rtos/netxduo/addons/http" -I"../ra/microsoft/azure-rtos/netxduo/common/inc" -I"../ra/microsoft/azure-rtos/netxduo/ports/cortex_m4" -I"../ra/fsp/src/rm_netxduo_ether" -I"../ra_cfg/fsp_cfg/middleware" -I"../ra_cfg/fsp_cfg/azure/nxd" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/fsp/src/rm_threadx_port" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/threadx/common/inc" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/src" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/fsp/inc" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/fsp/inc/api" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/fsp/inc/instances" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/fsp/src/rm_netxduo_ether" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/pop3" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/snmp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/nat" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/mqtt" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/ftp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/tftp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/sntp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/smtp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/web" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/auto_ip" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/telnet" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/dns" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/dhcp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/http" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/common/inc" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/ports/cortex_m4" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/cloud" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra_gen" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra_cfg/fsp_cfg/bsp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra_cfg/fsp_cfg" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra_cfg/fsp_cfg/middleware" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra_cfg/fsp_cfg/azure/nxd" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_threadX/ra_cfg/fsp_cfg/azure/tx" -std=c99 -Wall -Werror -Wno-aggregate-return -Wno-unused-result -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

