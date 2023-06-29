################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/board/ra6t2_mck/board_init.c \
../ra/board/ra6t2_mck/board_leds.c 

C_DEPS += \
./ra/board/ra6t2_mck/board_init.d \
./ra/board/ra6t2_mck/board_leds.d 

OBJS += \
./ra/board/ra6t2_mck/board_init.o \
./ra/board/ra6t2_mck/board_leds.o 

SREC += \
microros_testbench.srec 

MAP += \
microros_testbench.map 


# Each subdirectory must supply rules for building sources it contributes
ra/board/ra6t2_mck/%.o: ../ra/board/ra6t2_mck/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/src" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/micro_ros_renesas2estudio_component/libmicroros/include" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra/fsp/inc" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra/fsp/inc/api" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra/fsp/inc/instances" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra_gen" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra_cfg/fsp_cfg/bsp" -I"/home/username/workspace/Boards/renesas/micro_ros_renesas_testbench/boards/MCK_RA6T2/e2studio_project_CAN/ra_cfg/fsp_cfg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

