################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/LIN_Stack/transport/lin_commontl_api.c" \
"../Sources/LIN_Stack/transport/lin_commontl_proto.c" \
"../Sources/LIN_Stack/transport/lin_lin21tl_api.c" \

C_SRCS += \
../Sources/LIN_Stack/transport/lin_commontl_api.c \
../Sources/LIN_Stack/transport/lin_commontl_proto.c \
../Sources/LIN_Stack/transport/lin_lin21tl_api.c \

OBJS += \
./Sources/LIN_Stack/transport/lin_commontl_api.o \
./Sources/LIN_Stack/transport/lin_commontl_proto.o \
./Sources/LIN_Stack/transport/lin_lin21tl_api.o \

OBJS_QUOTED += \
"./Sources/LIN_Stack/transport/lin_commontl_api.o" \
"./Sources/LIN_Stack/transport/lin_commontl_proto.o" \
"./Sources/LIN_Stack/transport/lin_lin21tl_api.o" \

C_DEPS += \
./Sources/LIN_Stack/transport/lin_commontl_api.d \
./Sources/LIN_Stack/transport/lin_commontl_proto.d \
./Sources/LIN_Stack/transport/lin_lin21tl_api.d \

OBJS_OS_FORMAT += \
./Sources/LIN_Stack/transport/lin_commontl_api.o \
./Sources/LIN_Stack/transport/lin_commontl_proto.o \
./Sources/LIN_Stack/transport/lin_lin21tl_api.o \

C_DEPS_QUOTED += \
"./Sources/LIN_Stack/transport/lin_commontl_api.d" \
"./Sources/LIN_Stack/transport/lin_commontl_proto.d" \
"./Sources/LIN_Stack/transport/lin_lin21tl_api.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/LIN_Stack/transport/lin_commontl_api.o: ../Sources/LIN_Stack/transport/lin_commontl_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LIN_Stack/transport/lin_commontl_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LIN_Stack/transport/lin_commontl_api.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/LIN_Stack/transport/lin_commontl_proto.o: ../Sources/LIN_Stack/transport/lin_commontl_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LIN_Stack/transport/lin_commontl_proto.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LIN_Stack/transport/lin_commontl_proto.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/LIN_Stack/transport/lin_lin21tl_api.o: ../Sources/LIN_Stack/transport/lin_lin21tl_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LIN_Stack/transport/lin_lin21tl_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LIN_Stack/transport/lin_lin21tl_api.o"
	@echo 'Finished building: $<'
	@echo ' '

