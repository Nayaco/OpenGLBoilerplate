#include "GameScene.hpp"

const glm::vec3 sunpos_0(0.0, 0.0, -1.0);

GameScene::GameScene() : water(0, 0, 0){ }

void GameScene::draw() const {
    // terrain->enableReflectionRefration();
    // glEnable(GL_CLIP_DISTANCE0);
    // reflectionBuffer->bind();
    // // reflect camera
    // cam->Reflect(0.0);
    // // render the object that need reflected
    // terrain->draw(ResourceManager::getShader("terrainmesh"));
    // reflectionBuffer->unbind(Context::window_width, Context::window_height);
    // cam->Reflect(0.0);
    // glDisable(GL_CLIP_DISTANCE0);

    // glEnable(GL_CLIP_DISTANCE1);
    // refractionBuffer-> bind();
    // // // rfract only terrain is needed
    // terrain->draw(ResourceManager::getShader("terrainmesh"));
    // refractionBuffer->unbind(Context::window_width, Context::window_height);
    // glDisable(GL_CLIP_DISTANCE1);
    // terrain->disableReflectionRefration();

    //-----------------------
    firstpass->bind();

    terrain->draw(ResourceManager::getShader("terrainmesh"));
    waterRenderer->render(water, *cam, 
        reflectionBuffer->getColorBuffer(),
        refractionBuffer->getColorBuffer(),
        refractionBuffer->getDepthBuffer());
    sun->draw(ResourceManager::getShader("entitysun"));
    

    particle_sys->draw(ResourceManager::getShader("particle"));
   
    skybox->draw();

    firstpass->unbind();

    bloom->bind();
    bloom->bindTexture(firstpass->texture_buffers[FirstPass::TEX_BRIGHT_BUF]);
    bloom->draw(ResourceManager::getShader("bloom"));
    bloom->unbind();
    // std::cout<<"here"<<std::endl;

    // Texture rfcb; rfcb._id = refractionBuffer->getColorBuffer();//reflectionBuffer->getColorBuffer();
    // firstpass->bindTexture(rfcb, FirstPass::TEX_COLOR_BUF);
    firstpass->bindTexture(bloom->bloom_textures[bloom->horizon], FirstPass::TEX_BRIGHT_BUF);
    firstpass->draw(ResourceManager::getShader("firstpass"));
}

void GameScene::update() {
    // variables
    game_time = Context::game_time - floor((Context::game_time / TURNAROUND_DURATION)) * TURNAROUND_DURATION;
    projection_matrix = cam->GetProjectionMatrix();
    view_matrix = cam->GetViewMatrix();
    auto view = glm::mat4(glm::mat3(view_matrix));
    // sunposition 
    if (game_time <= DAY_DURATION) {
        glm::mat4 sunpos_matrix = glm::mat4(1.0f);
        sunpos_matrix = glm::rotate(sunpos_matrix, 
                game_time * (float)(DAY_DURATION / TURNAROUND_DURATION) * (float)(2.0 * M_PI / DAY_DURATION) , 
                glm::vec3(1.0f, 0.0f, 0.0f));
        sunpos_vec = glm::vec3(sunpos_matrix * glm::vec4(sunpos_0, 1.0));
        suncolor_vec = glm::vec3(1.5, 1.5, 1.5);
    } else {
        glm::mat4 sunpos_matrix = glm::mat4(1.0f);
        sunpos_matrix =  glm::rotate(sunpos_matrix, 
                (float)(game_time - DAY_DURATION) * (float)(NIGHT_DURATION / TURNAROUND_DURATION) * (float)(2.0 * M_PI / NIGHT_DURATION) , 
                glm::vec3(1.0f, 0.0f, 0.0f));
        sunpos_vec = glm::vec3(sunpos_matrix * glm::vec4(sunpos_0, 1.0));
        suncolor_vec = glm::vec3(0.75, 0.66, 0.45);
    }
    // skymap and cloud
    skymap->update(sunpos_vec, game_time <= DAY_DURATION ? suncolor_vec : suncolor_vec * 0.1f);
    // sunlight
    auto sun_light = 
        reinterpret_cast<ALight*>(ResourceManager::getLight("global_sun_light"));
    sun_light->setUpALight(glm::vec3(sunpos_vec), suncolor_vec);
    sun_light->enable();
    // skybox
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
    float sunlight_color_factor = glm::max(glm::dot(glm::normalize(sunpos_vec), glm::vec3(0.0, 1.0, 0.0)), 0.0f);   
    sun->update(normalize(sunpos_vec - glm::vec3(0.0, 0.1, 0.0)) * 0.8f, 
        suncolor_vec * glm::vec3(1.0, (0.6 + powf(sunlight_color_factor, 1.2) * 0.4), (0.5 + powf(sunlight_color_factor, 1.2) * 0.5) ));
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

        cloud->bind();
        cloud->render();
        cloud->unbind();
    } 
    //firstpass
    firstpass->setSize(Context::window_width, Context::window_height);
    bloom->setSize(Context::window_width, Context::window_height);
    //terrain
    Shader terrain_shader = ResourceManager::getShader("terrainmesh");
    terrain_shader.use();
    terrain_shader.setMat4("projection", projection_matrix);
    terrain_shader.setMat4("view", view_matrix);
    terrain_shader.setVec3("viewpos", cam->GetViewPosition());
    sun_light->use(terrain_shader);
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
    
    ResourceManager::loadVGF("terrainmesh", "Resources/Shaders/TerrainMesh/TerrainMesh");
    ResourceManager::loadVF("skymap", "Resources/Shaders/SkyMap/skymap");
    ResourceManager::loadVF("skybox", "Resources/Shaders/Skybox/skybox");
    ResourceManager::loadVF("grassblade", "Resources/Shaders/GrassBlade/grassBlades");
    ResourceManager::loadVF("entitysun", "Resources/Shaders/EntitySun/sun");
    ResourceManager::loadVGF("particle", "Resources/Shaders/Particle/particle_graph");
    ResourceManager::loadVF("firstpass", "Resources/Shaders/FirstPass/firstPass");
    ResourceManager::loadVF("bloom", "Resources/Shaders/Bloom/bloom");
    ResourceManager::loadVF("cloud", "Resources/Shaders/Cloud/cloud");

    ResourceManager::GenALisht("global_sun_light", 0, glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0));

    ResourceManager::Load2D("sprite", "Resources/Textures/Particle/particle.png");

    cam      = new Camera(glm::vec3(0.0f, 0.0f, 2.0f));

    cloud  = new Cloud(ResourceManager::getShader("cloud"));
    cloud->generate();
    cloud->initialize();

    skymap = new Skymap(ResourceManager::getShader("skymap"));
    skymap->setTextureSize(100, 100);
    skymap->initialize();

    skybox   = new Skybox(skymap->skymap_texture, ResourceManager::getShader("skybox"));
    skybox->bindCloud(cloud->cloud_tex);

    sun      = new EntitySun();

    particle_sys = new ParticleSystem(ResourceManager::getTexture("sprite"), 200);
    particle_sys->initialize(glm::vec3(0.0), glm::vec3(0.0, -0.1, 0.0), 
        0.2, 0.5, 0.2, 1.0);

    bloom     = new Bloom(Context::window_width, Context::window_height);  
    bloom->initialize();

    firstpass = new FirstPass(Context::window_width, Context::window_height, true, 1.0);
    firstpass->initialize();

    terrain  = new Terrain(0.0f, 0.0f, 50.0f, 50.0f, 30.0f, 8);
    terrain->setOctave( 12);
    terrain->generate(texture_vector{ }, 3.0);

    waterGenerator = new WaterGenerator();
    water = waterGenerator->generate(800, 600);

    reflectionBuffer = new FrameBuffer(800, 600, REFLECTION);
    refractionBuffer = new FrameBuffer(800, 600, REFRACTION);
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