################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/LIN_Stack/coreapi/lin_common_api.c" \
"../Sources/Driver/LIN_Stack/coreapi/lin_common_proto.c" \
"../Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.c" \
"../Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.c" \
"../Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.c" \
"../Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.c" \

C_SRCS += \
../Sources/Driver/LIN_Stack/coreapi/lin_common_api.c \
../Sources/Driver/LIN_Stack/coreapi/lin_common_proto.c \
../Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.c \
../Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.c \
../Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.c \
../Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.c \

OBJS += \
./Sources/Driver/LIN_Stack/coreapi/lin_common_api.o \
./Sources/Driver/LIN_Stack/coreapi/lin_common_proto.o \
./Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.o \
./Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.o \
./Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.o \
./Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.o \

OBJS_QUOTED += \
"./Sources/Driver/LIN_Stack/coreapi/lin_common_api.o" \
"./Sources/Driver/LIN_Stack/coreapi/lin_common_proto.o" \
"./Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.o" \
"./Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.o" \
"./Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.o" \
"./Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.o" \

C_DEPS += \
./Sources/Driver/LIN_Stack/coreapi/lin_common_api.d \
./Sources/Driver/LIN_Stack/coreapi/lin_common_proto.d \
./Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.d \
./Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.d \
./Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.d \
./Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.d \

OBJS_OS_FORMAT += \
./Sources/Driver/LIN_Stack/coreapi/lin_common_api.o \
./Sources/Driver/LIN_Stack/coreapi/lin_common_proto.o \
./Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.o \
./Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.o \
./Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.o \
./Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.o \

C_DEPS_QUOTED += \
"./Sources/Driver/LIN_Stack/coreapi/lin_common_api.d" \
"./Sources/Driver/LIN_Stack/coreapi/lin_common_proto.d" \
"./Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.d" \
"./Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.d" \
"./Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.d" \
"./Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/LIN_Stack/coreapi/lin_common_api.o: ../Sources/Driver/LIN_Stack/coreapi/lin_common_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/LIN_Stack/coreapi/lin_common_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/LIN_Stack/coreapi/lin_common_api.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Driver/LIN_Stack/coreapi/lin_common_proto.o: ../Sources/Driver/LIN_Stack/coreapi/lin_common_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/LIN_Stack/coreapi/lin_common_proto.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/LIN_Stack/coreapi/lin_common_proto.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.o: ../Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/LIN_Stack/coreapi/lin_j2602_api.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.o: ../Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/LIN_Stack/coreapi/lin_j2602_proto.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.o: ../Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/LIN_Stack/coreapi/lin_lin21_api.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.o: ../Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Driver/LIN_Stack/coreapi/lin_lin21_proto.o"
	@echo 'Finished building: $<'
	@echo ' '


