cmake_minimum_required(VERSION 3.14)

project(c_sortResearch)

set(INCLUDE_DIR include)
set(SRC_DIR src)

set(JSON_LIB ${SRC_DIR}/cJSON.c)
set(SRC_FILES ${SRC_DIR}/main.c ${SRC_DIR}/sorting.c ${SRC_DIR}/testing.c)
set(HEADERS ${INCLUDE_DIR}/sorting.h ${INCLUDE_DIR}/testing.h)

include_directories(${INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SRC_FILES} ${JSON_LIB} ${HEADERS})