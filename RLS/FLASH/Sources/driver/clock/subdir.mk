################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/clock/clock.c" \

C_SRCS += \
../Sources/Driver/clock/clock.c \

OBJS += \
./Sources/Driver/clock/clock.o \

OBJS_QUOTED += \
"./Sources/Driver/clock/clock.o" \

C_DEPS += \
./Sources/Driver/clock/clock.d \

OBJS_OS_FORMAT += \
./Sources/Driver/clock/clock.o \

C_DEPS_QUOTED += \
"./Sources/Driver/clock/clock.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/clock/clock.o: ../Sources/Driver/clock/clock.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/clock/clock.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/clock/clock.o"
	@echo 'Finished building: $<'
	@echo ' '


