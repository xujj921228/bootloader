################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/driver/ftm/ftm.c" \

C_SRCS += \
../Sources/driver/ftm/ftm.c \

OBJS += \
./Sources/driver/ftm/ftm.o \

OBJS_QUOTED += \
"./Sources/driver/ftm/ftm.o" \

C_DEPS += \
./Sources/driver/ftm/ftm.d \

OBJS_OS_FORMAT += \
./Sources/driver/ftm/ftm.o \

C_DEPS_QUOTED += \
"./Sources/driver/ftm/ftm.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/driver/ftm/ftm.o: ../Sources/driver/ftm/ftm.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/driver/ftm/ftm.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/driver/ftm/ftm.o"
	@echo 'Finished building: $<'
	@echo ' '


