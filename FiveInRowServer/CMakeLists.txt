cmake_minimum_required(VERSION 3.14)
project(FiveInRowServer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

if(WIN32)
link_libraries(ws2_32 wsock32)
endif()

set(SOURCE_FILES src/launcher/main.cpp)

include_directories(src/lib)
add_subdirectory(src/lib)
add_executable(FiveInRowServer ${SOURCE_FILES})

target_link_libraries(FiveInRowServer FiveInRowServerLib)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "server")
add_subdirectory(tests)