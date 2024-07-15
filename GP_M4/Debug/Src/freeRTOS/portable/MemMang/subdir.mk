################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/freeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./Src/freeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./Src/freeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Src/freeRTOS/portable/MemMang/%.o Src/freeRTOS/portable/MemMang/%.su Src/freeRTOS/portable/MemMang/%.cyclo: ../Src/freeRTOS/portable/MemMang/%.c Src/freeRTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/APP/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/freeRTOS/portable/GCC/ARM_CM4F" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/freeRTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-freeRTOS-2f-portable-2f-MemMang

clean-Src-2f-freeRTOS-2f-portable-2f-MemMang:
	-$(RM) ./Src/freeRTOS/portable/MemMang/heap_4.cyclo ./Src/freeRTOS/portable/MemMang/heap_4.d ./Src/freeRTOS/portable/MemMang/heap_4.o ./Src/freeRTOS/portable/MemMang/heap_4.su

.PHONY: clean-Src-2f-freeRTOS-2f-portable-2f-MemMang

