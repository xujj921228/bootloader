################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/Auto_humid/auto_humid.c" \

C_SRCS += \
../Sources/Application/Auto_humid/auto_humid.c \

OBJS += \
./Sources/Application/Auto_humid/auto_humid.o \

OBJS_QUOTED += \
"./Sources/Application/Auto_humid/auto_humid.o" \

C_DEPS += \
./Sources/Application/Auto_humid/auto_humid.d \

OBJS_OS_FORMAT += \
./Sources/Application/Auto_humid/auto_humid.o \

C_DEPS_QUOTED += \
"./Sources/Application/Auto_humid/auto_humid.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Auto_humid/auto_humid.o: ../Sources/Application/Auto_humid/auto_humid.c
	@echo 'Building file: $<'
	@echo 'Executing target #37 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/Auto_humid/auto_humid.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/Auto_humid/auto_humid.o"
	@echo 'Finished building: $<'
	@echo ' '


