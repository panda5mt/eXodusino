################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/device_dependent/lpc1115/cr_cpp_config.cpp \
../src/core/device_dependent/lpc1115/cr_startup_lpc11.cpp \
../src/core/device_dependent/lpc1115/delay.cpp \
../src/core/device_dependent/lpc1115/gpio.cpp \
../src/core/device_dependent/lpc1115/gpio_int.cpp \
../src/core/device_dependent/lpc1115/spi_middle.cpp \
../src/core/device_dependent/lpc1115/system_LPC11xx.cpp \
../src/core/device_dependent/lpc1115/uart_middle.cpp 

OBJS += \
./src/core/device_dependent/lpc1115/cr_cpp_config.o \
./src/core/device_dependent/lpc1115/cr_startup_lpc11.o \
./src/core/device_dependent/lpc1115/delay.o \
./src/core/device_dependent/lpc1115/gpio.o \
./src/core/device_dependent/lpc1115/gpio_int.o \
./src/core/device_dependent/lpc1115/spi_middle.o \
./src/core/device_dependent/lpc1115/system_LPC11xx.o \
./src/core/device_dependent/lpc1115/uart_middle.o 

CPP_DEPS += \
./src/core/device_dependent/lpc1115/cr_cpp_config.d \
./src/core/device_dependent/lpc1115/cr_startup_lpc11.d \
./src/core/device_dependent/lpc1115/delay.d \
./src/core/device_dependent/lpc1115/gpio.d \
./src/core/device_dependent/lpc1115/gpio_int.d \
./src/core/device_dependent/lpc1115/spi_middle.d \
./src/core/device_dependent/lpc1115/system_LPC11xx.d \
./src/core/device_dependent/lpc1115/uart_middle.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/device_dependent/lpc1115/%.o: ../src/core/device_dependent/lpc1115/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DNO_EXTCLK -DUSE_LPC800 -DNDEBUG -D__CODE_RED -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/Samples" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core/device_dependent/lpc800" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core" -O3 -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


