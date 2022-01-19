################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal_entry.c \
../src/micro_ros_thread_entry.c \
../src/microros_allocators.c \
../src/microros_app.c \
../src/microros_time.c \
../src/wifi_transport_freeRTOS.c 

OBJS += \
./src/hal_entry.o \
./src/micro_ros_thread_entry.o \
./src/microros_allocators.o \
./src/microros_app.o \
./src/microros_time.o \
./src/wifi_transport_freeRTOS.o 

C_DEPS += \
./src/hal_entry.d \
./src/micro_ros_thread_entry.d \
./src/microros_allocators.d \
./src/microros_app.d \
./src/microros_time.d \
./src/wifi_transport_freeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"../src" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/fsp/src/rm_freertos_port" -I"../ra/aws/amazon-freertos/freertos_kernel/include" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/aws" -I"../ra_cfg/arm" -I"../ra/aws/amazon-freertos/libraries/abstractions/wifi/include" -I"../ra/aws/amazon-freertos/libraries/c_sdk/standard/common/include/types" -I"../ra/aws/amazon-freertos/libraries/c_sdk/standard/common/include/private" -I"../ra/aws/amazon-freertos/libraries/c_sdk/standard/common/include" -I"../ra/aws/amazon-freertos/libraries/abstractions/platform/freertos/include" -I"../ra/aws/amazon-freertos/libraries/abstractions/platform/include" -I"../ra/aws/amazon-freertos/libraries/abstractions/secure_sockets/include" -I"../ra/fsp/src/rm_wifi_onchip_silex" -I"../ra_cfg/arm/mbedtls" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


