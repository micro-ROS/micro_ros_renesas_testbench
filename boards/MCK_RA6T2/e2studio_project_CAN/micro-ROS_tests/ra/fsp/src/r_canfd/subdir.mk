################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_canfd/r_canfd.c 

C_DEPS += \
./ra/fsp/src/r_canfd/r_canfd.d 

OBJS += \
./ra/fsp/src/r_canfd/r_canfd.o 

SREC += \
microros_testbench.srec 

MAP += \
microros_testbench.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_canfd/%.o: ../ra/fsp/src/r_canfd/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -D_RA_ORDINAL=1 -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/src" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/micro_ros_renesas2estudio_component/libmicroros/include" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra/fsp/inc" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra/fsp/inc/api" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra/fsp/inc/instances" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra_gen" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra_cfg/fsp_cfg/bsp" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra_cfg/fsp_cfg" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra/arm/CMSIS_6/CMSIS/Core/Include" -I"." -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

