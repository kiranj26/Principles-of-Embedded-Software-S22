################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/PWM_LED_Func.c \
../source/StateMachine.c \
../source/Switch_Interrupt.c \
../source/TSI_Sensor.c \
../source/Timing.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/PWM_LED_Func.d \
./source/StateMachine.d \
./source/Switch_Interrupt.d \
./source/TSI_Sensor.d \
./source/Timing.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/PWM_LED_Func.o \
./source/StateMachine.o \
./source/Switch_Interrupt.o \
./source/TSI_Sensor.o \
./source/Timing.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/board" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/source" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/drivers" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/CMSIS" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/utilities" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/startup" -O0 -fno-common -g -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/PWM_LED_Func.d ./source/PWM_LED_Func.o ./source/StateMachine.d ./source/StateMachine.o ./source/Switch_Interrupt.d ./source/Switch_Interrupt.o ./source/TSI_Sensor.d ./source/TSI_Sensor.o ./source/Timing.d ./source/Timing.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

