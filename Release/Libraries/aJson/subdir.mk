################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/dominik/arduino/libraries/aJson/aJSON.cpp 

CPP_DEPS += \
./Libraries/aJson/aJSON.cpp.d 

LINK_OBJ += \
./Libraries/aJson/aJSON.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/aJson/aJSON.cpp.o: /home/dominik/arduino/libraries/aJson/aJSON.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib -fno-rtti -fno-exceptions -mcpu=cortex-m4 -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -MMD -DARDUINO=152  -mthumb  -D__MK20DX128__  -felide-constructors -std=gnu++0x   -I"/opt/arduino-1.5.2/hardware/teensy/all/cores/teensy3" -I"/home/dominik/arduino/libraries/aJson" -I"/home/dominik/arduino/libraries/aJson/utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


