################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mkl25z4.c 

C_DEPS += \
./startup/startup_mkl25z4.d 

OBJS += \
./startup/startup_mkl25z4.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/board" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/source" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/drivers" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/CMSIS" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/utilities" -I"/Users/kiran/Documents/MCUXpressoIDE_11.7.0_9198/workspace/Assignment4_KiranJojare/startup" -O0 -fno-common -g -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_mkl25z4.d ./startup/startup_mkl25z4.o

.PHONY: clean-startup

