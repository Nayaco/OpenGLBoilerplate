# Project definition
cmake_minimum_required(VERSION 3.1)
project(SKYLINE)
set(CMAKE_CXX_STANDARD 11)

if (LINUX) 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lGL -lX11 -lpthread -lXrandr -lXi")
elseif(APPLE)
    link_directories(/usr/local/lib)
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
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)
find_package(Freetype REQUIRED)
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
# set(ASSIMP_DIR "${DEP_DIR}/assimp")
# ---------------------------------------------------------------------------------------------------------------------------#
# Executable definition and properties
set(SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/ExceptionHandle/ErrLog.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameEngine.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Utility/Random.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Utility/Noise/Noise.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Utility/ByteBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Mesh/TerrainMesh/TerrainMesh.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Shader/Shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Texture/Texture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Light/ALight.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Light/PLight.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Font/Font.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Mesh/DefaultMesh/Mesh.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Model/Model.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Physics/AABB/AABBObject.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Context/Context.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Input/Input.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/ResourceManager/ResourceManager.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Skymap/Skymap.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Camera/Camera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Cloud/Cloud.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Skybox/Skybox.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Skybox/EntitySun.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Terrain/Terrain.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Grass/GrassBlade.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/ParticleSystem/ParticleSystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Chunk/Chunk.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/PostProcessing/FirstPass/FirstPass.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/PostProcessing/Bloom/Bloom.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/Components/Scenes/GameScene/GameScene.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Graphics/Framebuffer/FrameBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Tile/WaterGenerator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Tile/WaterRenderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/GameObjects/Tile/WaterTile.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/Components/Plane/Plane.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Components/Tower/Tower.cpp"
    )
# copy to build folder
file(GLOB RESOURCE_FILES "Resources")
file(COPY
        ${RESOURCE_FILES}
        DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
        )

set(EXE_NAME skyline)
set(SYS_INCLUDE /usr/local/include/)
add_executable(${EXE_NAME} ${SOURCES})
include_directories(${SYS_INCLUDE})
target_include_directories(${EXE_NAME} PRIVATE "${INC_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${SRC_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${GLM_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${STB_DIR}")
target_include_directories(${EXE_NAME} PRIVATE "${GLAD_DIR}/include")
target_include_directories(${EXE_NAME} PRIVATE "${FREETYPE_INCLUDE_DIRS}")
    message("OKOK")
target_include_directories(${EXE_NAME} PRIVATE "${ASSIMP_INCLUDE_DIRS}")
target_link_libraries(${EXE_NAME} "${ASSIMP_LIBRARIES}")
target_link_libraries(${EXE_NAME} "glad" "${CMAKE_DL_LIBS}")
target_link_libraries(${EXE_NAME} glfw)
target_compile_definitions(${EXE_NAME} PRIVATE "GLFW_INCLUDE_NONE")
target_link_libraries(${EXE_NAME} IL)
target_link_libraries(${EXE_NAME} "${FREETYPE_LIBRARIES}")
if (APPLE)
    target_link_libraries(${EXE_NAME} "-framework OpenGL")
endif()

#set_property(TARGET ${EXE_NAME} PROPERTY CXX_STANDARD 11)