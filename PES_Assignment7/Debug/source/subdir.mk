################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Assignment-7-Waveforms.c \
../source/audio_input.c \
../source/audio_output.c \
../source/autocorrelate.c \
../source/fp_trip.c \
../source/hardware_init.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/systick.c \
../source/test_sine.c \
../source/tpm.c \
../source/waveform_processing.c 

C_DEPS += \
./source/Assignment-7-Waveforms.d \
./source/audio_input.d \
./source/audio_output.d \
./source/autocorrelate.d \
./source/fp_trip.d \
./source/hardware_init.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/systick.d \
./source/test_sine.d \
./source/tpm.d \
./source/waveform_processing.d 

OBJS += \
./source/Assignment-7-Waveforms.o \
./source/audio_input.o \
./source/audio_output.o \
./source/autocorrelate.o \
./source/fp_trip.o \
./source/hardware_init.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/systick.o \
./source/test_sine.o \
./source/tpm.o \
./source/waveform_processing.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/kiran/Documents/GitHub/assignment-7-waveforms-kiranj26/board" -I"/Users/kiran/Documents/GitHub/assignment-7-waveforms-kiranj26/source" -I"/Users/kiran/Documents/GitHub/assignment-7-waveforms-kiranj26" -I"/Users/kiran/Documents/GitHub/assignment-7-waveforms-kiranj26/drivers" -I"/Users/kiran/Documents/GitHub/assignment-7-waveforms-kiranj26/CMSIS" -I"/Users/kiran/Documents/GitHub/assignment-7-waveforms-kiranj26/utilities" -I"/Users/kiran/Documents/GitHub/assignment-7-waveforms-kiranj26/startup" -O0 -fno-common -g3 -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Assignment-7-Waveforms.d ./source/Assignment-7-Waveforms.o ./source/audio_input.d ./source/audio_input.o ./source/audio_output.d ./source/audio_output.o ./source/autocorrelate.d ./source/autocorrelate.o ./source/fp_trip.d ./source/fp_trip.o ./source/hardware_init.d ./source/hardware_init.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/systick.d ./source/systick.o ./source/test_sine.d ./source/test_sine.o ./source/tpm.d ./source/tpm.o ./source/waveform_processing.d ./source/waveform_processing.o

.PHONY: clean-source

