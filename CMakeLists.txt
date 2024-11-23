cmake_minimum_required(VERSION 3.30)

project(TestForCMake)

aux_source_directory(./src SRCS)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SRCS})