################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/IIC/iic.c" \

C_SRCS += \
../Sources/Driver/IIC/iic.c \

OBJS += \
./Sources/Driver/IIC/iic.o \

OBJS_QUOTED += \
"./Sources/Driver/IIC/iic.o" \

C_DEPS += \
./Sources/Driver/IIC/iic.d \

OBJS_OS_FORMAT += \
./Sources/Driver/IIC/iic.o \

C_DEPS_QUOTED += \
"./Sources/Driver/IIC/iic.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/IIC/iic.o: ../Sources/Driver/IIC/iic.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/IIC/iic.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/IIC/iic.o"
	@echo 'Finished building: $<'
	@echo ' '

