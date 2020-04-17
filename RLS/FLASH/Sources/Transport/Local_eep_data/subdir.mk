################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Transport/Local_eep_data/local_eep_data.c" \

C_SRCS += \
../Sources/Transport/Local_eep_data/local_eep_data.c \

OBJS += \
./Sources/Transport/Local_eep_data/local_eep_data.o \

OBJS_QUOTED += \
"./Sources/Transport/Local_eep_data/local_eep_data.o" \

C_DEPS += \
./Sources/Transport/Local_eep_data/local_eep_data.d \

OBJS_OS_FORMAT += \
./Sources/Transport/Local_eep_data/local_eep_data.o \

C_DEPS_QUOTED += \
"./Sources/Transport/Local_eep_data/local_eep_data.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Transport/Local_eep_data/local_eep_data.o: ../Sources/Transport/Local_eep_data/local_eep_data.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Transport/Local_eep_data/local_eep_data.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Transport/Local_eep_data/local_eep_data.o"
	@echo 'Finished building: $<'
	@echo ' '


