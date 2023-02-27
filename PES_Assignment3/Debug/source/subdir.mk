################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LED_Func.c \
../source/TSI_Sensor.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/LED_Func.d \
./source/TSI_Sensor.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/LED_Func.o \
./source/TSI_Sensor.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment3_Kiran_Final/board" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment3_Kiran_Final/source" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment3_Kiran_Final" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment3_Kiran_Final/drivers" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment3_Kiran_Final/CMSIS" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment3_Kiran_Final/utilities" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment3_Kiran_Final/startup" -O0 -fno-common -g3 -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/LED_Func.d ./source/LED_Func.o ./source/TSI_Sensor.d ./source/TSI_Sensor.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

