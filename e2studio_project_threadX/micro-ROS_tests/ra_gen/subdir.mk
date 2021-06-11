################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra_gen/common_data.c \
../ra_gen/hal_data.c \
../ra_gen/main.c \
../ra_gen/pin_data.c \
../ra_gen/thread_microros.c \
../ra_gen/vector_data.c 

OBJS += \
./ra_gen/common_data.o \
./ra_gen/hal_data.o \
./ra_gen/main.o \
./ra_gen/pin_data.o \
./ra_gen/thread_microros.o \
./ra_gen/vector_data.o 

C_DEPS += \
./ra_gen/common_data.d \
./ra_gen/hal_data.d \
./ra_gen/main.d \
./ra_gen/pin_data.d \
./ra_gen/thread_microros.d \
./ra_gen/vector_data.d 


# Each subdirectory must supply rules for building sources it contributes
ra_gen/%.o: ../ra_gen/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"/home/username/workspace/e2_studio/microros_testbench_threadx/src" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/micro_ros_renesas2estudio_component/libmicroros/include" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/fsp/inc" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/fsp/inc/api" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/fsp/inc/instances" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/fsp/src/rm_threadx_port" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/threadx/common/inc" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra_gen" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra_cfg/fsp_cfg/bsp" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra_cfg/fsp_cfg" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra_cfg/fsp_cfg/azure/tx" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/pop3" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/snmp" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/nat" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/mqtt" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/ftp" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/tftp" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/sntp" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/smtp" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/web" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/auto_ip" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/telnet" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/dns" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/dhcp" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/addons/http" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/common/inc" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/microsoft/azure-rtos/netxduo/ports/cortex_m4" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra/fsp/src/rm_netxduo_ether" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra_cfg/fsp_cfg/middleware" -I"/home/username/workspace/e2_studio/microros_testbench_threadx/ra_cfg/fsp_cfg/azure/nxd" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


