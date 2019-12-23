#ifndef DEMPSCENE_HPP
#define DEMOSCENE_HPP

#include "Core/Common.hpp"
#include "Core/Context/Context.hpp"
#include "Core/Scene/BaseScene.hpp"
#include "Core/Graphics/Mesh/TerrainMesh/TerrainMesh.hpp"
#include "Core/ResourceManagers/ShaderManager.hpp"
#include "Core/ResourceManagers/TextureManager.hpp"
#include "Core/Input/Input.hpp"
#include "Components/Cameras/DemoCamera.hpp"

#include "DemoSceneConfig.hpp"
#include "Core/ExceptionHandle/ErrLog.hpp"
class DemoScene : public BaseScene {
public:
    TerrainMesh *mesh;
    DemoCamera *cam;
    int screen_width;
    int screen_height;
    float cut_near = 0.1f;
    float cut_far = 1000.0f;

    DemoScene() {
    }
    virtual void draw() const override {
        glm::mat4 projection = glm::perspective(glm::radians(cam->Zoom), (float)Context::window_width / (float)Context::window_height, cut_near, cut_far);
        glm::mat4 view = cam->GetViewMatrix();
        
        Shader render_shader = ShaderManager::get(TER_SHADER_NAME);
        render_shader.use();
        render_shader.setMat4("projection", projection);
        render_shader.setMat4("view", view);
        render_shader.setMat4("model", glm::mat4(1.0f));
        
        mesh->Draw(render_shader);
    }
    virtual void initialize() override {
        ShaderManager::loadVTTF(TER_SHADER_NAME, TER_SHADER);
        TextureManager::Load2D(TER_TEX_NAME, TER_TEX, TEX_TYPE::HEIGHTMAP);
        texture_vector texes {TextureManager::get(TER_TEX_NAME)};
        
        mesh = new TerrainMesh(texes);
        // cam = new DemoCamera();
    }
    virtual void destory() override {
        delete mesh;
        delete cam;
    }
};

#endif