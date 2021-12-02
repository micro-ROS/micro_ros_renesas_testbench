################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_canfd/r_canfd.c 

OBJS += \
./ra/fsp/src/r_canfd/r_canfd.o 

C_DEPS += \
./ra/fsp/src/r_canfd/r_canfd.d 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_canfd/%.o: ../ra/fsp/src/r_canfd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"../ra/fsp/inc" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../src" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -std=c99 -Wall -Werror -Wno-aggregate-return -Wno-unused-result -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


