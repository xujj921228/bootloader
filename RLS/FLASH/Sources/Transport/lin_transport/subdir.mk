################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Transport/lin_transport/lin_commontl_api.c" \
"../Sources/Transport/lin_transport/lin_commontl_proto.c" \
"../Sources/Transport/lin_transport/lin_j2602tl_api.c" \
"../Sources/Transport/lin_transport/lin_lin21tl_api.c" \

C_SRCS += \
../Sources/Transport/lin_transport/lin_commontl_api.c \
../Sources/Transport/lin_transport/lin_commontl_proto.c \
../Sources/Transport/lin_transport/lin_j2602tl_api.c \
../Sources/Transport/lin_transport/lin_lin21tl_api.c \

OBJS += \
./Sources/Transport/lin_transport/lin_commontl_api.o \
./Sources/Transport/lin_transport/lin_commontl_proto.o \
./Sources/Transport/lin_transport/lin_j2602tl_api.o \
./Sources/Transport/lin_transport/lin_lin21tl_api.o \

OBJS_QUOTED += \
"./Sources/Transport/lin_transport/lin_commontl_api.o" \
"./Sources/Transport/lin_transport/lin_commontl_proto.o" \
"./Sources/Transport/lin_transport/lin_j2602tl_api.o" \
"./Sources/Transport/lin_transport/lin_lin21tl_api.o" \

C_DEPS += \
./Sources/Transport/lin_transport/lin_commontl_api.d \
./Sources/Transport/lin_transport/lin_commontl_proto.d \
./Sources/Transport/lin_transport/lin_j2602tl_api.d \
./Sources/Transport/lin_transport/lin_lin21tl_api.d \

OBJS_OS_FORMAT += \
./Sources/Transport/lin_transport/lin_commontl_api.o \
./Sources/Transport/lin_transport/lin_commontl_proto.o \
./Sources/Transport/lin_transport/lin_j2602tl_api.o \
./Sources/Transport/lin_transport/lin_lin21tl_api.o \

C_DEPS_QUOTED += \
"./Sources/Transport/lin_transport/lin_commontl_api.d" \
"./Sources/Transport/lin_transport/lin_commontl_proto.d" \
"./Sources/Transport/lin_transport/lin_j2602tl_api.d" \
"./Sources/Transport/lin_transport/lin_lin21tl_api.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Transport/lin_transport/lin_commontl_api.o: ../Sources/Transport/lin_transport/lin_commontl_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Transport/lin_transport/lin_commontl_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Transport/lin_transport/lin_commontl_api.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Transport/lin_transport/lin_commontl_proto.o: ../Sources/Transport/lin_transport/lin_commontl_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Transport/lin_transport/lin_commontl_proto.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Transport/lin_transport/lin_commontl_proto.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Transport/lin_transport/lin_j2602tl_api.o: ../Sources/Transport/lin_transport/lin_j2602tl_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Transport/lin_transport/lin_j2602tl_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Transport/lin_transport/lin_j2602tl_api.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Transport/lin_transport/lin_lin21tl_api.o: ../Sources/Transport/lin_transport/lin_lin21tl_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Transport/lin_transport/lin_lin21tl_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Transport/lin_transport/lin_lin21tl_api.o"
	@echo 'Finished building: $<'
	@echo ' '


