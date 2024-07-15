################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/src/Encoder.c \
../Src/HAL/src/ULTRASONIC.c 

OBJS += \
./Src/HAL/src/Encoder.o \
./Src/HAL/src/ULTRASONIC.o 

C_DEPS += \
./Src/HAL/src/Encoder.d \
./Src/HAL/src/ULTRASONIC.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/src/%.o Src/HAL/src/%.su Src/HAL/src/%.cyclo: ../Src/HAL/src/%.c Src/HAL/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/APP/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/freeRTOS/portable/GCC/ARM_CM4F" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/freeRTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-src

clean-Src-2f-HAL-2f-src:
	-$(RM) ./Src/HAL/src/Encoder.cyclo ./Src/HAL/src/Encoder.d ./Src/HAL/src/Encoder.o ./Src/HAL/src/Encoder.su ./Src/HAL/src/ULTRASONIC.cyclo ./Src/HAL/src/ULTRASONIC.d ./Src/HAL/src/ULTRASONIC.o ./Src/HAL/src/ULTRASONIC.su

.PHONY: clean-Src-2f-HAL-2f-src

