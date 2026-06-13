# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Overboard C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_library(ili9341
	ili9341.c
)

add_subdirectory(lvgl-master)

target_include_directories(ili9341 PUBLIC ${CMAKE_CURRENT_LIST_DIR})


# Add executable. Default name is the project name, version 0.1

add_executable(Overboard Overboard.cpp
                uart_control.cpp
                spi_control.cpp
                total_init.cpp
                i2c_control.cpp
                ili9341.c
                encoder_control.cpp
                usb_descriptors.c
                encoder_actions.cpp
                encoder_manager.cpp
                song_info.cpp
                lvgl_helper.cpp
                ws2812.cpp
                )

pico_set_program_name(Overboard "Overboard")
pico_set_program_version(Overboard "0.1")

# Generate PIO header
pico_generate_pio_header(Overboard ${CMAKE_CURRENT_LIST_DIR}/blink.pio)
pico_generate_pio_header(Overboard
    ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Overboard 0)
pico_enable_stdio_usb(Overboard 1)

# Add the standard library to the build
target_link_libraries(Overboard
        pico_stdlib
        )

target_link_libraries(ili9341 
    pico_stdlib 
    hardware_spi 
    hardware_dma
)

# Add the standard include files to the build
target_include_directories(Overboard PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/lvgl-master
)

# Add any user requested libraries
target_link_libraries(Overboard 
        hardware_uart
        hardware_spi
        hardware_i2c
        hardware_pio
        hardware_dma
        hardware_irq
        ili9341
        lvgl
        tinyusb_device
        pico_multicore
        )
pico_add_extra_outputs(Overboard)
