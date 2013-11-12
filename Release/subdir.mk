################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Actuator.cpp \
../Bluetooth.cpp \
../Log.cpp \
../PirateDotty.cpp \
../RandomWalk.cpp \
../jsmn.cpp 

CPP_DEPS += \
./Actuator.cpp.d \
./Bluetooth.cpp.d \
./Log.cpp.d \
./PirateDotty.cpp.d \
./RandomWalk.cpp.d \
./jsmn.cpp.d 

LINK_OBJ += \
./Actuator.cpp.o \
./Bluetooth.cpp.o \
./Log.cpp.o \
./PirateDotty.cpp.o \
./RandomWalk.cpp.o \
./jsmn.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
Actuator.cpp.o: ../Actuator.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib -fno-rtti -fno-exceptions -mcpu=cortex-m4 -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -MMD -DARDUINO=152  -mthumb  -D__MK20DX128__  -felide-constructors -std=gnu++0x   -I"/opt/arduino-1.5.2/hardware/teensy/all/cores/teensy3" -I"/home/dominik/arduino/libraries/aJson" -I"/home/dominik/arduino/libraries/aJson/utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Bluetooth.cpp.o: ../Bluetooth.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib -fno-rtti -fno-exceptions -mcpu=cortex-m4 -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -MMD -DARDUINO=152  -mthumb  -D__MK20DX128__  -felide-constructors -std=gnu++0x   -I"/opt/arduino-1.5.2/hardware/teensy/all/cores/teensy3" -I"/home/dominik/arduino/libraries/aJson" -I"/home/dominik/arduino/libraries/aJson/utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Log.cpp.o: ../Log.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib -fno-rtti -fno-exceptions -mcpu=cortex-m4 -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -MMD -DARDUINO=152  -mthumb  -D__MK20DX128__  -felide-constructors -std=gnu++0x   -I"/opt/arduino-1.5.2/hardware/teensy/all/cores/teensy3" -I"/home/dominik/arduino/libraries/aJson" -I"/home/dominik/arduino/libraries/aJson/utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

PirateDotty.cpp.o: ../PirateDotty.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib -fno-rtti -fno-exceptions -mcpu=cortex-m4 -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -MMD -DARDUINO=152  -mthumb  -D__MK20DX128__  -felide-constructors -std=gnu++0x   -I"/opt/arduino-1.5.2/hardware/teensy/all/cores/teensy3" -I"/home/dominik/arduino/libraries/aJson" -I"/home/dominik/arduino/libraries/aJson/utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

RandomWalk.cpp.o: ../RandomWalk.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib -fno-rtti -fno-exceptions -mcpu=cortex-m4 -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -MMD -DARDUINO=152  -mthumb  -D__MK20DX128__  -felide-constructors -std=gnu++0x   -I"/opt/arduino-1.5.2/hardware/teensy/all/cores/teensy3" -I"/home/dominik/arduino/libraries/aJson" -I"/home/dominik/arduino/libraries/aJson/utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

jsmn.cpp.o: ../jsmn.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/arduino-1.5.2/hardware/teensy/tools/linux/arm-none-eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib -fno-rtti -fno-exceptions -mcpu=cortex-m4 -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -MMD -DARDUINO=152  -mthumb  -D__MK20DX128__  -felide-constructors -std=gnu++0x   -I"/opt/arduino-1.5.2/hardware/teensy/all/cores/teensy3" -I"/home/dominik/arduino/libraries/aJson" -I"/home/dominik/arduino/libraries/aJson/utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


