################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/LiquidCrystal.cpp \
../src/core/Print.cpp \
../src/core/SPI.cpp \
../src/core/SoftwareSerial.cpp \
../src/core/Wire.cpp \
../src/core/arithmetical.cpp \
../src/core/startup_mary.cpp \
../src/core/uart.cpp 

OBJS += \
./src/core/LiquidCrystal.o \
./src/core/Print.o \
./src/core/SPI.o \
./src/core/SoftwareSerial.o \
./src/core/Wire.o \
./src/core/arithmetical.o \
./src/core/startup_mary.o \
./src/core/uart.o 

CPP_DEPS += \
./src/core/LiquidCrystal.d \
./src/core/Print.d \
./src/core/SPI.d \
./src/core/SoftwareSerial.d \
./src/core/Wire.d \
./src/core/arithmetical.d \
./src/core/startup_mary.d \
./src/core/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DUSE_LPC800 -DNDEBUG -D__CODE_RED -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/Samples" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core/device_dependent/lpc800" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


