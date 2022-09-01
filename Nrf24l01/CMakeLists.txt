# Template CMakeLists.txt configuration for STM32 MCUS
cmake_minimum_required(VERSION 3.12)
# ##############################################################################
# Edit your MCU information up to the next border
project(nrf24l01)
set(PROJECT_DIR output)

include(${CMAKE_CURRENT_SOURCE_DIR}/gcc-arm-none-eabi.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/source.cmake)

set(PROJECT_OUTPUT_PATH /build_outputs)
if(DEFINED PROJECT_OUTPUT_PATH)
    set(BUILD_OUTPUT_DIR  ${PROJECT_OUTPUT_PATH})
else()
    set(BUILD_OUTPUT_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_TYPE}/build_outputs)
endif()

set(MCU_FAMILY STM32F1xx)
set(MCU_MODEL STM32F103x6)
set(CPU_PARAMETERS
    -mcpu=cortex-m3
    )
# Some default GCC settings
set(FLAGS
    "-fdata-sections -ffunction-sections \
    --specs=nano.specs -Wl,--gc-sections")
set(CPP_FLAGS
    "-fno-rtti -fno-exceptions \
    -fno-threadsafe-statics")


set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f103x6.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F103R6Hx_FLASH.ld)
# ##############################################################################
set(EXECUTABLE ${CMAKE_PROJECT_NAME})
# enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Executable files
add_executable(${EXECUTABLE}
    ${STM32CUBEMX_SOURCES}
    ${PROJECT_SOURCES}
    ${STARTUP_SCRIPT})

# Embedded macros(defines)
target_compile_definitions(${EXECUTABLE} PRIVATE
    ${MCU_MODEL}
    USE_HAL_DRIVER)

# Add header directories (AFTER add_executable !!)
target_include_directories(${EXECUTABLE} PRIVATE
    ${CUBEMX_INCLUDE_DIRECTORIES}
    ${PROJECT_INCLUDE_DIRECTORIES})

# Compiler and linker options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin)