project(example)

add_executable(example
	example.cpp
)

target_link_libraries(example json)
target_include_directories(example PUBLIC ${CMAKE_SOURCE_DIR})