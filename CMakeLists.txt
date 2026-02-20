cmake_minimum_required(VERSION 3.16)
project(Learning3DS)

set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/devkitpro/libctru/include)
include_directories(/opt/devkitpro/citro2d/include)
link_directories(/opt/devkitpro/libctru/lib)
link_directories(/opt/devkitpro/citro2d/lib)
target_link_libraries(${PROJECT_NAME}.3dsx ctru citro3d citro2d)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Build 3DS executable
add_executable(${PROJECT_NAME}.3dsx ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}.3dsx ctru citro3d citro2d)