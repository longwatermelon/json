cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(json)

add_subdirectory(example)
add_subdirectory(json)
add_subdirectory(json-cli)

set_property(TARGET example PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})