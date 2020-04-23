################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/ftm/ftm.c" \

C_SRCS += \
../Sources/Driver/ftm/ftm.c \

OBJS += \
./Sources/Driver/ftm/ftm.o \

OBJS_QUOTED += \
"./Sources/Driver/ftm/ftm.o" \

C_DEPS += \
./Sources/Driver/ftm/ftm.d \

OBJS_OS_FORMAT += \
./Sources/Driver/ftm/ftm.o \

C_DEPS_QUOTED += \
"./Sources/Driver/ftm/ftm.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/ftm/ftm.o: ../Sources/Driver/ftm/ftm.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/ftm/ftm.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/ftm/ftm.o"
	@echo 'Finished building: $<'
	@echo ' '


