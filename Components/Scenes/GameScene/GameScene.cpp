#include "GameScene.hpp"

const glm::vec3 sunpos_0(0.0, 0.0, -1.0);

GameScene::GameScene() { }
void GameScene::draw() const {
    auto sun_light = 
        reinterpret_cast<ALight*>(ResourceManager::getLight("global_sun_light"));
    sun_light->enable();
    
    firstpass->bind();

    sun->draw(ResourceManager::getShader("entitysun"));

    particle_sys->draw(ResourceManager::getShader("particle"));

    skybox->draw();

    firstpass->unbind();

    bloom->bind();
    bloom->bindTexture(firstpass->texture_buffers[FirstPass::TEX_BRIGHT_BUF]);
    bloom->draw(ResourceManager::getShader("bloom"));
    bloom->unbind();

    firstpass->bindTexture(bloom->bloom_textures[bloom->horizon], FirstPass::TEX_BRIGHT_BUF);
    firstpass->draw(ResourceManager::getShader("firstpass"));
}

void GameScene::update() {
    // variables
    game_time = Context::game_time - floor((Context::game_time / DAY_DURATION)) * DAY_DURATION;
    projection_matrix = cam->GetProjectionMatrix();
    view_matrix = cam->GetViewMatrix();
    // sunposition 
    glm::mat4 sunpos_matrix = glm::mat4(1.0f);
    sunpos_matrix = glm::rotate(sunpos_matrix, game_time * (float)(M_PI / DAY_DURATION) , glm::vec3(1.0f, 0.0f, 0.0f));
    sunpos_vec = glm::vec3(sunpos_matrix * glm::vec4(sunpos_0, 1.0));
    // skymap
    skymap->update(sunpos_vec, glm::vec3(1.0, 1.0, 1.0));
    
    // sunlight
    auto sun_light = 
        reinterpret_cast<ALight*>(ResourceManager::getLight("global_sun_light"));
    sun_light->setUpALight(glm::vec3(sunpos_vec), glm::vec3(1.0, 1.0, 1.0));
    // skybox
    auto view = glm::mat4(glm::mat3(view_matrix));
    skybox->setPV(projection_matrix, view);
    // particle system
    auto particleshader = ResourceManager::getShader("particle");
    particleshader.use();
    particleshader.setMat4("projection", projection_matrix);
    particleshader.setMat4("view", view_matrix);
    particleshader.setVec3("campos", cam->GetViewPosition());
    particle_sys->setGenerator(
        cam->GetViewPosition() + glm::vec3(0.0, 0.0, -2.0),
        glm::vec3(0.0, -0.1, 0.0), 
        0.2, 0.5, 0.2, 1.0);
    particle_sys->update(Context::delta_time, 1);
    // entity sun
    float sunlight_color_factor = glm::dot(glm::normalize(sunpos_vec), glm::vec3(0.0, 1.0, 0.0));   
    sun->update(normalize(sunpos_vec) * 0.8f, glm::vec3(1.5, 1.5 * (0.6 + powf(sunlight_color_factor, 1.2) * 0.4), 1.5 * (0.5 + powf(sunlight_color_factor, 1.2) * 0.5) ));
    auto sunshader = ResourceManager::getShader("entitysun");
    sunshader.use();
    sunshader.setMat4("projection", projection_matrix);
    sunshader.setMat4("view", view);
    // skymap
    static float delta_time;
    delta_time = 0.0 <= delta_time && delta_time < 0.04 ? Context::delta_time + delta_time : 0.0;
    sky_should_update = delta_time == 0.0;
    if (sky_should_update) {
        skymap->bind();        
        skymap->render();
        skymap->unbind();
    }
    //firstpass
    firstpass->setSize(Context::window_width, Context::window_height);
    bloom->setSize(Context::window_width, Context::window_height);
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
    ResourceManager::loadVF("firstpass", "Resources/Shaders/FirstPass/firstPass");
    ResourceManager::loadVF("bloom", "Resources/Shaders/Bloom/bloom");

    ResourceManager::GenALisht("global_sun_light", 0, glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0));

    ResourceManager::Load2D("sprite", "Resources/Textures/Particle/particle.png");

    cam      = new Camera(glm::vec3(0.0f, 0.0f, 2.0f));
    
    skymap = new Skymap(ResourceManager::getShader("skymap"));
    skymap->setTextureSize(100, 100);
    skymap->initialize();

    skybox   = new Skybox(skymap->skymap_texture, ResourceManager::getShader("skybox"));
    sun      = new EntitySun();

    particle_sys = new ParticleSystem(ResourceManager::getTexture("sprite"), 200);
    particle_sys->initialize(glm::vec3(0.0), glm::vec3(0.0, -0.1, 0.0), 
        0.2, 0.5, 0.2, 1.0);

    bloom     = new Bloom(Context::window_width, Context::window_height);  
    bloom->initialize();

    firstpass = new FirstPass(Context::window_width, Context::window_height, true, 1.0);
    firstpass->initialize();
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