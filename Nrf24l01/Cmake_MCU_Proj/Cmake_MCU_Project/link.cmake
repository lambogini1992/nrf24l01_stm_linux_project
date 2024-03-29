link_directories(
    "${PROJECT_DIR}/Sources/Modules/algorithms/ohr/lifeq_lib"
    "${PROJECT_DIR}/Third_Parties/microej/platform/lib"
    "${PREBUILD_LIBS_DIR}"
)

unset(main_src)
unset(other_src)
set(LIBS
    ":MicroJvm.a"
    ":bestfitAllocator.a"
    ":display.a"
    ":display_decoder_bmpm.a"
    ":display_decoder_png.a"
    ":display_extra.a"
    ":display_noloader.a"
    ":external-resource-loader-stub.a"
    ":input.a"
    ":leds.a"
    ":logger.a"
    ":microui_queue.a"
    ":rt.a"
    ":sni.a"
)

add_link_options(
    "-nostdlib"
    "-Wl,-Map=${CMAKE_PROJECT_NAME}.map"
    "-Wl,--gc-sections"
    "-Wl,--cref"
    "-Wl,-print-memory-usage"
    "-Wl,--sort-section=alignment"
    "-mcpu=cortex-m33"
    "-mfpu=fpv5-sp-d16"
    "-mfloat-abi=hard"
    "-mthumb"
)

set(CUSTOM_OBJ
    "${PROJECT_DIR}/Third_Parties/microej/platform/lib/microejapp.o"
    "${PREBUILD_LIBS_DIR}/crtbegin.o"
    "${PREBUILD_LIBS_DIR}/crtend.o"
    "${PREBUILD_LIBS_DIR}/crti.o"
    "${PREBUILD_LIBS_DIR}/crtn.o")
