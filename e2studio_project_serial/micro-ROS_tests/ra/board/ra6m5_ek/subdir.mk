################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/board/ra6m5_ek/board_init.c \
../ra/board/ra6m5_ek/board_leds.c 

OBJS += \
./ra/board/ra6m5_ek/board_init.o \
./ra/board/ra6m5_ek/board_leds.o 

C_DEPS += \
./ra/board/ra6m5_ek/board_init.d \
./ra/board/ra6m5_ek/board_leds.d 


# Each subdirectory must supply rules for building sources it contributes
ra/board/ra6m5_ek/%.o: ../ra/board/ra6m5_ek/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"../src" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/src/r_usb_basic/src/driver/inc" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_gen" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra/fsp/inc/instances" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../src" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -std=c99 -Wall -Werror -Wno-aggregate-return -Wno-unused-result -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


