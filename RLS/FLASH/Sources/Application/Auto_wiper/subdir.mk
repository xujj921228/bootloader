################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/Auto_wiper/auto_wiper.c" \

C_SRCS += \
../Sources/Application/Auto_wiper/auto_wiper.c \

OBJS += \
./Sources/Application/Auto_wiper/auto_wiper.o \

OBJS_QUOTED += \
"./Sources/Application/Auto_wiper/auto_wiper.o" \

C_DEPS += \
./Sources/Application/Auto_wiper/auto_wiper.d \

OBJS_OS_FORMAT += \
./Sources/Application/Auto_wiper/auto_wiper.o \

C_DEPS_QUOTED += \
"./Sources/Application/Auto_wiper/auto_wiper.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Auto_wiper/auto_wiper.o: ../Sources/Application/Auto_wiper/auto_wiper.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/Auto_wiper/auto_wiper.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/Auto_wiper/auto_wiper.o"
	@echo 'Finished building: $<'
	@echo ' '


