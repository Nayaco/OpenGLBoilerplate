#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "Core/Common.hpp"
#include "Core/Context/Context.hpp"
#include "Core/GameObjects/Scene/BaseScene.hpp"

#include "Core/GameObjects/Camera/Camera.hpp"

#include "Core/Graphics/Mesh/TerrainMesh/TerrainMesh.hpp"
#include "Core/ResourceManager/ResourceManager.hpp"
#include "Core/Input/Input.hpp"
#include "Core/GameObjects/Skymap/Skymap.hpp"
#include "Core/GameObjects/Skybox/Skybox.hpp"
#include "Core/GameObjects/Skybox/EntitySun.hpp"
#include "Core/GameObjects/Terrain/Terrain.hpp"
#include "Core/GameObjects/Grass/GrassBlade.h"
#include "Core/GameObjects/ParticleSystem/ParticleSystem.hpp"
#include "Core/GameObjects/Cloud/Cloud.hpp"
#include "Core/PostProcessing/FirstPass/FirstPass.hpp"
#include "Core/PostProcessing/Bloom/Bloom.hpp"

#include "Core/ExceptionHandle/ErrLog.hpp"

#include "GameSceneConfig.hpp"

class GameScene : public BaseScene {
    Skymap *skymap;
    Skybox *skybox;
    EntitySun *sun;
    Camera *cam;
    ParticleSystem *particle_sys;
    FirstPass *firstpass;
    Bloom *bloom;
    Cloud *cloud;
    Terrain *terrain;
    
    bool  firstMouse = true;
    float lastX      = 0.0f;
    float lastY      = 0.0f;

    float game_time  = 0.0f;
    bool  sky_should_update = false;
    glm::mat4 projection_matrix;
    glm::mat4 view_matrix;
    glm::vec3 sunpos_vec;
    glm::vec3 suncolor_vec;

    std::function<void(float, float)> mmove_func;
    std::function<void(float)> mscroll_func;
    std::function<void()> keyesc_func;
    std::function<void()> keyf_func;    
    std::function<void()> keya_func;
    std::function<void()> keys_func;
    std::function<void()> keyw_func;
    std::function<void()> keyd_func;
    
    void mouseMovecallback(float xpos, float ypos);
    void scrollcallback(float yoffset);

    void keyEsc();
    void keyF();
    void keyA();
    void keyS();
    void keyW();
    void keyD();
public:
    GameScene();

    virtual void initialize() override;
    virtual void draw() const override;
    virtual void destory() override;
    virtual void update() override;
};

#endif