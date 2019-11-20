################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/lin_cfg/lin_cfg.c" \

C_SRCS += \
../Sources/lin_cfg/lin_cfg.c \

OBJS += \
./Sources/lin_cfg/lin_cfg.o \

OBJS_QUOTED += \
"./Sources/lin_cfg/lin_cfg.o" \

C_DEPS += \
./Sources/lin_cfg/lin_cfg.d \

OBJS_OS_FORMAT += \
./Sources/lin_cfg/lin_cfg.o \

C_DEPS_QUOTED += \
"./Sources/lin_cfg/lin_cfg.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/lin_cfg/lin_cfg.o: ../Sources/lin_cfg/lin_cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/lin_cfg/lin_cfg.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/lin_cfg/lin_cfg.o"
	@echo 'Finished building: $<'
	@echo ' '


