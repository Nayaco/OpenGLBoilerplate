# GL AD
cmake_minimum_required(VERSION 3.1)

message("compiling glad library...")

add_library("glad" "${GLAD_DIR}/src/glad.c")

target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")