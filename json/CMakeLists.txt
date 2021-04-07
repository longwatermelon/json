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
	include/utils.h
)