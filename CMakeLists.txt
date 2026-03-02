cmake_minimum_required(VERSION 3.22)

project(
    AMLL
    VERSION 0.0.1
    DESCRIPTION "AMLL (Another Machine Learning Library)"
    LANGUAGES C
)

# C standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Generate compile_commands.json for vscode intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type is Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Summary
message(STATUS "")
message(STATUS "===============================")
message(STATUS "Build:      ${CMAKE_BUILD_TYPE}")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Generator:  ${CMAKE_GENERATOR}")
message(STATUS "===============================")
message(STATUS "")

# Backend options
set(AMLL_BACKEND "CPU_NAIVE" CACHE STRING "Choose AMLL Backend")
set_property(CACHE AMLL_BACKEND PROPERTY STRINGS "CPU_NAIVE" "CPU_SIMD" "CPU_MT" "GPU")

# Lib type options
set(AMLL_LIB_TYPE "STATIC" CACHE STRING "Build AMLL as")
set_property(CACHE AMLL_LIB_TYPE PROPERTY STRINGS "STATIC" "SHARED")

message(STATUS "")
message(STATUS "===============================")
message(STATUS "Building AMLL library ...")

# Sources
set(AMLL_SOURCES
    src/core/error.c
)

# Backend sources and definitions
message(STATUS "AMLL Backend:   ${AMLL_BACKEND}")
if(AMLL_BACKEND STREQUAL "CPU_NAIVE")
    set(AMLL_BACKEND_SOURCES)
    set(AMLL_BACKEND_DEFS AMLL_BACKEND_CPU_NAIVE=1)

elseif(AMLL_BACKEND STREQUAL "CPU_SIMD")
    set(AMLL_BACKEND_SOURCES)
    set(AMLL_BACKEND_DEFS AMLL_BACKEND_CPU_SIMD=1)

elseif(AMLL_BACKEND STREQUAL "CPU_MT")
    set(AMLL_BACKEND_SOURCES)
    set(AMLL_BACKEND_DEFS AMLL_BACKEND_CPU_MT=1)

else() # GPU
    set(AMLL_BACKEND_SOURCES)
    set(AMLL_BACKEND_DEFS AMLL_BACKEND_GPU=1)

endif()

# Library creation
message(STATUS "AMLL Lib type:  ${AMLL_LIB_TYPE}")
add_library(amll ${AMLL_LIB_TYPE} ${AMLL_SOURCES} ${AMLL_BACKEND_SOURCES})

target_compile_definitions(amll PRIVATE ${AMLL_BACKEND_DEFS})
target_include_directories(amll PRIVATE include)
target_compile_options(amll PRIVATE
    -Wall
    -Wextra
    -pedantic
)

message(STATUS "===============================")
message(STATUS "")