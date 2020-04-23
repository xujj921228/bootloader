################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/RLS_app/rls_app.c" \

C_SRCS += \
../Sources/Application/RLS_app/rls_app.c \

OBJS += \
./Sources/Application/RLS_app/rls_app.o \

OBJS_QUOTED += \
"./Sources/Application/RLS_app/rls_app.o" \

C_DEPS += \
./Sources/Application/RLS_app/rls_app.d \

OBJS_OS_FORMAT += \
./Sources/Application/RLS_app/rls_app.o \

C_DEPS_QUOTED += \
"./Sources/Application/RLS_app/rls_app.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/RLS_app/rls_app.o: ../Sources/Application/RLS_app/rls_app.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/RLS_app/rls_app.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/RLS_app/rls_app.o"
	@echo 'Finished building: $<'
	@echo ' '


