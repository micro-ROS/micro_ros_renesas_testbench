################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_ARP.c \
../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_DHCP.c \
../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_DNS.c \
../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_IP.c \
../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_Sockets.c \
../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_Stream_Buffer.c \
../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_TCP_IP.c \
../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_TCP_WIN.c \
../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_UDP_IP.c 

OBJS += \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_ARP.o \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_DHCP.o \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_DNS.o \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_IP.o \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_Sockets.o \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_Stream_Buffer.o \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_TCP_IP.o \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_TCP_WIN.o \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_UDP_IP.o 

C_DEPS += \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_ARP.d \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_DHCP.d \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_DNS.d \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_IP.d \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_Sockets.d \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_Stream_Buffer.d \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_TCP_IP.d \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_TCP_WIN.d \
./ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/FreeRTOS_UDP_IP.d 


# Each subdirectory must supply rules for building sources it contributes
ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/%.o: ../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"../src" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/fsp/src/rm_freertos_port" -I"../ra/aws/amazon-freertos/freertos_kernel/include" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/aws" -I"..ra/fsp/src/rm_freertos_plus_tcp" -I"../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/include" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/src" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/fsp/inc" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/fsp/inc/api" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/fsp/inc/instances" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/fsp/src/rm_freertos_port" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/aws/amazon-freertos/freertos_kernel/include" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/fsp/src/rm_freertos_plus_tcp" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/include" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra_gen" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra_cfg/fsp_cfg/bsp" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra_cfg/fsp_cfg" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra_cfg/aws" -std=c99 -Wall -Werror -Wno-aggregate-return -Wno-unused-result -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


