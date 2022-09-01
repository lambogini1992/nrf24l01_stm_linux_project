

cmake_minimum_required(VERSION 3.13.0)
set(CMAKE_TOOLCHAIN_FILE "cmake/toolchain-arm-none-eabi.cmake")

project(Sidekick C ASM CXX)

# Set directories
set(LINKER_SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/linker_script)
set(PREBUILD_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(PROJECT_DIR       ${CMAKE_CURRENT_SOURCE_DIR}/../..)

# Project type definition
if(PROJECT_TYPE)
    message(STATUS "PROJECT_TYPE: ${PROJECT_TYPE}")
    add_definitions(-DPROJECT_TYPE=${PROJECT_TYPE})
endif(PROJECT_TYPE)

# Include
if(PROJECT_TYPE STREQUAL "Sidekick_Customer")
    include("cmake/gen7/config.cmake")
    include("cmake/gen7/source.cmake")
    include("cmake/gen7/compile.cmake")
elseif(PROJECT_TYPE STREQUAL "Sidekick_Factory")
    include("cmake/gen7_factory/config.cmake")
    include("cmake/gen7_factory/source.cmake")
    include("cmake/gen7_factory/compile.cmake")
elseif(PROJECT_TYPE STREQUAL "Cardinal_Factory")
    include("cmake/cardinal_factory/config.cmake")
    include("cmake/cardinal_factory/source.cmake")
    include("cmake/cardinal_factory/compile.cmake")
else()
    message(FATAL_ERROR "Please input project type")
endif()

include("cmake/link.cmake")

if(PROJECT_TYPE STREQUAL "Cardinal_Factory")
    if(BUILD_TYPE STREQUAL "Release")
        # Board version definition
        if(BOARD_VERSION)
            message(STATUS "BOARD_VERSION: ${BOARD_VERSION}")
            add_definitions(-DBOARD_VERSION=${BOARD_VERSION})
        endif(BOARD_VERSION)

        if(BOOTLOADER_CONFIGURATION_CLOCK_ENABLE)
            message(STATUS "BOOTLOADER_CONFIGURATION_CLOCK_ENABLE: ${BOOTLOADER_CONFIGURATION_CLOCK_ENABLE}")
            add_definitions(-DBOOTLOADER_CONFIGURATION_CLOCK_ENABLE=${BOOTLOADER_CONFIGURATION_CLOCK_ENABLE})
        endif(BOOTLOADER_CONFIGURATION_CLOCK_ENABLE)

        # Build and link second application named Cardinal (placed at the second region)
        add_executable(Cardinal_OTA ${MAIN_C} ${MAIN_SRCS_FILES} ${OTHER_SRCS_FILES} ${CUSTOM_OBJ})
        target_link_options(Cardinal_OTA BEFORE PUBLIC "-T${LINKER_SCRIPT_DIR}/Cardinal.ld")
        set_target_properties(
            Cardinal_OTA
            PROPERTIES
                OUTPUT_NAME "Cardinal_OTA"
                SUFFIX ".axf"
                RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

        # start-group and end-group are used for linking cycling dependend libraries for Sidekick2 application
        target_link_libraries(Cardinal_OTA "-Wl,--start-group" ${LIBS} "-Wl,--end-group")

        # Create Sidekick2 binary file from axf
        add_custom_command(
            TARGET Cardinal_OTA
            POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${BUILD_OUTPUT_DIR}/Cardinal_OTA.axf ${BUILD_OUTPUT_DIR}/Cardinal_OTA.bin
            COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${BUILD_OUTPUT_DIR}/Cardinal_OTA.axf ${BUILD_OUTPUT_DIR}/Cardinal_OTA.hex)

        # Run post-build script to create full Sidekick image for OTA and flashing directly
        add_custom_target(
            run ALL
            COMMAND ${PYTHON3_PATH}/python3 ${PROJECT_DIR}/Sources/Scripts/post_build_scripts/CA_postbuild_sidekick.py --proj_type=${PROJECT_TYPE} --build_out_path=${POST_BUILD_OUT} --post_build_out_path=${POST_BUILD_OUT} --target=${BOARD_VERSION} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            DEPENDS Cardinal_OTA)

        # Build and link second application named Cardinal (placed at the second region)
        add_executable(Cardinal ${MAIN_C} ${MAIN_SRCS_FILES} ${OTHER_SRCS_FILES} ${CUSTOM_OBJ})
        target_link_options(Cardinal BEFORE PUBLIC "-T${LINKER_SCRIPT_DIR}/Cardinal_Debug.ld")
        set_target_properties(
            Cardinal
            PROPERTIES
                OUTPUT_NAME "Cardinal"
                SUFFIX ".axf"
                RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

        # start-group and end-group are used for linking cycling dependend libraries for Sidekick2 application
        target_link_libraries(Cardinal "-Wl,--start-group" ${LIBS} "-Wl,--end-group")

        # Create Sidekick2 binary file from axf
        add_custom_command(
            TARGET Cardinal
            POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${BUILD_OUTPUT_DIR}/Cardinal.axf ${BUILD_OUTPUT_DIR}/Cardinal.bin
            COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${BUILD_OUTPUT_DIR}/Cardinal.axf ${BUILD_OUTPUT_DIR}/Cardinal.hex)

    else()
        # Board version definition
        if(BOARD_VERSION)
            message(STATUS "BOARD_VERSION: ${BOARD_VERSION}")
            add_definitions(-DBOARD_VERSION=${BOARD_VERSION})
        endif(BOARD_VERSION)

        if(BOOTLOADER_CONFIGURATION_CLOCK_ENABLE)
            message(STATUS "BOOTLOADER_CONFIGURATION_CLOCK_ENABLE: ${BOOTLOADER_CONFIGURATION_CLOCK_ENABLE}")
            add_definitions(-DBOOTLOADER_CONFIGURATION_CLOCK_ENABLE=${BOOTLOADER_CONFIGURATION_CLOCK_ENABLE})
        endif(BOOTLOADER_CONFIGURATION_CLOCK_ENABLE)

        # Build and link second application named Cardinal (placed at the second region)
        add_executable(Cardinal_OTA ${MAIN_C} ${MAIN_SRCS_FILES} ${OTHER_SRCS_FILES} ${CUSTOM_OBJ})
        target_link_options(Cardinal_OTA BEFORE PUBLIC "-T${LINKER_SCRIPT_DIR}/Cardinal.ld")
        set_target_properties(
            Cardinal_OTA
            PROPERTIES
                OUTPUT_NAME "Cardinal_OTA"
                SUFFIX ".axf"
                RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

        # start-group and end-group are used for linking cycling dependend libraries for Sidekick2 application
        target_link_libraries(Cardinal_OTA "-Wl,--start-group" ${LIBS} "-Wl,--end-group")

        # Create Sidekick2 binary file from axf
        add_custom_command(
            TARGET Cardinal_OTA
            POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${BUILD_OUTPUT_DIR}/Cardinal_OTA.axf ${BUILD_OUTPUT_DIR}/Cardinal_OTA.bin
            COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${BUILD_OUTPUT_DIR}/Cardinal_OTA.axf ${BUILD_OUTPUT_DIR}/Cardinal_OTA.hex)

        # Run post-build script to create full Sidekick image for OTA and flashing directly
        add_custom_target(
            run ALL
            COMMAND ${PYTHON3_PATH}/python3 ${PROJECT_DIR}/Sources/Scripts/post_build_scripts/CA_postbuild_sidekick.py --proj_type=${PROJECT_TYPE} --build_out_path=${POST_BUILD_OUT} --post_build_out_path=${POST_BUILD_OUT} --target=${BOARD_VERSION} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            DEPENDS Cardinal_OTA)

        # Build and link second application named Cardinal (placed at the second region)
        add_executable(Cardinal ${MAIN_C} ${MAIN_SRCS_FILES} ${OTHER_SRCS_FILES} ${CUSTOM_OBJ})
        target_link_options(Cardinal BEFORE PUBLIC "-T${LINKER_SCRIPT_DIR}/Cardinal_Debug.ld")
        set_target_properties(
            Cardinal
            PROPERTIES
                OUTPUT_NAME "Cardinal"
                SUFFIX ".axf"
                RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

        # start-group and end-group are used for linking cycling dependend libraries for Sidekick2 application
        target_link_libraries(Cardinal "-Wl,--start-group" ${LIBS} "-Wl,--end-group")

        # Create Sidekick2 binary file from axf
        add_custom_command(
            TARGET Cardinal
            POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${BUILD_OUTPUT_DIR}/Cardinal.axf ${BUILD_OUTPUT_DIR}/Cardinal.bin
            COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${BUILD_OUTPUT_DIR}/Cardinal.axf ${BUILD_OUTPUT_DIR}/Cardinal.hex)
    endif()
else()
    # Board version definition
    if(BOARD_VERSION)
        message(STATUS "BOARD_VERSION: ${BOARD_VERSION}")
        add_definitions(-DBOARD_VERSION=${BOARD_VERSION})
    endif(BOARD_VERSION)

    # Build and link first application named Sidekick1 (placed at the first region)
    add_executable(Sidekick1 ${MAIN_C} ${MAIN_SRCS_FILES} ${OTHER_SRCS_FILES} ${CUSTOM_OBJ})
    target_link_options(Sidekick1 BEFORE PUBLIC "-T${LINKER_SCRIPT_DIR}/Sidekick1.ld")
    set_target_properties(
        Sidekick1
        PROPERTIES
            OUTPUT_NAME "Sidekick1"
            SUFFIX ".axf"
            RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

    # start-group and end-group are used for linking cycling dependend libraries for Sidekick1 application
    target_link_libraries(Sidekick1 "-Wl,--start-group" ${LIBS} "-Wl,--end-group")

    # Create Sidekick1 binary file from axf
    add_custom_command(
        TARGET Sidekick1
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${BUILD_OUTPUT_DIR}/Sidekick1.axf ${BUILD_OUTPUT_DIR}/Sidekick1.bin)

    # Build and link second application named Sidekick2 (placed at the second region)
    add_executable(Sidekick2 ${MAIN_C} ${MAIN_SRCS_FILES} ${OTHER_SRCS_FILES} ${CUSTOM_OBJ})
    target_link_options(Sidekick2 BEFORE PUBLIC "-T${LINKER_SCRIPT_DIR}/Sidekick2.ld")
    set_target_properties(
        Sidekick2
        PROPERTIES
            OUTPUT_NAME "Sidekick2"
            SUFFIX ".axf"
            RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

    # start-group and end-group are used for linking cycling dependend libraries for Sidekick2 application
    target_link_libraries(Sidekick2 "-Wl,--start-group" ${LIBS} "-Wl,--end-group")

    # Create Sidekick2 binary file from axf
    add_custom_command(
        TARGET Sidekick2
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${BUILD_OUTPUT_DIR}/Sidekick2.axf ${BUILD_OUTPUT_DIR}/Sidekick2.bin)

    # Run post-build script to create full Sidekick image for OTA and flashing directly
    add_custom_target(
        run ALL
        COMMAND ${PYTHON3_PATH}/python3 ${PROJECT_DIR}/Sources/Scripts/post_build_scripts/postbuild_sidekick.py --proj_type=${PROJECT_TYPE} --build_out_path=${POST_BUILD_OUT} --post_build_out_path=${POST_BUILD_OUT} --target=${BOARD_VERSION} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        DEPENDS Sidekick1
        DEPENDS Sidekick2)

endif()
