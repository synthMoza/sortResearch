cmake_minimum_required(VERSION 3.14)

project(cpp_sortResearch)

set(INCLUDE_DIR include)
set(SRC_DIR src)

set(SRC_FILES ${SRC_DIR}/main.cpp ${SRC_DIR}/sorting.cpp)
set(HEADERS ${INCLUDE_DIR}/sorting.hpp)

include_directories(${INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SRC_FILES} ${JSON_LIB} ${HEADERS})