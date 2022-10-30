################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../application/main.c 

OBJS += \
./application/main.o 

C_DEPS += \
./application/main.d 


# Each subdirectory must supply rules for building sources it contributes
application/%.o: ../application/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-nuclei-elf-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -mno-save-restore -O0 -ffunction-sections -fdata-sections -fno-common  -g -DDOWNLOAD_MODE=DOWNLOAD_MODE_WORK3 -I"D:\a_liulanqixiazai\SF1_PWM\riscv_project\pwm_demo\sf1_sdk\SoC\anlogic\Board\sf1_eval\Include" -I"D:\a_liulanqixiazai\SF1_PWM\riscv_project\pwm_demo\application\Device" -I"D:\a_liulanqixiazai\SF1_PWM\riscv_project\pwm_demo\application" -I"D:\a_liulanqixiazai\SF1_PWM\riscv_project\pwm_demo\sf1_sdk\NMSIS\Core\Include" -I"D:\a_liulanqixiazai\SF1_PWM\riscv_project\pwm_demo\sf1_sdk\SoC\anlogic\Common\Include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


