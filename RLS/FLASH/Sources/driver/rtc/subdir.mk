################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/rtc/rtc.c" \

C_SRCS += \
../Sources/Driver/rtc/rtc.c \

OBJS += \
./Sources/Driver/rtc/rtc.o \

OBJS_QUOTED += \
"./Sources/Driver/rtc/rtc.o" \

C_DEPS += \
./Sources/Driver/rtc/rtc.d \

OBJS_OS_FORMAT += \
./Sources/Driver/rtc/rtc.o \

C_DEPS_QUOTED += \
"./Sources/Driver/rtc/rtc.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/rtc/rtc.o: ../Sources/Driver/rtc/rtc.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/rtc/rtc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/rtc/rtc.o"
	@echo 'Finished building: $<'
	@echo ' '


