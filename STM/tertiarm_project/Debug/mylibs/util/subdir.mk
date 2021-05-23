################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mylibs/util/DWT_Delay.c \
../mylibs/util/button.c \
../mylibs/util/filter.c 

C_DEPS += \
./mylibs/util/DWT_Delay.d \
./mylibs/util/button.d \
./mylibs/util/filter.d 

OBJS += \
./mylibs/util/DWT_Delay.o \
./mylibs/util/button.o \
./mylibs/util/filter.o 


# Each subdirectory must supply rules for building sources it contributes
mylibs/util/DWT_Delay.o: ../mylibs/util/DWT_Delay.c mylibs/util/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I/home/roser/Documents/stm32/deb_stm_files/C8_try/ros_lib -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/SERVO -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/util -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/JOYSTICK -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"mylibs/util/DWT_Delay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
mylibs/util/button.o: ../mylibs/util/button.c mylibs/util/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I/home/roser/Documents/stm32/deb_stm_files/C8_try/ros_lib -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/SERVO -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/util -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/JOYSTICK -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"mylibs/util/button.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
mylibs/util/filter.o: ../mylibs/util/filter.c mylibs/util/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I/home/roser/Documents/stm32/deb_stm_files/C8_try/ros_lib -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/SERVO -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/util -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/JOYSTICK -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"mylibs/util/filter.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

