################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/LiquidCrystal.cpp \
../src/core/Print.cpp \
../src/core/SPI.cpp \
../src/core/SPI1.cpp \
../src/core/SoftwareSerial.cpp \
../src/core/Wire.cpp \
../src/core/analogio.cpp \
../src/core/arithmetical.cpp \
../src/core/startup_mary.cpp \
../src/core/uart.cpp 

OBJS += \
./src/core/LiquidCrystal.o \
./src/core/Print.o \
./src/core/SPI.o \
./src/core/SPI1.o \
./src/core/SoftwareSerial.o \
./src/core/Wire.o \
./src/core/analogio.o \
./src/core/arithmetical.o \
./src/core/startup_mary.o \
./src/core/uart.o 

CPP_DEPS += \
./src/core/LiquidCrystal.d \
./src/core/Print.d \
./src/core/SPI.d \
./src/core/SPI1.d \
./src/core/SoftwareSerial.d \
./src/core/Wire.d \
./src/core/analogio.d \
./src/core/arithmetical.d \
./src/core/startup_mary.d \
./src/core/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DUSE_LPC1114 -DNDEBUG -D__CODE_RED -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core/device_dependent/lpc1114" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/XBee" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/FatFs" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core" -O3 -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


