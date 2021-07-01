################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_agt/r_agt.c 

OBJS += \
./ra/fsp/src/r_agt/r_agt.o 

C_DEPS += \
./ra/fsp/src/r_agt/r_agt.d 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_agt/%.o: ../ra/fsp/src/r_agt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"../src" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/fsp/src/rm_freertos_port" -I"../ra/aws/amazon-freertos/freertos_kernel/include" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/aws" -I"..ra/fsp/src/rm_freertos_plus_tcp" -I"../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/include" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/src" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/fsp/inc" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/fsp/inc/api" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/fsp/inc/instances" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/fsp/src/rm_freertos_port" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/aws/amazon-freertos/freertos_kernel/include" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/fsp/src/rm_freertos_plus_tcp" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/include" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra_gen" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra_cfg/fsp_cfg/bsp" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra_cfg/fsp_cfg" -I"/home/pgarrido/dev/micro-ROS/micro_ros_renesas_testbench/e2studio_project_freeRTOS/ra_cfg/aws" -std=c99 -Wall -Werror -Wno-aggregate-return -Wno-unused-result -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


