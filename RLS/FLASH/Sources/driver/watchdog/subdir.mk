################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/driver/watchdog/watchdog.c" \

C_SRCS += \
../Sources/driver/watchdog/watchdog.c \

OBJS += \
./Sources/driver/watchdog/watchdog.o \

OBJS_QUOTED += \
"./Sources/driver/watchdog/watchdog.o" \

C_DEPS += \
./Sources/driver/watchdog/watchdog.d \

OBJS_OS_FORMAT += \
./Sources/driver/watchdog/watchdog.o \

C_DEPS_QUOTED += \
"./Sources/driver/watchdog/watchdog.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/driver/watchdog/watchdog.o: ../Sources/driver/watchdog/watchdog.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/driver/watchdog/watchdog.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/driver/watchdog/watchdog.o"
	@echo 'Finished building: $<'
	@echo ' '


