################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/LIN_Stack/lowlevel/lin.c" \

C_SRCS += \
../Sources/LIN_Stack/lowlevel/lin.c \

OBJS += \
./Sources/LIN_Stack/lowlevel/lin.o \

C_DEPS += \
./Sources/LIN_Stack/lowlevel/lin.d \

OBJS_QUOTED += \
"./Sources/LIN_Stack/lowlevel/lin.o" \

C_DEPS_QUOTED += \
"./Sources/LIN_Stack/lowlevel/lin.d" \

OBJS_OS_FORMAT += \
./Sources/LIN_Stack/lowlevel/lin.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/LIN_Stack/lowlevel/lin.o: ../Sources/LIN_Stack/lowlevel/lin.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LIN_Stack/lowlevel/lin.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LIN_Stack/lowlevel/lin.o"
	@echo 'Finished building: $<'
	@echo ' '


