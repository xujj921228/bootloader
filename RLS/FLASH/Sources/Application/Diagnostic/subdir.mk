################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/Diagnostic/lin_diagnostic_service.c" \

C_SRCS += \
../Sources/Application/Diagnostic/lin_diagnostic_service.c \

OBJS += \
./Sources/Application/Diagnostic/lin_diagnostic_service.o \

OBJS_QUOTED += \
"./Sources/Application/Diagnostic/lin_diagnostic_service.o" \

C_DEPS += \
./Sources/Application/Diagnostic/lin_diagnostic_service.d \

OBJS_OS_FORMAT += \
./Sources/Application/Diagnostic/lin_diagnostic_service.o \

C_DEPS_QUOTED += \
"./Sources/Application/Diagnostic/lin_diagnostic_service.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Diagnostic/lin_diagnostic_service.o: ../Sources/Application/Diagnostic/lin_diagnostic_service.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/Diagnostic/lin_diagnostic_service.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/Diagnostic/lin_diagnostic_service.o"
	@echo 'Finished building: $<'
	@echo ' '


