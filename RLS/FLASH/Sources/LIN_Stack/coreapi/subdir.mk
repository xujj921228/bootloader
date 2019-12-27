################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/LIN_Stack/coreapi/lin_common_api.c" \
"../Sources/LIN_Stack/coreapi/lin_common_proto.c" \
"../Sources/LIN_Stack/coreapi/lin_j2602_api.c" \
"../Sources/LIN_Stack/coreapi/lin_j2602_proto.c" \
"../Sources/LIN_Stack/coreapi/lin_lin21_api.c" \
"../Sources/LIN_Stack/coreapi/lin_lin21_proto.c" \

C_SRCS += \
../Sources/LIN_Stack/coreapi/lin_common_api.c \
../Sources/LIN_Stack/coreapi/lin_common_proto.c \
../Sources/LIN_Stack/coreapi/lin_j2602_api.c \
../Sources/LIN_Stack/coreapi/lin_j2602_proto.c \
../Sources/LIN_Stack/coreapi/lin_lin21_api.c \
../Sources/LIN_Stack/coreapi/lin_lin21_proto.c \

OBJS += \
./Sources/LIN_Stack/coreapi/lin_common_api.o \
./Sources/LIN_Stack/coreapi/lin_common_proto.o \
./Sources/LIN_Stack/coreapi/lin_j2602_api.o \
./Sources/LIN_Stack/coreapi/lin_j2602_proto.o \
./Sources/LIN_Stack/coreapi/lin_lin21_api.o \
./Sources/LIN_Stack/coreapi/lin_lin21_proto.o \

OBJS_QUOTED += \
"./Sources/LIN_Stack/coreapi/lin_common_api.o" \
"./Sources/LIN_Stack/coreapi/lin_common_proto.o" \
"./Sources/LIN_Stack/coreapi/lin_j2602_api.o" \
"./Sources/LIN_Stack/coreapi/lin_j2602_proto.o" \
"./Sources/LIN_Stack/coreapi/lin_lin21_api.o" \
"./Sources/LIN_Stack/coreapi/lin_lin21_proto.o" \

C_DEPS += \
./Sources/LIN_Stack/coreapi/lin_common_api.d \
./Sources/LIN_Stack/coreapi/lin_common_proto.d \
./Sources/LIN_Stack/coreapi/lin_j2602_api.d \
./Sources/LIN_Stack/coreapi/lin_j2602_proto.d \
./Sources/LIN_Stack/coreapi/lin_lin21_api.d \
./Sources/LIN_Stack/coreapi/lin_lin21_proto.d \

OBJS_OS_FORMAT += \
./Sources/LIN_Stack/coreapi/lin_common_api.o \
./Sources/LIN_Stack/coreapi/lin_common_proto.o \
./Sources/LIN_Stack/coreapi/lin_j2602_api.o \
./Sources/LIN_Stack/coreapi/lin_j2602_proto.o \
./Sources/LIN_Stack/coreapi/lin_lin21_api.o \
./Sources/LIN_Stack/coreapi/lin_lin21_proto.o \

C_DEPS_QUOTED += \
"./Sources/LIN_Stack/coreapi/lin_common_api.d" \
"./Sources/LIN_Stack/coreapi/lin_common_proto.d" \
"./Sources/LIN_Stack/coreapi/lin_j2602_api.d" \
"./Sources/LIN_Stack/coreapi/lin_j2602_proto.d" \
"./Sources/LIN_Stack/coreapi/lin_lin21_api.d" \
"./Sources/LIN_Stack/coreapi/lin_lin21_proto.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/LIN_Stack/coreapi/lin_common_api.o: ../Sources/LIN_Stack/coreapi/lin_common_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LIN_Stack/coreapi/lin_common_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LIN_Stack/coreapi/lin_common_api.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/LIN_Stack/coreapi/lin_common_proto.o: ../Sources/LIN_Stack/coreapi/lin_common_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LIN_Stack/coreapi/lin_common_proto.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LIN_Stack/coreapi/lin_common_proto.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/LIN_Stack/coreapi/lin_j2602_api.o: ../Sources/LIN_Stack/coreapi/lin_j2602_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LIN_Stack/coreapi/lin_j2602_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LIN_Stack/coreapi/lin_j2602_api.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/LIN_Stack/coreapi/lin_j2602_proto.o: ../Sources/LIN_Stack/coreapi/lin_j2602_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #26 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LIN_Stack/coreapi/lin_j2602_proto.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LIN_Stack/coreapi/lin_j2602_proto.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/LIN_Stack/coreapi/lin_lin21_api.o: ../Sources/LIN_Stack/coreapi/lin_lin21_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LIN_Stack/coreapi/lin_lin21_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LIN_Stack/coreapi/lin_lin21_api.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/LIN_Stack/coreapi/lin_lin21_proto.o: ../Sources/LIN_Stack/coreapi/lin_lin21_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LIN_Stack/coreapi/lin_lin21_proto.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LIN_Stack/coreapi/lin_lin21_proto.o"
	@echo 'Finished building: $<'
	@echo ' '


