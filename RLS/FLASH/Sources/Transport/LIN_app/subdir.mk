################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Transport/LIN_app/lin_app.c" \

C_SRCS += \
../Sources/Transport/LIN_app/lin_app.c \

OBJS += \
./Sources/Transport/LIN_app/lin_app.o \

OBJS_QUOTED += \
"./Sources/Transport/LIN_app/lin_app.o" \

C_DEPS += \
./Sources/Transport/LIN_app/lin_app.d \

OBJS_OS_FORMAT += \
./Sources/Transport/LIN_app/lin_app.o \

C_DEPS_QUOTED += \
"./Sources/Transport/LIN_app/lin_app.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Transport/LIN_app/lin_app.o: ../Sources/Transport/LIN_app/lin_app.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Transport/LIN_app/lin_app.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Transport/LIN_app/lin_app.o"
	@echo 'Finished building: $<'
	@echo ' '


