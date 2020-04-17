################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/gpio/gpio.c" \

C_SRCS += \
../Sources/Driver/gpio/gpio.c \

OBJS += \
./Sources/Driver/gpio/gpio.o \

OBJS_QUOTED += \
"./Sources/Driver/gpio/gpio.o" \

C_DEPS += \
./Sources/Driver/gpio/gpio.d \

OBJS_OS_FORMAT += \
./Sources/Driver/gpio/gpio.o \

C_DEPS_QUOTED += \
"./Sources/Driver/gpio/gpio.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/gpio/gpio.o: ../Sources/Driver/gpio/gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/gpio/gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/gpio/gpio.o"
	@echo 'Finished building: $<'
	@echo ' '


