cmake_minimum_required(VERSION 3.10)
project(matrop)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE 1)

set(SOURCE_PATH "src")
set(MULTIPLY_PATH "${SOURCE_PATH}/multiply")
set(SCAN_PATH     "${SOURCE_PATH}/scan")
set(CONV_PATH     "${SOURCE_PATH}/conv")

set(FRAMEWORK_FILES
        ${SOURCE_PATH}/App.cpp
        ${SOURCE_PATH}/Util.cpp
        ${SOURCE_PATH}/Matrix.cpp
        )

set(MULTIPLY_FILES
        ${MULTIPLY_PATH}/MultiplyApp.cpp
        ${SOURCE_PATH}/Main.cpp
        )

set(SCAN_FILES
        ${SCAN_PATH}/ScanApp.cpp
        ${SOURCE_PATH}/Main.cpp
        )

set(CONV_FILES
        ${CONV_PATH}/ConvApp.cpp
        ${SOURCE_PATH}/Main.cpp
        )

include_directories(${SOURCE_PATH})

if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(INCL_EXTRA_HTON_FUNCTIONS)
    add_compile_definitions(NOMINMAX)
    list(APPEND LIBRARIES ws2_32)
else()
    list(APPEND LIBRARIES pthread)
endif()

add_library(matrop-framework ${FRAMEWORK_FILES})

add_executable(matrop-multiply ${MULTIPLY_FILES})
target_compile_definitions(matrop-multiply PUBLIC -DMULTIPLY)
target_link_libraries(matrop-multiply matrop-framework ${LIBRARIES})

add_executable(matrop-scan ${SCAN_FILES})
target_compile_definitions(matrop-scan PUBLIC -DSCAN)
target_link_libraries(matrop-scan matrop-framework ${LIBRARIES})

add_executable(matrop-conv ${CONV_FILES})
target_compile_definitions(matrop-conv PUBLIC -DCONV)
target_link_libraries(matrop-conv matrop-framework ${LIBRARIES})
