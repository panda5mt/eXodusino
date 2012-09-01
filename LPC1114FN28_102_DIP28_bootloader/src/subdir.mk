################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/user_application.cpp 

OBJS += \
./src/user_application.o 

CPP_DEPS += \
./src/user_application.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DNO_EXTCLK -DNDEBUG -D__CODE_RED -I"/Users/lynxeyed/Documents/workspace/eXodusino/src" -I"/Users/lynxeyed/Documents/workspace/eXodusino/src/XBee" -I"/Users/lynxeyed/Documents/workspace/eXodusino/src/FatFs" -I"/Users/lynxeyed/Documents/workspace/eXodusino/src/core" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


