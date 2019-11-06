################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/driver/eeprom/eeprom.c" \

C_SRCS += \
../Sources/driver/eeprom/eeprom.c \

OBJS += \
./Sources/driver/eeprom/eeprom.o \

C_DEPS += \
./Sources/driver/eeprom/eeprom.d \

OBJS_QUOTED += \
"./Sources/driver/eeprom/eeprom.o" \

C_DEPS_QUOTED += \
"./Sources/driver/eeprom/eeprom.d" \

OBJS_OS_FORMAT += \
./Sources/driver/eeprom/eeprom.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/driver/eeprom/eeprom.o: ../Sources/driver/eeprom/eeprom.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/driver/eeprom/eeprom.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/driver/eeprom/eeprom.o"
	@echo 'Finished building: $<'
	@echo ' '


