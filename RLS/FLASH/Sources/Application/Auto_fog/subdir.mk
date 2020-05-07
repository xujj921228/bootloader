################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/Auto_fog/auto_fog.c" \

C_SRCS += \
../Sources/Application/Auto_fog/auto_fog.c \

OBJS += \
./Sources/Application/Auto_fog/auto_fog.o \

OBJS_QUOTED += \
"./Sources/Application/Auto_fog/auto_fog.o" \

C_DEPS += \
./Sources/Application/Auto_fog/auto_fog.d \

OBJS_OS_FORMAT += \
./Sources/Application/Auto_fog/auto_fog.o \

C_DEPS_QUOTED += \
"./Sources/Application/Auto_fog/auto_fog.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Auto_fog/auto_fog.o: ../Sources/Application/Auto_fog/auto_fog.c
	@echo 'Building file: $<'
	@echo 'Executing target #37 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/Auto_fog/auto_fog.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/Auto_fog/auto_fog.o"
	@echo 'Finished building: $<'
	@echo ' '


