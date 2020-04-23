################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/main.c" \

C_SRCS += \
../Sources/Application/main.c \

OBJS += \
./Sources/Application/main.o \

OBJS_QUOTED += \
"./Sources/Application/main.o" \

C_DEPS += \
./Sources/Application/main.d \

OBJS_OS_FORMAT += \
./Sources/Application/main.o \

C_DEPS_QUOTED += \
"./Sources/Application/main.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/main.o: ../Sources/Application/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/main.o"
	@echo 'Finished building: $<'
	@echo ' '


