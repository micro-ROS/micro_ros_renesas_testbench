################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/bsp/mcu/all/bsp_clocks.c \
../ra/fsp/src/bsp/mcu/all/bsp_common.c \
../ra/fsp/src/bsp/mcu/all/bsp_delay.c \
../ra/fsp/src/bsp/mcu/all/bsp_group_irq.c \
../ra/fsp/src/bsp/mcu/all/bsp_guard.c \
../ra/fsp/src/bsp/mcu/all/bsp_io.c \
../ra/fsp/src/bsp/mcu/all/bsp_irq.c \
../ra/fsp/src/bsp/mcu/all/bsp_register_protection.c \
../ra/fsp/src/bsp/mcu/all/bsp_rom_registers.c \
../ra/fsp/src/bsp/mcu/all/bsp_sbrk.c \
../ra/fsp/src/bsp/mcu/all/bsp_security.c 

OBJS += \
./ra/fsp/src/bsp/mcu/all/bsp_clocks.o \
./ra/fsp/src/bsp/mcu/all/bsp_common.o \
./ra/fsp/src/bsp/mcu/all/bsp_delay.o \
./ra/fsp/src/bsp/mcu/all/bsp_group_irq.o \
./ra/fsp/src/bsp/mcu/all/bsp_guard.o \
./ra/fsp/src/bsp/mcu/all/bsp_io.o \
./ra/fsp/src/bsp/mcu/all/bsp_irq.o \
./ra/fsp/src/bsp/mcu/all/bsp_register_protection.o \
./ra/fsp/src/bsp/mcu/all/bsp_rom_registers.o \
./ra/fsp/src/bsp/mcu/all/bsp_sbrk.o \
./ra/fsp/src/bsp/mcu/all/bsp_security.o 

C_DEPS += \
./ra/fsp/src/bsp/mcu/all/bsp_clocks.d \
./ra/fsp/src/bsp/mcu/all/bsp_common.d \
./ra/fsp/src/bsp/mcu/all/bsp_delay.d \
./ra/fsp/src/bsp/mcu/all/bsp_group_irq.d \
./ra/fsp/src/bsp/mcu/all/bsp_guard.d \
./ra/fsp/src/bsp/mcu/all/bsp_io.d \
./ra/fsp/src/bsp/mcu/all/bsp_irq.d \
./ra/fsp/src/bsp/mcu/all/bsp_register_protection.d \
./ra/fsp/src/bsp/mcu/all/bsp_rom_registers.d \
./ra/fsp/src/bsp/mcu/all/bsp_sbrk.d \
./ra/fsp/src/bsp/mcu/all/bsp_security.d 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/bsp/mcu/all/%.o: ../ra/fsp/src/bsp/mcu/all/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"../src" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/fsp/src/rm_threadx_port" -I"../ra/microsoft/azure-rtos/threadx/common/inc" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/fsp_cfg/azure/tx" -I"../ra/fsp/src/rm_netxduo_ether" -I"../ra/microsoft/azure-rtos/netxduo/addons/pop3" -I"../ra/microsoft/azure-rtos/netxduo/addons/snmp" -I"../ra/microsoft/azure-rtos/netxduo/addons/nat" -I"../ra/microsoft/azure-rtos/netxduo/addons/mqtt" -I"../ra/microsoft/azure-rtos/netxduo/addons/ftp" -I"../ra/microsoft/azure-rtos/netxduo/addons/tftp" -I"../ra/microsoft/azure-rtos/netxduo/addons/sntp" -I"../ra/microsoft/azure-rtos/netxduo/addons/smtp" -I"../ra/microsoft/azure-rtos/netxduo/addons/web" -I"../ra/microsoft/azure-rtos/netxduo/addons/auto_ip" -I"../ra/microsoft/azure-rtos/netxduo/addons/telnet" -I"../ra/microsoft/azure-rtos/netxduo/addons/dns" -I"../ra/microsoft/azure-rtos/netxduo/addons/dhcp" -I"../ra/microsoft/azure-rtos/netxduo/addons/http" -I"../ra/microsoft/azure-rtos/netxduo/common/inc" -I"../ra/microsoft/azure-rtos/netxduo/ports/cortex_m4" -I"../ra/microsoft/azure-rtos/netxduo/addons/cloud" -I"../ra_cfg/fsp_cfg/middleware" -I"../ra_cfg/fsp_cfg/azure/nxd" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


