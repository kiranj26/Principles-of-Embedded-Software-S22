################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Accumulate_Line.c \
../source/TSI.c \
../source/cbfifo.c \
../source/i2c.c \
../source/main.c \
../source/mtb.c \
../source/process_command.c \
../source/pwm.c \
../source/rgb_led.c \
../source/semihost_hardfault.c \
../source/sht21.c \
../source/state_machine.c \
../source/sysclock.c \
../source/test_cbfifo.c \
../source/test_sht21.c \
../source/timer.c \
../source/uart.c \
../source/wdt.c 

C_DEPS += \
./source/Accumulate_Line.d \
./source/TSI.d \
./source/cbfifo.d \
./source/i2c.d \
./source/main.d \
./source/mtb.d \
./source/process_command.d \
./source/pwm.d \
./source/rgb_led.d \
./source/semihost_hardfault.d \
./source/sht21.d \
./source/state_machine.d \
./source/sysclock.d \
./source/test_cbfifo.d \
./source/test_sht21.d \
./source/timer.d \
./source/uart.d \
./source/wdt.d 

OBJS += \
./source/Accumulate_Line.o \
./source/TSI.o \
./source/cbfifo.o \
./source/i2c.o \
./source/main.o \
./source/mtb.o \
./source/process_command.o \
./source/pwm.o \
./source/rgb_led.o \
./source/semihost_hardfault.o \
./source/sht21.o \
./source/state_machine.o \
./source/sysclock.o \
./source/test_cbfifo.o \
./source/test_sht21.o \
./source/timer.o \
./source/uart.o \
./source/wdt.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=0 -I"/Users/kiran/Desktop/Pes_Final_Project-main/board" -I"/Users/kiran/Desktop/Pes_Final_Project-main/source" -I"/Users/kiran/Desktop/Pes_Final_Project-main" -I"/Users/kiran/Desktop/Pes_Final_Project-main/drivers" -I"/Users/kiran/Desktop/Pes_Final_Project-main/CMSIS" -I"/Users/kiran/Desktop/Pes_Final_Project-main/utilities" -I"/Users/kiran/Desktop/Pes_Final_Project-main/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Accumulate_Line.d ./source/Accumulate_Line.o ./source/TSI.d ./source/TSI.o ./source/cbfifo.d ./source/cbfifo.o ./source/i2c.d ./source/i2c.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/process_command.d ./source/process_command.o ./source/pwm.d ./source/pwm.o ./source/rgb_led.d ./source/rgb_led.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/sht21.d ./source/sht21.o ./source/state_machine.d ./source/state_machine.o ./source/sysclock.d ./source/sysclock.o ./source/test_cbfifo.d ./source/test_cbfifo.o ./source/test_sht21.d ./source/test_sht21.o ./source/timer.d ./source/timer.o ./source/uart.d ./source/uart.o ./source/wdt.d ./source/wdt.o

.PHONY: clean-source

