################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

C_DEPS += \
./utilities/fsl_debug_console.d 

OBJS += \
./utilities/fsl_debug_console.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"/Volumes/Partition 1 - Kiran/Course Work/PES/Assignments/Assignment5/PBKDF2 - Spring23/board" -I"/Volumes/Partition 1 - Kiran/Course Work/PES/Assignments/Assignment5/PBKDF2 - Spring23/source" -I"/Volumes/Partition 1 - Kiran/Course Work/PES/Assignments/Assignment5/PBKDF2 - Spring23" -I"/Volumes/Partition 1 - Kiran/Course Work/PES/Assignments/Assignment5/PBKDF2 - Spring23/drivers" -I"/Volumes/Partition 1 - Kiran/Course Work/PES/Assignments/Assignment5/PBKDF2 - Spring23/CMSIS" -I"/Volumes/Partition 1 - Kiran/Course Work/PES/Assignments/Assignment5/PBKDF2 - Spring23/utilities" -I"/Volumes/Partition 1 - Kiran/Course Work/PES/Assignments/Assignment5/PBKDF2 - Spring23/startup" -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o

.PHONY: clean-utilities

