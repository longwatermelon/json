cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(json)

add_library(json
  src/json.cpp
  src/lexer.cpp
  src/parser.cpp
  include/json.h
  include/token.h
  include/lexer.h
  include/node.h
  include/parser.h
)

project(example)
add_executable(example
  example.cpp
)

set_property(TARGET example PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries(example json)