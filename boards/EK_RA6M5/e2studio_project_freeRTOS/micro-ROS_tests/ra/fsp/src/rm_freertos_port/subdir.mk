################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/rm_freertos_port/port.c 

C_DEPS += \
./ra/fsp/src/rm_freertos_port/port.d 

OBJS += \
./ra/fsp/src/rm_freertos_port/port.o 

SREC += \
microros_testbench.srec 

MAP += \
microros_testbench.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/rm_freertos_port/%.o: ../ra/fsp/src/rm_freertos_port/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -I"../src" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/fsp/src/rm_freertos_port" -I"../ra/aws/amazon-freertos/freertos_kernel/include" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/aws" -I"..ra/fsp/src/rm_freertos_plus_tcp" -I"../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/include" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/src" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra/fsp/inc" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra/fsp/inc/api" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra/fsp/inc/instances" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra/fsp/src/rm_freertos_plus_tcp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra/fsp/src/rm_freertos_port" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra_gen" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra_cfg/fsp_cfg/bsp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra_cfg/fsp_cfg" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra_cfg/aws" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/EK_RA6M5/e2studio_project_freeRTOS/ra/aws/FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-TCP/include" -std=c99 -Wall -Werror -Wno-unused-function  -Wno-aggregate-return -Wno-unused-parameter -Wno-format -Wno-address-of-packed-member -Wno-unused-result -Wno-unused-variable -Wno-conversion -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

