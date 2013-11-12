################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include arduino/core/subdir.mk
-include Libraries/aJson/utility/subdir.mk
-include Libraries/aJson/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/data/ws_arduino/PirateDotty/Release/teensy.ar \

ELF += \
PirateDotty.elf \

EEP += \
PirateDotty.eep \

FLASH_IMAGE += \
Release/PirateDotty.hex \


# All Target
all: PirateDotty

# Tool invocations
PirateDotty: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-size" -A "/data/ws_arduino/PirateDotty/Release/PirateDotty.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/data/ws_arduino/PirateDotty/Release/teensy.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-ar" -r "/data/ws_arduino/PirateDotty/Release/teensy.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

PirateDotty.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-gcc"  -Os -Wl,--gc-sections -mcpu=cortex-m4 -mthumb "-T/opt/arduino-1.5.2/hardware/teensy/all/cores/teensy3/mk20dx128.ld" -o "/data/ws_arduino/PirateDotty/Release/PirateDotty.elf"   $(LINK_OBJ) $(AR)  -L"/data/ws_arduino/PirateDotty/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

PirateDotty.eep: $(ELF)
	@echo 'Create eeprom image'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 "/data/ws_arduino/PirateDotty/Release/PirateDotty.elf" "/data/ws_arduino/PirateDotty/Release/PirateDotty.eep"
	@echo 'Finished building: $@'
	@echo ' '

Release/PirateDotty.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-objcopy" -O ihex -R .eeprom "/data/ws_arduino/PirateDotty/Release/PirateDotty.elf" "/data/ws_arduino/PirateDotty/Release/PirateDotty.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELF)$(C++_DEPS)$(AR)$(C_DEPS)$(CC_DEPS)$(FLASH_IMAGE)$(AR_OBJ)$(CPP_DEPS)$(LINK_OBJ)$(EEP)$(CXX_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) PirateDotty
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
