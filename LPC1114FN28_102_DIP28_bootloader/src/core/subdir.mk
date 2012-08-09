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
../src/core/cr_cpp_config.cpp \
../src/core/cr_startup_lpc11.cpp \
../src/core/delay.cpp \
../src/core/gpio.cpp \
../src/core/gpio_int.cpp \
../src/core/maryoled.cpp \
../src/core/startup_mary.cpp \
../src/core/system_LPC11xx.cpp \
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
./src/core/cr_cpp_config.o \
./src/core/cr_startup_lpc11.o \
./src/core/delay.o \
./src/core/gpio.o \
./src/core/gpio_int.o \
./src/core/maryoled.o \
./src/core/startup_mary.o \
./src/core/system_LPC11xx.o \
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
./src/core/cr_cpp_config.d \
./src/core/cr_startup_lpc11.d \
./src/core/delay.d \
./src/core/gpio.d \
./src/core/gpio_int.d \
./src/core/maryoled.d \
./src/core/startup_mary.d \
./src/core/system_LPC11xx.d \
./src/core/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DNDEBUG -D__CODE_RED -I"/Users/lynxeyed/Documents/workspace/eXodusino/src" -I"/Users/lynxeyed/Documents/workspace/eXodusino/src/XBee" -I"/Users/lynxeyed/Documents/workspace/eXodusino/src/FatFs" -I"/Users/lynxeyed/Documents/workspace/eXodusino/src/core" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


