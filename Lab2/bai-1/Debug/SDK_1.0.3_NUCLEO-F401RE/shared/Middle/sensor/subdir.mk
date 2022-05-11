################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/THUC\ TAP\ LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/lightsensor.c \
D:/THUC\ TAP\ LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/temhumsensor.c 

OBJS += \
./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/lightsensor.o \
./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/temhumsensor.o 

C_DEPS += \
./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/lightsensor.d \
./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/temhumsensor.d 


# Each subdirectory must supply rules for building sources it contributes
SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/lightsensor.o: D:/THUC\ TAP\ LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/lightsensor.c SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/CMSIS/Include" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/STM32F401RE_StdPeriph_Driver/inc" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/button" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/buzzer" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/led" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/rtos" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/ucglib" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Utilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/temhumsensor.o: D:/THUC\ TAP\ LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/temhumsensor.c SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/CMSIS/Include" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/STM32F401RE_StdPeriph_Driver/inc" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/button" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/buzzer" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/led" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/rtos" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/ucglib" -I"D:/THUC TAP LUMI/thu-vien/SDK_1.0.3_NUCLEO-F401RE/shared/Utilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-SDK_1-2e-0-2e-3_NUCLEO-2d-F401RE-2f-shared-2f-Middle-2f-sensor

clean-SDK_1-2e-0-2e-3_NUCLEO-2d-F401RE-2f-shared-2f-Middle-2f-sensor:
	-$(RM) ./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/lightsensor.d ./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/lightsensor.o ./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/temhumsensor.d ./SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor/temhumsensor.o

.PHONY: clean-SDK_1-2e-0-2e-3_NUCLEO-2d-F401RE-2f-shared-2f-Middle-2f-sensor

