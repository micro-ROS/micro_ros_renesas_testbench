################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/rm_threadx_port/tx_iar.c \
../ra/fsp/src/rm_threadx_port/tx_initialize_low_level.c \
../ra/fsp/src/rm_threadx_port/tx_isr_end.c \
../ra/fsp/src/rm_threadx_port/tx_isr_start.c \
../ra/fsp/src/rm_threadx_port/tx_port_wait_thread_ready.c \
../ra/fsp/src/rm_threadx_port/tx_thread_interrupt_control.c \
../ra/fsp/src/rm_threadx_port/tx_thread_interrupt_disable.c \
../ra/fsp/src/rm_threadx_port/tx_thread_interrupt_restore.c \
../ra/fsp/src/rm_threadx_port/tx_thread_schedule.c \
../ra/fsp/src/rm_threadx_port/tx_thread_secure_stack_allocate.c \
../ra/fsp/src/rm_threadx_port/tx_thread_secure_stack_free.c \
../ra/fsp/src/rm_threadx_port/tx_thread_stack_build.c \
../ra/fsp/src/rm_threadx_port/tx_thread_system_return.c \
../ra/fsp/src/rm_threadx_port/tx_timer_interrupt.c \
../ra/fsp/src/rm_threadx_port/txe_thread_secure_stack_allocate.c \
../ra/fsp/src/rm_threadx_port/txe_thread_secure_stack_free.c 

OBJS += \
./ra/fsp/src/rm_threadx_port/tx_iar.o \
./ra/fsp/src/rm_threadx_port/tx_initialize_low_level.o \
./ra/fsp/src/rm_threadx_port/tx_isr_end.o \
./ra/fsp/src/rm_threadx_port/tx_isr_start.o \
./ra/fsp/src/rm_threadx_port/tx_port_wait_thread_ready.o \
./ra/fsp/src/rm_threadx_port/tx_thread_interrupt_control.o \
./ra/fsp/src/rm_threadx_port/tx_thread_interrupt_disable.o \
./ra/fsp/src/rm_threadx_port/tx_thread_interrupt_restore.o \
./ra/fsp/src/rm_threadx_port/tx_thread_schedule.o \
./ra/fsp/src/rm_threadx_port/tx_thread_secure_stack_allocate.o \
./ra/fsp/src/rm_threadx_port/tx_thread_secure_stack_free.o \
./ra/fsp/src/rm_threadx_port/tx_thread_stack_build.o \
./ra/fsp/src/rm_threadx_port/tx_thread_system_return.o \
./ra/fsp/src/rm_threadx_port/tx_timer_interrupt.o \
./ra/fsp/src/rm_threadx_port/txe_thread_secure_stack_allocate.o \
./ra/fsp/src/rm_threadx_port/txe_thread_secure_stack_free.o 

C_DEPS += \
./ra/fsp/src/rm_threadx_port/tx_iar.d \
./ra/fsp/src/rm_threadx_port/tx_initialize_low_level.d \
./ra/fsp/src/rm_threadx_port/tx_isr_end.d \
./ra/fsp/src/rm_threadx_port/tx_isr_start.d \
./ra/fsp/src/rm_threadx_port/tx_port_wait_thread_ready.d \
./ra/fsp/src/rm_threadx_port/tx_thread_interrupt_control.d \
./ra/fsp/src/rm_threadx_port/tx_thread_interrupt_disable.d \
./ra/fsp/src/rm_threadx_port/tx_thread_interrupt_restore.d \
./ra/fsp/src/rm_threadx_port/tx_thread_schedule.d \
./ra/fsp/src/rm_threadx_port/tx_thread_secure_stack_allocate.d \
./ra/fsp/src/rm_threadx_port/tx_thread_secure_stack_free.d \
./ra/fsp/src/rm_threadx_port/tx_thread_stack_build.d \
./ra/fsp/src/rm_threadx_port/tx_thread_system_return.d \
./ra/fsp/src/rm_threadx_port/tx_timer_interrupt.d \
./ra/fsp/src/rm_threadx_port/txe_thread_secure_stack_allocate.d \
./ra/fsp/src/rm_threadx_port/txe_thread_secure_stack_free.d 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/rm_threadx_port/%.o: ../ra/fsp/src/rm_threadx_port/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/src" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/micro_ros_renesas2estudio_component/libmicroros/include" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/fsp/inc" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/fsp/inc/api" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/fsp/inc/instances" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/fsp/src/rm_threadx_port" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/threadx/common/inc" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra_gen" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra_cfg/fsp_cfg/bsp" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra_cfg/fsp_cfg" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra_cfg/fsp_cfg/azure/tx" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/pop3" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/snmp" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/nat" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/mqtt" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/ftp" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/tftp" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/sntp" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/smtp" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/web" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/auto_ip" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/telnet" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/dns" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/dhcp" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/addons/http" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/common/inc" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/microsoft/azure-rtos/netxduo/ports/cortex_m4" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra/fsp/src/rm_netxduo_ether" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra_cfg/fsp_cfg/middleware" -I"/home/micro_ros_renesas_testbench/e2studio_project_threadX/ra_cfg/fsp_cfg/azure/nxd" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '

