################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/freeRTOS/croutine.c \
../Src/freeRTOS/event_groups.c \
../Src/freeRTOS/list.c \
../Src/freeRTOS/queue.c \
../Src/freeRTOS/stream_buffer.c \
../Src/freeRTOS/tasks.c \
../Src/freeRTOS/timers.c 

OBJS += \
./Src/freeRTOS/croutine.o \
./Src/freeRTOS/event_groups.o \
./Src/freeRTOS/list.o \
./Src/freeRTOS/queue.o \
./Src/freeRTOS/stream_buffer.o \
./Src/freeRTOS/tasks.o \
./Src/freeRTOS/timers.o 

C_DEPS += \
./Src/freeRTOS/croutine.d \
./Src/freeRTOS/event_groups.d \
./Src/freeRTOS/list.d \
./Src/freeRTOS/queue.d \
./Src/freeRTOS/stream_buffer.d \
./Src/freeRTOS/tasks.d \
./Src/freeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/freeRTOS/%.o Src/freeRTOS/%.su Src/freeRTOS/%.cyclo: ../Src/freeRTOS/%.c Src/freeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/APP/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/freeRTOS/portable/GCC/ARM_CM4F" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/freeRTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-freeRTOS

clean-Src-2f-freeRTOS:
	-$(RM) ./Src/freeRTOS/croutine.cyclo ./Src/freeRTOS/croutine.d ./Src/freeRTOS/croutine.o ./Src/freeRTOS/croutine.su ./Src/freeRTOS/event_groups.cyclo ./Src/freeRTOS/event_groups.d ./Src/freeRTOS/event_groups.o ./Src/freeRTOS/event_groups.su ./Src/freeRTOS/list.cyclo ./Src/freeRTOS/list.d ./Src/freeRTOS/list.o ./Src/freeRTOS/list.su ./Src/freeRTOS/queue.cyclo ./Src/freeRTOS/queue.d ./Src/freeRTOS/queue.o ./Src/freeRTOS/queue.su ./Src/freeRTOS/stream_buffer.cyclo ./Src/freeRTOS/stream_buffer.d ./Src/freeRTOS/stream_buffer.o ./Src/freeRTOS/stream_buffer.su ./Src/freeRTOS/tasks.cyclo ./Src/freeRTOS/tasks.d ./Src/freeRTOS/tasks.o ./Src/freeRTOS/tasks.su ./Src/freeRTOS/timers.cyclo ./Src/freeRTOS/timers.d ./Src/freeRTOS/timers.o ./Src/freeRTOS/timers.su

.PHONY: clean-Src-2f-freeRTOS

