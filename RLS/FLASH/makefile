################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 20
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Sources/lin_cfg/subdir.mk
-include Sources/driver/gpio/subdir.mk
-include Sources/driver/eeprom/subdir.mk
-include Sources/driver/clock/subdir.mk
-include Sources/LIN_Stack/transport/subdir.mk
-include Sources/LIN_Stack/lowlevel/subdir.mk
-include Sources/LIN_Stack/diagnostic/subdir.mk
-include Sources/LIN_Stack/coreapi/subdir.mk
-include Sources/LIN_Stack/bsp/UART/subdir.mk
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
	@echo 'Executing target #21 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) @"RLS.args" -o"RLS.elf"
	@echo 'Finished building target: $@'
	@echo ' '

RLS.hex: RLS.elf
	@echo 'Executing target #22 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Create Flash Image'
	"$(ARMSourceryDirEnv)/arm-none-eabi-objcopy"  -O srec RLS.elf "RLS.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) $(SECONDARY_FLASH_QUOTED) "./*/*/*.o" "./*/*/*/*/*.o" "./*/*/*/*.o" "./*/*.o"  $(S_UPPER_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*/*.d" "./*/*/*/*/*.d" "./*/*/*/*.d" "./*/*.d"  $(ProjDirPath)/FLASH/RLS.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/SKEAZN64_flash.ld RLS.elf 

warning-messages: 

