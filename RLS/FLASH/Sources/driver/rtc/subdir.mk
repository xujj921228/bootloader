################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/driver/rtc/rtc.c" \

C_SRCS += \
../Sources/driver/rtc/rtc.c \

OBJS += \
./Sources/driver/rtc/rtc.o \

OBJS_QUOTED += \
"./Sources/driver/rtc/rtc.o" \

C_DEPS += \
./Sources/driver/rtc/rtc.d \

OBJS_OS_FORMAT += \
./Sources/driver/rtc/rtc.o \

C_DEPS_QUOTED += \
"./Sources/driver/rtc/rtc.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/driver/rtc/rtc.o: ../Sources/driver/rtc/rtc.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/driver/rtc/rtc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/driver/rtc/rtc.o"
	@echo 'Finished building: $<'
	@echo ' '


