################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/SPI/spi.c" \

C_SRCS += \
../Sources/Driver/SPI/spi.c \

OBJS += \
./Sources/Driver/SPI/spi.o \

OBJS_QUOTED += \
"./Sources/Driver/SPI/spi.o" \

C_DEPS += \
./Sources/Driver/SPI/spi.d \

OBJS_OS_FORMAT += \
./Sources/Driver/SPI/spi.o \

C_DEPS_QUOTED += \
"./Sources/Driver/SPI/spi.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/SPI/spi.o: ../Sources/Driver/SPI/spi.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/SPI/spi.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/SPI/spi.o"
	@echo 'Finished building: $<'
	@echo ' '


