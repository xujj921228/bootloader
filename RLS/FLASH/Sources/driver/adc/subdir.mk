################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/adc/adc.c" \

C_SRCS += \
../Sources/Driver/adc/adc.c \

OBJS += \
./Sources/Driver/adc/adc.o \

OBJS_QUOTED += \
"./Sources/Driver/adc/adc.o" \

C_DEPS += \
./Sources/Driver/adc/adc.d \

OBJS_OS_FORMAT += \
./Sources/Driver/adc/adc.o \

C_DEPS_QUOTED += \
"./Sources/Driver/adc/adc.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/adc/adc.o: ../Sources/Driver/adc/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/adc/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/adc/adc.o"
	@echo 'Finished building: $<'
	@echo ' '


