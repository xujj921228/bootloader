################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/Auto_light/auto_light.c" \

C_SRCS += \
../Sources/Application/Auto_light/auto_light.c \

OBJS += \
./Sources/Application/Auto_light/auto_light.o \

OBJS_QUOTED += \
"./Sources/Application/Auto_light/auto_light.o" \

C_DEPS += \
./Sources/Application/Auto_light/auto_light.d \

OBJS_OS_FORMAT += \
./Sources/Application/Auto_light/auto_light.o \

C_DEPS_QUOTED += \
"./Sources/Application/Auto_light/auto_light.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Auto_light/auto_light.o: ../Sources/Application/Auto_light/auto_light.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/Auto_light/auto_light.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/Auto_light/auto_light.o"
	@echo 'Finished building: $<'
	@echo ' '


