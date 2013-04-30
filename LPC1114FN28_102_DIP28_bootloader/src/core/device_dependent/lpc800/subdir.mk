################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/device_dependent/lpc800/cr_cpp_config.cpp \
../src/core/device_dependent/lpc800/cr_startup_lpc8xx.cpp \
../src/core/device_dependent/lpc800/delay.cpp \
../src/core/device_dependent/lpc800/gpio.cpp \
../src/core/device_dependent/lpc800/gpio_int.cpp \
../src/core/device_dependent/lpc800/lpc8xx_gpio.cpp \
../src/core/device_dependent/lpc800/lpc8xx_spi.cpp \
../src/core/device_dependent/lpc800/spi_middle.cpp \
../src/core/device_dependent/lpc800/swm.cpp \
../src/core/device_dependent/lpc800/system_LPC8xx.cpp \
../src/core/device_dependent/lpc800/uart_middle.cpp 

C_SRCS += \
../src/core/device_dependent/lpc800/lpc8xx_uart.c 

OBJS += \
./src/core/device_dependent/lpc800/cr_cpp_config.o \
./src/core/device_dependent/lpc800/cr_startup_lpc8xx.o \
./src/core/device_dependent/lpc800/delay.o \
./src/core/device_dependent/lpc800/gpio.o \
./src/core/device_dependent/lpc800/gpio_int.o \
./src/core/device_dependent/lpc800/lpc8xx_gpio.o \
./src/core/device_dependent/lpc800/lpc8xx_spi.o \
./src/core/device_dependent/lpc800/lpc8xx_uart.o \
./src/core/device_dependent/lpc800/spi_middle.o \
./src/core/device_dependent/lpc800/swm.o \
./src/core/device_dependent/lpc800/system_LPC8xx.o \
./src/core/device_dependent/lpc800/uart_middle.o 

C_DEPS += \
./src/core/device_dependent/lpc800/lpc8xx_uart.d 

CPP_DEPS += \
./src/core/device_dependent/lpc800/cr_cpp_config.d \
./src/core/device_dependent/lpc800/cr_startup_lpc8xx.d \
./src/core/device_dependent/lpc800/delay.d \
./src/core/device_dependent/lpc800/gpio.d \
./src/core/device_dependent/lpc800/gpio_int.d \
./src/core/device_dependent/lpc800/lpc8xx_gpio.d \
./src/core/device_dependent/lpc800/lpc8xx_spi.d \
./src/core/device_dependent/lpc800/spi_middle.d \
./src/core/device_dependent/lpc800/swm.d \
./src/core/device_dependent/lpc800/system_LPC8xx.d \
./src/core/device_dependent/lpc800/uart_middle.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/device_dependent/lpc800/%.o: ../src/core/device_dependent/lpc800/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DUSE_LPC1114 -DNEXTPINO -DNO_EXTCLK -DNDEBUG -D__CODE_RED -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core/device_dependent/lpc1114" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/Samples" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/XBee" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/FatFs" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/core/device_dependent/lpc800/%.o: ../src/core/device_dependent/lpc800/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DNDEBUG -D__CODE_RED -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core/device_dependent/lpc1114" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/Samples" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/FatFs" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/XBee" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core" -Os -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


