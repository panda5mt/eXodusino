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
	arm-none-eabi-c++ -D__NEWLIB__ -D__CODE_RED -I"C:\Documents and Settings\atsu\My Documents\LPCXpresso_4.2.0_264\workspace\eXodusino\src" -I"C:\Documents and Settings\atsu\My Documents\LPCXpresso_4.2.0_264\workspace\eXodusino\src\core" -I"C:\Documents and Settings\atsu\My Documents\LPCXpresso_4.2.0_264\workspace\eXodusino\src\FatFs" -I"C:\Documents and Settings\atsu\My Documents\LPCXpresso_4.2.0_264\workspace\eXodusino\src\XBee" -Os -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


