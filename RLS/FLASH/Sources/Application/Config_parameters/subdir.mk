################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/Config_parameters/config_parameter.c" \

C_SRCS += \
../Sources/Application/Config_parameters/config_parameter.c \

OBJS += \
./Sources/Application/Config_parameters/config_parameter.o \

OBJS_QUOTED += \
"./Sources/Application/Config_parameters/config_parameter.o" \

C_DEPS += \
./Sources/Application/Config_parameters/config_parameter.d \

OBJS_OS_FORMAT += \
./Sources/Application/Config_parameters/config_parameter.o \

C_DEPS_QUOTED += \
"./Sources/Application/Config_parameters/config_parameter.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Config_parameters/config_parameter.o: ../Sources/Application/Config_parameters/config_parameter.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/Config_parameters/config_parameter.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/Config_parameters/config_parameter.o"
	@echo 'Finished building: $<'
	@echo ' '


