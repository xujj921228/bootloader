################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 41
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/Transport/lin_transport/subdir.mk
-include Sources/Transport/lin_cfg/subdir.mk
-include Sources/Transport/MLX75308/subdir.mk
-include Sources/Transport/Local_eep_data/subdir.mk
-include Sources/Transport/LIN_app/subdir.mk
-include Sources/Driver/watchdog/subdir.mk
-include Sources/Driver/rtc/subdir.mk
-include Sources/Driver/pmc/subdir.mk
-include Sources/Driver/gpio/subdir.mk
-include Sources/Driver/ftm/subdir.mk
-include Sources/Driver/eeprom/subdir.mk
-include Sources/Driver/clock/subdir.mk
-include Sources/Driver/adc/subdir.mk
-include Sources/Driver/SPI/subdir.mk
-include Sources/Driver/LIN_Stack/lowlevel/subdir.mk
-include Sources/Driver/LIN_Stack/coreapi/subdir.mk
-include Sources/Driver/LIN_Stack/bsp/UART/subdir.mk
-include Sources/Driver/IIC/subdir.mk
-include Sources/Application/subdir.mk
-include Sources/Application/Sleep/subdir.mk
-include Sources/Application/Diagnostic/subdir.mk
-include Sources/Application/Config_parameters/subdir.mk
-include Sources/Application/Battery/subdir.mk
-include Sources/Application/Auto_wiper/subdir.mk
-include Sources/Application/Auto_light/subdir.mk
-include Sources/Application/Auto_humid/subdir.mk
-include Sources/Application/Auto_fog/subdir.mk
-include Sources/Application/Auto_air/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
RLS.elf \

EXECUTABLES_QUOTED += \
"RLS.elf" \

EXECUTABLES_OS_FORMAT += \
RLS.elf \

SECONDARY_FLASH += \
RLS.hex \

SECONDARY_FLASH_QUOTED += \
"RLS.hex" \

SECONDARY_FLASH_OS_FORMAT += \
RLS.hex \


# All Target
all: warning-messages explicit-dependencies RLS.elf secondary-outputs

# Tool invocations
RLS.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/SKEAZN64_flash.ld
	@echo 'Building target: $@'
	@echo 'Executing target #42 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) @"RLS.args" -o"RLS.elf"
	@echo 'Finished building target: $@'
	@echo ' '

RLS.hex: RLS.elf
	@echo 'Executing target #43 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Create Flash Image'
	"$(ARMSourceryDirEnv)/arm-none-eabi-objcopy"  -O srec RLS.elf "RLS.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) $(SECONDARY_FLASH_QUOTED) "./*/*/*.o" "./*/*/*/*.o" "./*/*/*/*/*/*.o" "./*/*/*/*/*.o"  $(S_UPPER_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*/*.d" "./*/*/*/*.d" "./*/*/*/*/*/*.d" "./*/*/*/*/*.d"  $(ProjDirPath)/FLASH/RLS.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/SKEAZN64_flash.ld RLS.elf 

warning-messages: 

