################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_ether_phy/targets/DP83620/r_ether_phy_target_dp83620.c 

OBJS += \
./ra/fsp/src/r_ether_phy/targets/DP83620/r_ether_phy_target_dp83620.o 

C_DEPS += \
./ra/fsp/src/r_ether_phy/targets/DP83620/r_ether_phy_target_dp83620.d 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_ether_phy/targets/DP83620/%.o: ../ra/fsp/src/r_ether_phy/targets/DP83620/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"../src" -I"../micro_ros_renesas2estudio_component/libmicroros/include" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/fsp/src/rm_freertos_port" -I"../ra/aws/amazon-freertos/freertos_kernel/include" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/aws" -I"..ra/fsp/src/rm_freertos_plus_tcp" -I"../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/include" -I"../src" -I"../ra/fsp/inc" -I"../ra/fsp/inc/api" -I"../ra/fsp/inc/instances" -I"../ra/fsp/src/rm_freertos_port" -I"../ra/aws/amazon-freertos/freertos_kernel/include" -I"../ra/arm/CMSIS_5/CMSIS/Core/Include" -I"../ra/fsp/src/rm_freertos_plus_tcp" -I"../ra/aws/amazon-freertos/libraries/freertos_plus/standard/freertos_plus_tcp/include" -I"../ra_gen" -I"../ra_cfg/fsp_cfg/bsp" -I"../ra_cfg/fsp_cfg" -I"../ra_cfg/aws" -std=c99 -Wall -Werror -Wno-unused-function  -Wno-aggregate-return -Wno-unused-parameter -Wno-format -Wno-address-of-packed-member -Wno-unused-result -Wno-unused-variable -Wno-conversion -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


