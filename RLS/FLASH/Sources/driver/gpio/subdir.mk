################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/driver/gpio/gpio.c" \

C_SRCS += \
../Sources/driver/gpio/gpio.c \

OBJS += \
./Sources/driver/gpio/gpio.o \

OBJS_QUOTED += \
"./Sources/driver/gpio/gpio.o" \

C_DEPS += \
./Sources/driver/gpio/gpio.d \

OBJS_OS_FORMAT += \
./Sources/driver/gpio/gpio.o \

C_DEPS_QUOTED += \
"./Sources/driver/gpio/gpio.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/driver/gpio/gpio.o: ../Sources/driver/gpio/gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/driver/gpio/gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/driver/gpio/gpio.o"
	@echo 'Finished building: $<'
	@echo ' '


