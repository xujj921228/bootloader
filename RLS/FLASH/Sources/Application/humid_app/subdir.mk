################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/humid_app/humid.c" \

C_SRCS += \
../Sources/Application/humid_app/humid.c \

OBJS += \
./Sources/Application/humid_app/humid.o \

OBJS_QUOTED += \
"./Sources/Application/humid_app/humid.o" \

C_DEPS += \
./Sources/Application/humid_app/humid.d \

OBJS_OS_FORMAT += \
./Sources/Application/humid_app/humid.o \

C_DEPS_QUOTED += \
"./Sources/Application/humid_app/humid.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/humid_app/humid.o: ../Sources/Application/humid_app/humid.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/humid_app/humid.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/humid_app/humid.o"
	@echo 'Finished building: $<'
	@echo ' '


