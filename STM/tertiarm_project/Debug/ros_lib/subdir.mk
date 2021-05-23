################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ros_lib/duration.cpp \
../ros_lib/time.cpp 

OBJS += \
./ros_lib/duration.o \
./ros_lib/time.o 

CPP_DEPS += \
./ros_lib/duration.d \
./ros_lib/time.d 


# Each subdirectory must supply rules for building sources it contributes
ros_lib/duration.o: ../ros_lib/duration.cpp ros_lib/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I/home/roser/Documents/stm32/deb_stm_files/C8_try/ros_lib -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/SERVO -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/util -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/JOYSTICK -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"ros_lib/duration.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ros_lib/time.o: ../ros_lib/time.cpp ros_lib/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I/home/roser/Documents/stm32/deb_stm_files/C8_try/ros_lib -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/SERVO -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/util -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/JOYSTICK -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"ros_lib/time.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

