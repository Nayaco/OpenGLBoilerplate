#ifndef DEMPSCENE_HPP
#define DEMOSCENE_HPP

#include "Core/Common.hpp"
#include "Core/Context/Context.hpp"
#include "Core/Scene/BaseScene.hpp"
#include "Core/Camera/Camera.hpp"
#include "Core/Graphics/Mesh/TerrainMesh/TerrainMesh.hpp"
#include "Core/Graphics/Skybox/Skybox.hpp"
#include "Core/ResourceManagers/ShaderManager.hpp"
#include "Core/ResourceManagers/TextureManager.hpp"
#include "Core/Input/Input.hpp"

#include "DemoSceneConfig.hpp"
#include "Core/ExceptionHandle/ErrLog.hpp"
class DemoScene : public BaseScene {
public:
    TerrainMesh *mesh;
    Skybox *skybox;
    Camera *cam;
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
    virtual void destory() override;

    void mouseMovecallback(float xpos, float ypos);
    void scrollcallback(float yoffset);

    void keyUp();
    void keyDown();
    void keyLeft();
    void keyRight();
};

#endif