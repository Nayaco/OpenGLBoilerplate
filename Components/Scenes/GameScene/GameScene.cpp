#include "GameScene.hpp"

const glm::vec3 sunpos_0(0.0, 0.0, -1.0);

GameScene::GameScene() { }
void GameScene::draw() const {
    auto sun_light = 
        reinterpret_cast<ALight*>(ResourceManager::getLight("global_sun_light"));
    sun_light->enable();
    
    auto particleshader = ResourceManager::getShader("particle");
    particleshader.use();
    particleshader.setMat4("view", view_matrix);
    particleshader.setMat4("projection", projection_matrix);
    particleshader.setVec3("campos", cam->GetViewPosition());
    particle_sys->draw(particleshader);
    
    

    auto sunshader = ResourceManager::getShader("entitysun");
    auto view = glm::mat4(glm::mat3(view_matrix));
    sunshader.use();
    sunshader.setMat4("view", view);
    sunshader.setMat4("projection", projection_matrix);
    sun->draw(sunshader);

    skybox->draw();
}

void GameScene::update() {
    game_time = Context::game_time - floor((Context::game_time / DAY_DURATION)) * DAY_DURATION;
    projection_matrix = cam->GetProjectionMatrix();
    view_matrix = cam->GetViewMatrix();

    glm::mat4 sunpos_matrix = glm::mat4(1.0f);
    sunpos_matrix = glm::rotate(sunpos_matrix, game_time * (float)(M_PI / DAY_DURATION) , glm::vec3(1.0f, 0.0f, 0.0f));
    sunpos_vec = glm::vec3(sunpos_matrix * glm::vec4(sunpos_0, 1.0));
    
    skymap->update(sunpos_vec, glm::vec3(1.0, 1.0, 1.0));
    sun->update(normalize(sunpos_vec), glm::vec3(1.0, 1.0, 1.0));

    auto sun_light = 
        reinterpret_cast<ALight*>(ResourceManager::getLight("global_sun_light"));
    sun_light->setUpALight(glm::vec3(sunpos_vec), glm::vec3(1.0, 1.0, 1.0));

    auto view = glm::mat4(glm::mat3(view_matrix));
    skybox->setPV(projection_matrix, view);

    static float delta_time;
    delta_time = 0.0 <= delta_time && delta_time < 0.04 ? Context::delta_time + delta_time : 0.0;
    sky_should_update = delta_time == 0.0;

    particle_sys->setGenerator(
        cam->GetViewPosition() + glm::vec3(0.0, 0.0, -2.0),
        glm::vec3(0.0, -0.1, 0.0), 
        0.2, 0.5, 0.2, 1.0);
    particle_sys->update(Context::delta_time, 1);

    if (sky_should_update) {
        skymap->bind();        
        skymap->render();
        skymap->unbind();
    }
}

void GameScene::initialize() {
    mmove_func = std::bind(&GameScene::mouseMovecallback, this, std::placeholders::_1, std::placeholders::_2);
    mscroll_func = std::bind(&GameScene::scrollcallback, this, std::placeholders::_1);
    keyesc_func = std::bind(&GameScene::keyEsc, this);    
    keyf_func = std::bind(&GameScene::keyF, this);    
    keya_func = std::bind(&GameScene::keyA, this);    
    keys_func = std::bind(&GameScene::keyS, this);    
    keyd_func = std::bind(&GameScene::keyD, this);    
    keyw_func = std::bind(&GameScene::keyW, this);    

    Input::bindMousemoveCallback(&mmove_func);
    Input::bindScrollCallback(&mscroll_func);
    Input::bindKeydownCallback(Input::Keys::KEY_ESC, &keyesc_func);
    Input::bindKeydownCallback(Input::Keys::KEY_F, &keyf_func);
    Input::bindKeydownCallback(Input::Keys::KEY_A, &keya_func);
    Input::bindKeydownCallback(Input::Keys::KEY_S, &keys_func);
    Input::bindKeydownCallback(Input::Keys::KEY_D, &keyd_func);
    Input::bindKeydownCallback(Input::Keys::KEY_W, &keyw_func);

    ResourceManager::loadVF("skymap", "Resources/Shaders/SkyMap/skymap");
    ResourceManager::loadVF("skybox", "Resources/Shaders/Skybox/skybox");
    ResourceManager::loadVF("grassblade", "Resources/Shaders/GrassBlade/grassBlades");
    ResourceManager::loadVF("entitysun", "Resources/Shaders/EntitySun/sun");
    ResourceManager::loadVGF("particle", "Resources/Shaders/Particle/particle_graph");

    ResourceManager::GenALisht("global_sun_light", 0, glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0));

    ResourceManager::Load2D("sprite", "Resources/Textures/Particle/particle.png");

    skymap = new Skymap(ResourceManager::getShader("skymap"));
    skymap->setTextureSize(100, 100);
    skymap->initialize();

    skybox   = new Skybox(skymap->skymap_texture, ResourceManager::getShader("skybox"));
    sun      = new EntitySun();

    particle_sys = new ParticleSystem(ResourceManager::getTexture("sprite"), 200);
    particle_sys->initialize(glm::vec3(0.0), glm::vec3(0.0, -0.1, 0.0), 
        0.2, 0.5, 0.2, 1.0);

    cam      = new Camera(glm::vec3(0.0f, 0.0f, 2.0f));
}

void GameScene::destory() {
    delete cam;
}

void GameScene::mouseMovecallback(float xpos, float ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    cam->ProcessMouseMovement(xoffset, yoffset);
}

void GameScene::scrollcallback(float yoffset) {
    cam->ProcessMouseScroll(yoffset);
}

void GameScene::keyEsc() {
    destory();
    Context::close();
}

void GameScene::keyF() { }

void GameScene::keyA() {
    cam->ProcessKeyboard(Camera::Camera_Movement::LEFT, Context::delta_time);
}

void GameScene::keyS() {
    cam->ProcessKeyboard(Camera::Camera_Movement::BACKWARD, Context::delta_time);
}

void GameScene::keyW() {
    cam->ProcessKeyboard(Camera::Camera_Movement::FORWARD, Context::delta_time);
}

void GameScene::keyD() {
    cam->ProcessKeyboard(Camera::Camera_Movement::RIGHT, Context::delta_time);
}