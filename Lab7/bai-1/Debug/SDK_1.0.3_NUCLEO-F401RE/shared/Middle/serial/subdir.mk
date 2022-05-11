################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/THUC\ TAP\ LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/serial.c \
D:/THUC\ TAP\ LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/uartcmd.c 

OBJS += \
./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/serial.o \
./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/uartcmd.o 

C_DEPS += \
./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/serial.d \
./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/uartcmd.d 


# Each subdirectory must supply rules for building sources it contributes
SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/serial.o: D:/THUC\ TAP\ LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/serial.c SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/CMSIS/Include" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/STM32F401RE_StdPeriph_Driver/inc" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/button" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/buzzer" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/led" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/rtos" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/ucglib" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Utilities" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/utils" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/uartcmd.o: D:/THUC\ TAP\ LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/uartcmd.c SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/CMSIS/Include" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/STM32F401RE_StdPeriph_Driver/inc" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/button" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/buzzer" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/led" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/rtos" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/ucglib" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Utilities" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/utils" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-SDK_1-2e-0-2e-3_NUCLEO-2d-F401RE-2f-shared-2f-Middle-2f-serial

clean-SDK_1-2e-0-2e-3_NUCLEO-2d-F401RE-2f-shared-2f-Middle-2f-serial:
	-$(RM) ./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/serial.d ./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/serial.o ./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/uartcmd.d ./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial/uartcmd.o

.PHONY: clean-SDK_1-2e-0-2e-3_NUCLEO-2d-F401RE-2f-shared-2f-Middle-2f-serial

