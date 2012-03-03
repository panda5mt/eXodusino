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
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -I"C:\Documents and Settings\atsu\My Documents\LPCXpresso_4.0.6_152\workspace\eXodusino\src" -I"C:\Documents and Settings\atsu\My Documents\LPCXpresso_4.0.6_152\workspace\eXodusino\src\core" -I"C:\Documents and Settings\atsu\My Documents\LPCXpresso_4.0.6_152\workspace\eXodusino\src\XBee" -I"C:\Documents and Settings\atsu\My Documents\LPCXpresso_4.0.6_152\workspace\eXodusino\src\FatFs" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


