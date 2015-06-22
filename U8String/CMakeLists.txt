cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Wextra -pedantic -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wredundant-decls -Winit-self -Wundef -Winline")

set(SRC_DIR "src/")
set(INC_DIR "include/")
set(TESTS_DIR "Tests/")

file(
		GLOB
		SOURCE
		${SRC_DIR}*.cpp
)

file(
		GLOB
		Tests
		main.cpp
		${TESTS_DIR}*.cpp
)

set(SOURCES_TESTS ${Tests})

set(CATCH "extlibs/Catch/")
set(UTF8 "extlibs/utf8_v2_3_4/source")

set(EXETESTS "TestUTF8")
message(STATUS "Add executable ${EXETESTS}")
include_directories(${INC_DIR} ${CATCH} ${UTF8})
add_executable(${EXETESTS} ${SOURCE} ${SOURCES_TESTS})
