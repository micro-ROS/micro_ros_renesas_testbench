################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal_entry.c \
../src/microros_allocators.c \
../src/microros_app.c \
../src/microros_time.c \
../src/microros_transports.c 

OBJS += \
./src/hal_entry.o \
./src/microros_allocators.o \
./src/microros_app.o \
./src/microros_time.o \
./src/microros_transports.o 

C_DEPS += \
./src/hal_entry.d \
./src/microros_allocators.d \
./src/microros_app.d \
./src/microros_time.d \
./src/microros_transports.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"../ra/fsp/inc" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../src" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -std=c99 -Wall -Werror -Wno-aggregate-return -Wno-unused-result -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '

