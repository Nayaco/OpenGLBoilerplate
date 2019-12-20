# Project definition
cmake_minimum_required(VERSION 3.1)
project(SKYLINE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lGL -lX11 -lpthread -lXrandr -lXi")
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Library")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release")
# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Core" "${CMAKE_CURRENT_SOURCE_DIR}/Components" "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Core" "${CMAKE_CURRENT_SOURCE_DIR}/Components" "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
set(DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependences")
# ---------------------------------------------------------------------------------------------------------------------------#
# Dependences
# glfw
set(GLFW_DIR "${DEP_DIR}/glfw3")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
# glad
set(GLAD_DIR "${DEP_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
# stb_image
set(STB_DIR "${DEP_DIR}/stb")
# glm
set(GLM_DIR "${DEP_DIR}/glm")
# ---------------------------------------------------------------------------------------------------------------------------#
# Executable definition and properties
set(SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp"
    )
set(EXE_NAME skyline)
add_executable(${EXE_NAME} ${SOURCES})
target_include_directories(${EXE_NAME} PRIVATE "${INC_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${GLM_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${STB_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${GLAD_DIR}/include")
target_include_directories(${EXE_NAME} PRIVATE "${GLFW_DIR}/include")
target_link_libraries(${EXE_NAME} "glad" "${CMAKE_DL_LIBS}")
target_link_libraries(${EXE_NAME} "glfw" "${GLFW_LIBRARIES}")
target_compile_definitions(${EXE_NAME} PRIVATE "GLFW_INCLUDE_NONE")
set_property(TARGET ${EXE_NAME} PROPERTY CXX_STANDARD 11)