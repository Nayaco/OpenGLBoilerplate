#ifndef DEMOSCENE_HPP
#define DEMOSCENE_HPP

#include "Core/Common.hpp"
#include "Core/Context/Context.hpp"
#include "Core/GameObjects/Scene/BaseScene.hpp"
#include "Core/GameObjects/Camera/Camera.hpp"
#include "Core/Graphics/Mesh/TerrainMesh/TerrainMesh.hpp"
#include "Core/ResourceManager/ResourceManager.hpp"
#include "Core/Input/Input.hpp"
#include "Core/GameObjects/Skymap/Skymap.hpp"
#include "Core/GameObjects/Skybox/Skybox.hpp"
#include "Core/GameObjects/Terrain/Terrain.hpp"
#include "Core/GameObjects/Grass/GrassBlade.h"

#include "DemoSceneConfig.hpp"
#include "Core/ExceptionHandle/ErrLog.hpp"

#include "Components/Tests/Noisemap/Noisemap.hpp"

class DemoScene : public BaseScene {
public:
    Terrain *terrain;
    Terrain *terrain2;
    Terrain *terrain3;
    Terrain *terrain4;
    TerrainMesh *mesh;
    GrassBlade *grass;

    Skymap *skymap;
    Skybox *skybox;
    Camera *cam;
    
    NPMT *testmap;

    int screen_width;
    int screen_height;
    float cut_near = 0.1f;
    float cut_far = 1000.0f;
    bool firstMouse = true;
    float lastX = 0.0f;
    float lastY = 0.0f;
    std::function<void(float, float)> mmove;
    std::function<void(float)> mscroll;
    std::function<void()> kup;
    std::function<void()> kdn;
    std::function<void()> klf;
    std::function<void()> krt;
    
    DemoScene();

    virtual void initialize() override;
    virtual void draw() const override;
    virtual void destroy() override;
    virtual void update() override;
    
    void mouseMovecallback(float xpos, float ypos);
    void scrollcallback(float yoffset);

    void keyUp();
    void keyDown();
    void keyLeft();
    void keyRight();
};

#endif