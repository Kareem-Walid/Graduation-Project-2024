################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/freeRTOS/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./Src/freeRTOS/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./Src/freeRTOS/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
Src/freeRTOS/portable/GCC/ARM_CM4F/%.o Src/freeRTOS/portable/GCC/ARM_CM4F/%.su Src/freeRTOS/portable/GCC/ARM_CM4F/%.cyclo: ../Src/freeRTOS/portable/GCC/ARM_CM4F/%.c Src/freeRTOS/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/APP/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/freeRTOS/portable/GCC/ARM_CM4F" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/freeRTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-freeRTOS-2f-portable-2f-GCC-2f-ARM_CM4F

clean-Src-2f-freeRTOS-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./Src/freeRTOS/portable/GCC/ARM_CM4F/port.cyclo ./Src/freeRTOS/portable/GCC/ARM_CM4F/port.d ./Src/freeRTOS/portable/GCC/ARM_CM4F/port.o ./Src/freeRTOS/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-Src-2f-freeRTOS-2f-portable-2f-GCC-2f-ARM_CM4F

