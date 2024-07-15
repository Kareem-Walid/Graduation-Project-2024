################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Free_RTOS/croutine.c \
../Src/Free_RTOS/event_groups.c \
../Src/Free_RTOS/list.c \
../Src/Free_RTOS/queue.c \
../Src/Free_RTOS/stream_buffer.c \
../Src/Free_RTOS/tasks.c \
../Src/Free_RTOS/timers.c 

OBJS += \
./Src/Free_RTOS/croutine.o \
./Src/Free_RTOS/event_groups.o \
./Src/Free_RTOS/list.o \
./Src/Free_RTOS/queue.o \
./Src/Free_RTOS/stream_buffer.o \
./Src/Free_RTOS/tasks.o \
./Src/Free_RTOS/timers.o 

C_DEPS += \
./Src/Free_RTOS/croutine.d \
./Src/Free_RTOS/event_groups.d \
./Src/Free_RTOS/list.d \
./Src/Free_RTOS/queue.d \
./Src/Free_RTOS/stream_buffer.d \
./Src/Free_RTOS/tasks.d \
./Src/Free_RTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Free_RTOS/%.o Src/Free_RTOS/%.su Src/Free_RTOS/%.cyclo: ../Src/Free_RTOS/%.c Src/Free_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/LIB/STD_TYPES" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/APP/Inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/portable/GCC/ARM_CM3" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Free_RTOS

clean-Src-2f-Free_RTOS:
	-$(RM) ./Src/Free_RTOS/croutine.cyclo ./Src/Free_RTOS/croutine.d ./Src/Free_RTOS/croutine.o ./Src/Free_RTOS/croutine.su ./Src/Free_RTOS/event_groups.cyclo ./Src/Free_RTOS/event_groups.d ./Src/Free_RTOS/event_groups.o ./Src/Free_RTOS/event_groups.su ./Src/Free_RTOS/list.cyclo ./Src/Free_RTOS/list.d ./Src/Free_RTOS/list.o ./Src/Free_RTOS/list.su ./Src/Free_RTOS/queue.cyclo ./Src/Free_RTOS/queue.d ./Src/Free_RTOS/queue.o ./Src/Free_RTOS/queue.su ./Src/Free_RTOS/stream_buffer.cyclo ./Src/Free_RTOS/stream_buffer.d ./Src/Free_RTOS/stream_buffer.o ./Src/Free_RTOS/stream_buffer.su ./Src/Free_RTOS/tasks.cyclo ./Src/Free_RTOS/tasks.d ./Src/Free_RTOS/tasks.o ./Src/Free_RTOS/tasks.su ./Src/Free_RTOS/timers.cyclo ./Src/Free_RTOS/timers.d ./Src/Free_RTOS/timers.o ./Src/Free_RTOS/timers.su

.PHONY: clean-Src-2f-Free_RTOS

