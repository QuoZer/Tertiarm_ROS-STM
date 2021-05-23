################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mylibs/SERVO/SERVO.c \
../mylibs/SERVO/SERVO_cfg.c 

C_DEPS += \
./mylibs/SERVO/SERVO.d \
./mylibs/SERVO/SERVO_cfg.d 

OBJS += \
./mylibs/SERVO/SERVO.o \
./mylibs/SERVO/SERVO_cfg.o 


# Each subdirectory must supply rules for building sources it contributes
mylibs/SERVO/SERVO.o: ../mylibs/SERVO/SERVO.c mylibs/SERVO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I/home/roser/Documents/stm32/deb_stm_files/C8_try/ros_lib -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/SERVO -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/util -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/JOYSTICK -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"mylibs/SERVO/SERVO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
mylibs/SERVO/SERVO_cfg.o: ../mylibs/SERVO/SERVO_cfg.c mylibs/SERVO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I/home/roser/Documents/stm32/deb_stm_files/C8_try/ros_lib -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/SERVO -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/util -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/JOYSTICK -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"mylibs/SERVO/SERVO_cfg.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

