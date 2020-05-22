set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
cmake_minimum_required(VERSION 3.16)
project(FiveInRowClient)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)
if(WIN32)
    link_libraries(Ws2_32 wsock32)
endif()

set(SOURCE_FILES src/launcher/main.cpp)

include_directories(src/lib)
add_subdirectory(src/lib)
add_executable(FiveInRowClient ${SOURCE_FILES})

target_link_libraries(FiveInRowClient FiveInRowClientLib)