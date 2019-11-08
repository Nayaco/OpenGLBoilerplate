# cg tutorial lesson-9
cmake_minimum_required(VERSION 3.1)
project(9-material)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lGL -lX11 -lpthread -lXrandr -lXi")

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SOURCES "${SRC_DIR}/main.cpp")


# Excutable defininition and properties 
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${INC_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}")

# GLFW 
set(GLFW_DIR "${LIB_DIR}/GLFW")
target_link_libraries(${PROJECT_NAME} "${GLFW_DIR}/src/libglfw3.a")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_subdirectory(${GLAD_DIR} ${GLAD_DIR})
# add_library(glad "${GLAD_DIR}/src/glad.c")
# target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} glad "${CMAKE_DL_LIBS}")

#assimp
set(ASSIMP_DIR "${LIB_DIR}/assimp")
target_include_directories(${PROJECT_NAME} PRIVATE "${ASSIMP_DIR}/include")
target_link_libraries(${PROJECT_NAME} "${ASSIMP_DIR}/lib/libassimp.so.5.0.0")

# stb
set(STB_DIR "${LIB_DIR}/stb")
target_include_directories(${PROJECT_NAME} PRIVATE "${STB_DIR}")

