################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/Auto_air/auto_air.c" \

C_SRCS += \
../Sources/Application/Auto_air/auto_air.c \

OBJS += \
./Sources/Application/Auto_air/auto_air.o \

OBJS_QUOTED += \
"./Sources/Application/Auto_air/auto_air.o" \

C_DEPS += \
./Sources/Application/Auto_air/auto_air.d \

OBJS_OS_FORMAT += \
./Sources/Application/Auto_air/auto_air.o \

C_DEPS_QUOTED += \
"./Sources/Application/Auto_air/auto_air.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Auto_air/auto_air.o: ../Sources/Application/Auto_air/auto_air.c
	@echo 'Building file: $<'
	@echo 'Executing target #37 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/Auto_air/auto_air.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/Auto_air/auto_air.o"
	@echo 'Finished building: $<'
	@echo ' '


