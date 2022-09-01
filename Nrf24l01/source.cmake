
# Headers
set(CUBEMX_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/CMSIS_RTOS_V2
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/portable/GCC/ARM_CM3
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core
    )
set(PROJECT_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_DIR})

# Sources
file(GLOB_RECURSE STM32CUBEMX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/freertos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/stm32f1xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/stm32f1xx_hal_msp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_gpio_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_cortex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_flash_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_exti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/stm32f1xx_hal_tim_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/croutine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/stream_buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/CMSIS_RTOS_V2/cmsis_os2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/portable/MemMang/heap_4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/portable/GCC/ARM_CM3/port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/system_stm32f1xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/croutine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/stream_buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/CMSIS_RTOS_V2/cmsis_os2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/portable/MemMang/heap_4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/portable/GCC/ARM_CM3/port.c)
file(GLOB_RECURSE PROJECT_SOURCES FOLLOW_SYMLINKS
    ${PROJECT_DIR}/*.cpp
    ${PROJECT_DIR}/*.c)
