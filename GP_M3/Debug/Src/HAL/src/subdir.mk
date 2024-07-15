################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/src/BUZZER.c \
../Src/HAL/src/Motor.c \
../Src/HAL/src/SERVO.c 

OBJS += \
./Src/HAL/src/BUZZER.o \
./Src/HAL/src/Motor.o \
./Src/HAL/src/SERVO.o 

C_DEPS += \
./Src/HAL/src/BUZZER.d \
./Src/HAL/src/Motor.d \
./Src/HAL/src/SERVO.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/src/%.o Src/HAL/src/%.su Src/HAL/src/%.cyclo: ../Src/HAL/src/%.c Src/HAL/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/LIB/STD_TYPES" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/APP/Inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/portable/GCC/ARM_CM3" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-src

clean-Src-2f-HAL-2f-src:
	-$(RM) ./Src/HAL/src/BUZZER.cyclo ./Src/HAL/src/BUZZER.d ./Src/HAL/src/BUZZER.o ./Src/HAL/src/BUZZER.su ./Src/HAL/src/Motor.cyclo ./Src/HAL/src/Motor.d ./Src/HAL/src/Motor.o ./Src/HAL/src/Motor.su ./Src/HAL/src/SERVO.cyclo ./Src/HAL/src/SERVO.d ./Src/HAL/src/SERVO.o ./Src/HAL/src/SERVO.su

.PHONY: clean-Src-2f-HAL-2f-src

