################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/board/ra6m5_ek/board_init.c \
../ra/board/ra6m5_ek/board_leds.c 

C_DEPS += \
./ra/board/ra6m5_ek/board_init.d \
./ra/board/ra6m5_ek/board_leds.d 

OBJS += \
./ra/board/ra6m5_ek/board_init.o \
./ra/board/ra6m5_ek/board_leds.o 

SREC += \
microros_testbench.srec 

MAP += \
microros_testbench.map 


# Each subdirectory must supply rules for building sources it contributes
ra/board/ra6m5_ek/%.o: ../ra/board/ra6m5_ek/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/src" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/micro_ros_renesas2estudio_component/libmicroros/include" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra/fsp/inc" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra/fsp/inc/api" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra/fsp/inc/instances" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra/fsp/src/rm_freertos_port" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra_gen" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra_cfg/fsp_cfg/bsp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra_cfg/fsp_cfg" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra_cfg/aws" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra/fsp/src/rm_wifi_onchip_silex" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra/fsp/src/rm_aws_sockets_wrapper_wifi_silex" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_wifi/ra/aws/FreeRTOS/FreeRTOS-Plus/Source/Utilities/logging" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

