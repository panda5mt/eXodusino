################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FatFs/SD.cpp \
../src/FatFs/pff.cpp \
../src/FatFs/sdcard.cpp 

OBJS += \
./src/FatFs/SD.o \
./src/FatFs/pff.o \
./src/FatFs/sdcard.o 

CPP_DEPS += \
./src/FatFs/SD.d \
./src/FatFs/pff.d \
./src/FatFs/sdcard.d 


# Each subdirectory must supply rules for building sources it contributes
src/FatFs/%.o: ../src/FatFs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DNDEBUG -D__CODE_RED -I"/Users/lynxeyed/Documents/workspace/eXodusino/src" -I"/Users/lynxeyed/Documents/workspace/eXodusino/src/XBee" -I"/Users/lynxeyed/Documents/workspace/eXodusino/src/FatFs" -I"/Users/lynxeyed/Documents/workspace/eXodusino/src/core" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


