################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/dominik/arduino/libraries/aJson/utility/stringbuffer.c 

C_DEPS += \
./Libraries/aJson/utility/stringbuffer.c.d 

LINK_OBJ += \
./Libraries/aJson/utility/stringbuffer.c.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/aJson/utility/stringbuffer.c.o: /home/dominik/arduino/libraries/aJson/utility/stringbuffer.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-gcc" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib  -mcpu=cortex-m4 -DF_CPU=96000000 -DTIME_T=1365449461 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -MMD -DARDUINO=152  -mthumb  -D__MK20DX128__    -I"/opt/arduino-1.5.2/hardware/teensy/all/cores/teensy3" -I"/data/ws_arduino/PirateDotty/includes" -I"/home/dominik/arduino/libraries/aJson" -I"/home/dominik/arduino/libraries/aJson/utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


