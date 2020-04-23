################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/pmc/pmc.c" \

C_SRCS += \
../Sources/Driver/pmc/pmc.c \

OBJS += \
./Sources/Driver/pmc/pmc.o \

OBJS_QUOTED += \
"./Sources/Driver/pmc/pmc.o" \

C_DEPS += \
./Sources/Driver/pmc/pmc.d \

OBJS_OS_FORMAT += \
./Sources/Driver/pmc/pmc.o \

C_DEPS_QUOTED += \
"./Sources/Driver/pmc/pmc.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/pmc/pmc.o: ../Sources/Driver/pmc/pmc.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/pmc/pmc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/pmc/pmc.o"
	@echo 'Finished building: $<'
	@echo ' '


