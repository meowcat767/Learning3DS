cmake_minimum_required(VERSION 3.10)
project(Learning3DS CXX)

# Use devkitARM compiler
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(DEVKITPRO "/opt/devkitpro" CACHE PATH "")
set(DEVKITARM "${DEVKITPRO}/devkitARM" CACHE PATH "")

set(CMAKE_C_COMPILER   "${DEVKITARM}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${DEVKITARM}/bin/arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "${DEVKITARM}/bin/arm-none-eabi-gcc")

# 3DS specific flags
set(COMMON_FLAGS "-march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=3dsx.specs ${COMMON_FLAGS}")

message(STATUS "DEVKITPRO = ${DEVKITPRO}")

# Include directories for headers
include_directories(
        ${DEVKITPRO}/libctru/include
)

# Add executable (ELF)
add_executable(Learning3DS.elf src/main.cpp)


# Link libraries
link_directories(
        ${DEVKITPRO}/libctru/lib
        ${DEVKITPRO}/portlibs/3ds/lib
)

target_link_libraries(Learning3DS.elf
        ${DEVKITPRO}/libctru/lib/libctru.a
        ${DEVKITPRO}/libctru/lib/libcitro2d.a
        ${DEVKITPRO}/libctru/lib/libcitro3d.a
)

# Post-build command to convert ELF to 3DSX
set(3DSXTOOL "${DEVKITPRO}/tools/bin/3dsxtool")
set(SMDHTOOL "${DEVKITPRO}/tools/bin/smdhtool")

# Convert ELF to 3DSX and embed SMDH
add_custom_command(TARGET Learning3DS.elf POST_BUILD
        COMMAND ${SMDHTOOL} --create "Learning3DS" "Learning 3DS development" "meowcat767" "${DEVKITPRO}/libctru/default_icon.png" ${CMAKE_CURRENT_BINARY_DIR}/Learning3DS.smdh
        COMMAND ${3DSXTOOL} $<TARGET_FILE:Learning3DS.elf> ${CMAKE_CURRENT_BINARY_DIR}/Learning3DS.3dsx --smdh=${CMAKE_CURRENT_BINARY_DIR}/Learning3DS.smdh
        COMMENT "Generating SMDH and converting ELF to 3DSX"
)

