cmake_minimum_required(VERSION 3.6)
project(SQLiteCppDemo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories ("${PROJECT_SOURCE_DIR}/SQLiteCpp")
add_subdirectory (SQLiteCpp)
set (LIBS ${LIBS} SQLiteCpp sqlite3)

set(SOURCE_FILES main.cpp)
add_executable(SQLiteCppDemo ${SOURCE_FILES})
target_link_libraries (SQLiteCppDemo  ${LIBS})