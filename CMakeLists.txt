cmake_minimum_required(VERSION 3.11)

project(A1)

include(ExternalProject)

# Set install directory
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist CACHE PATH ${CMAKE_SOURCE_DIR}/dist FORCE)
if (WIN32)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug;Release" FORCE)
endif ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

include(BuildGLEW)
include(BuildGLFW)
include(BuildGLM)

set(EXEC A1)

file(GLOB SRC src/*.cpp src/*/*.cpp src/*/*.h)

add_executable(${EXEC} ${SRC} src/inputs/inputs.cpp src/inputs/inputs.h src/Cube/Cube.cpp src/Cube/Cube.h src/Shaders/shaders.cpp src/Shaders/shaders.h src/sources/generalShader/GeneralShader.cpp src/sources/generalShader/GeneralShader.h)

target_link_libraries(${EXEC} OpenGL::GL glew_s glfw glm)

list(APPEND BIN ${EXEC})

# install files to install location
install(TARGETS ${BIN} DESTINATION ${CMAKE_INSTALL_PREFIX})


