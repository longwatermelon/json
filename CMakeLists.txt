cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(example)
add_executable(example
  example.cpp
)

add_subdirectory(json)

set_property(TARGET example PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries(example json)