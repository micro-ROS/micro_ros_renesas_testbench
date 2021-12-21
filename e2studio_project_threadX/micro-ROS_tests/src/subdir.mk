################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal_entry.c \
../src/microros_allocators.c \
../src/microros_app.c \
../src/microros_time.c \
../src/thread_microros_entry.c \
../src/udp_transport_threadX.c 

OBJS += \
./src/hal_entry.o \
./src/microros_allocators.o \
./src/microros_app.o \
./src/microros_time.o \
./src/thread_microros_entry.o \
./src/udp_transport_threadX.o 

C_DEPS += \
./src/hal_entry.d \
./src/microros_allocators.d \
./src/microros_app.d \
./src/microros_time.d \
./src/thread_microros_entry.d \
./src/udp_transport_threadX.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"../src" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/fsp/src/rm_threadx_port" -I"../ra/microsoft/azure-rtos/threadx/common/inc" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/fsp_cfg/azure/tx" -I"../ra/fsp/src/rm_netxduo_ether" -I"../ra/microsoft/azure-rtos/netxduo/addons/pop3" -I"../ra/microsoft/azure-rtos/netxduo/addons/snmp" -I"../ra/microsoft/azure-rtos/netxduo/addons/nat" -I"../ra/microsoft/azure-rtos/netxduo/addons/mqtt" -I"../ra/microsoft/azure-rtos/netxduo/addons/ftp" -I"../ra/microsoft/azure-rtos/netxduo/addons/tftp" -I"../ra/microsoft/azure-rtos/netxduo/addons/sntp" -I"../ra/microsoft/azure-rtos/netxduo/addons/smtp" -I"../ra/microsoft/azure-rtos/netxduo/addons/web" -I"../ra/microsoft/azure-rtos/netxduo/addons/auto_ip" -I"../ra/microsoft/azure-rtos/netxduo/addons/telnet" -I"../ra/microsoft/azure-rtos/netxduo/addons/dns" -I"../ra/microsoft/azure-rtos/netxduo/addons/dhcp" -I"../ra/microsoft/azure-rtos/netxduo/addons/http" -I"../ra/microsoft/azure-rtos/netxduo/common/inc" -I"../ra/microsoft/azure-rtos/netxduo/ports/cortex_m4" -I"../ra/microsoft/azure-rtos/netxduo/addons/cloud" -I"../ra_cfg/fsp_cfg/middleware" -I"../ra_cfg/fsp_cfg/azure/nxd" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


