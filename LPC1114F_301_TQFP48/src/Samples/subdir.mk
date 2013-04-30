################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Samples/maryoled.cpp 

OBJS += \
./src/Samples/maryoled.o 

CPP_DEPS += \
./src/Samples/maryoled.d 


# Each subdirectory must supply rules for building sources it contributes
src/Samples/%.o: ../src/Samples/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DUSE_LPC1114 -DNDEBUG -D__CODE_RED -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core/device_dependent/lpc1114" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/XBee" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/FatFs" -I"/Users/lynxeyed/Documents/LPCXpresso_5.1.0/workspace/eXodusino/src/core" -O3 -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


