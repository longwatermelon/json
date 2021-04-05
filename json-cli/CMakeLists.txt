project(json-cli)

add_executable(json-cli
	src/main.cpp
	src/args.cpp
	include/args.h
)

target_link_libraries(json-cli json)
target_include_directories(json-cli PUBLIC ${CMAKE_SOURCE_DIR})