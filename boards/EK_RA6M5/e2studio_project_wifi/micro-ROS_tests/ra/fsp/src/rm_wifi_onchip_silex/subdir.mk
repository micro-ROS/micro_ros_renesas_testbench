################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/rm_wifi_onchip_silex/rm_wifi_api_silex.c \
../ra/fsp/src/rm_wifi_onchip_silex/rm_wifi_onchip_silex.c 

C_DEPS += \
./ra/fsp/src/rm_wifi_onchip_silex/rm_wifi_api_silex.d \
./ra/fsp/src/rm_wifi_onchip_silex/rm_wifi_onchip_silex.d 

OBJS += \
./ra/fsp/src/rm_wifi_onchip_silex/rm_wifi_api_silex.o \
./ra/fsp/src/rm_wifi_onchip_silex/rm_wifi_onchip_silex.o 

SREC += \
microros_testbench.srec 

MAP += \
microros_testbench.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/rm_wifi_onchip_silex/%.o: ../ra/fsp/src/rm_wifi_onchip_silex/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -I"../src" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/fsp/src/rm_freertos_port" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/aws" -I"../ra/fsp/src/rm_wifi_onchip_silex" -I"../ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"../ra/fsp/src/rm_aws_sockets_wrapper_wifi_silex" -I"../ra/aws/FreeRTOS/FreeRTOS-Plus/Source/Utilities/logging" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

