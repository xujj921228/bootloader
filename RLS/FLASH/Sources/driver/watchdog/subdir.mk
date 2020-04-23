################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/watchdog/watchdog.c" \

C_SRCS += \
../Sources/Driver/watchdog/watchdog.c \

OBJS += \
./Sources/Driver/watchdog/watchdog.o \

OBJS_QUOTED += \
"./Sources/Driver/watchdog/watchdog.o" \

C_DEPS += \
./Sources/Driver/watchdog/watchdog.d \

OBJS_OS_FORMAT += \
./Sources/Driver/watchdog/watchdog.o \

C_DEPS_QUOTED += \
"./Sources/Driver/watchdog/watchdog.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/watchdog/watchdog.o: ../Sources/Driver/watchdog/watchdog.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/watchdog/watchdog.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/watchdog/watchdog.o"
	@echo 'Finished building: $<'
	@echo ' '


