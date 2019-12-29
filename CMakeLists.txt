# Project definition
cmake_minimum_required(VERSION 3.1)
project(SKYLINE)

if (LINUX) 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lGL -lX11 -lpthread -lXrandr -lXi")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lGL -pthread")
endif()

set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Library")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release")
# Source file directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/Core" "${CMAKE_CURRENT_SOURCE_DIR}/Components" "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/Core" "${CMAKE_CURRENT_SOURCE_DIR}/Components" "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
set(DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependences")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Tests")
# ---------------------------------------------------------------------------------------------------------------------------#
# Dependences
# Dependence glfw
find_package(glfw3)
# set(GLFW_DIR "${DEP_DIR}/glfw3")
# set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
# set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
# set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
# set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
# add_subdirectory("${GLFW_DIR}")
# Dependence glad
set(GLAD_DIR "${DEP_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
# Dependence stb_image
set(STB_DIR "${DEP_DIR}")
# Dependence glm
set(GLM_DIR "${DEP_DIR}/glm")
# Dependence assimp
set(ASSIMP_DIR "${DEP_DIR}/assimp")
# ---------------------------------------------------------------------------------------------------------------------------#
# Executable definition and properties
set(SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/ExceptionHandle/ErrLog.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameEngine.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Utility/Random.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Utility/Noise/Noise.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Mesh/TerrainMesh/TerrainMesh.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Shader/Shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Texture/Texture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Light/ALight.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Light/PLight.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Context/Context.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Input/Input.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/ResourceManager/ResourceManager.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Skymap/Skymap.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Camera/Camera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Skybox/Skybox.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Skybox/EntitySun.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Terrain/Terrain.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Grass/GrassBlade.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/ParticleSystem/ParticleSystem.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Core/PostProcessing/FirstPass/FirstPass.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Components/Scenes/GameScene/GameScene.cpp"
    # "${CMAKE_CURRENT_SOURCE_DIR}/Components/Scenes/Demo/DemoScene.cpp"
    )
set(EXE_NAME skyline)
add_executable(${EXE_NAME} ${SOURCES})
target_include_directories(${EXE_NAME} PRIVATE "${INC_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${SRC_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${GLM_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${STB_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${GLAD_DIR}/include")
target_include_directories(${EXE_NAME} PRIVATE "${ASSIMP_DIR}/include")
# target_include_directories(${EXE_NAME} PRIVATE "${GLFW_DIR}/include")
target_link_libraries(${EXE_NAME} "glad" "${CMAKE_DL_LIBS}")
# target_link_libraries(${EXE_NAME} "glfw" "${GLFW_LIBRARIES}")
target_link_libraries(${EXE_NAME} glfw)
target_link_libraries(${EXE_NAME} "${ASSIMP_DIR}/lib/libassimp.so.5.0.0")
target_compile_definitions(${EXE_NAME} PRIVATE "GLFW_INCLUDE_NONE")
set_property(TARGET ${EXE_NAME} PROPERTY CXX_STANDARD 11)