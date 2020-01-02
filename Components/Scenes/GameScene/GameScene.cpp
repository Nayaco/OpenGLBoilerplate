#include "GameScene.hpp"

const glm::vec3 sunpos_0(0.0, 0.0, -1.0);

GameScene::GameScene() { }

float CalculateFrameRate() {    
    static float framesPerSecond = 0.0f;
    static float FPS = 0.0f;
    static float lastTime = 0.0f;       
    float currentTime = Context::game_time;    
    ++framesPerSecond;
    if( currentTime - lastTime > 0.5f ) {
        lastTime = currentTime;
        FPS = framesPerSecond * 2.0;
        framesPerSecond = 0;
    }
    return FPS;
}

void GameScene::draw() const {
    chunk->terrain->enableReflectionRefration();

    // glEnable(GL_CLIP_DISTANCE0);
    glDisable(GL_CULL_FACE);
    cam->Reflect(2.5);
    Shader terrain_shader = ResourceManager::getShader("terrainmesh");
    terrain_shader.use();
    terrain_shader.setMat4("view", cam->GetViewMatrix());
    terrain_shader.setVec3("viewpos", cam->GetViewPosition());
    
    reflectionBuffer->bind();
    chunk->draw_terrain(ResourceManager::getShader("terrainmesh"));
    
    Shader tower_shader = ResourceManager::getShader("tower");    
    tower_shader.use();
    tower_shader.setFloat("reflection_refraction", 1.0);
    tower_shader.setMat4("view", cam->GetViewMatrix());
    tower_shader.setVec3("viewpos", cam->GetViewPosition());
    tower->draw(ResourceManager::getShader("tower"));

    reflectionBuffer->unbind(Context::window_width, Context::window_height);

    cam->Reflect(2.5);
    terrain_shader.use();
    terrain_shader.setMat4("view", cam->GetViewMatrix());
    terrain_shader.setVec3("viewpos", cam->GetViewPosition());
    
    tower_shader.use();
    tower_shader.setFloat("reflection_refraction", 0.0);
    tower_shader.setMat4("view", cam->GetViewMatrix());
    tower_shader.setVec3("viewpos", cam->GetViewPosition());

    glEnable(GL_CULL_FACE);
    // glDisable(GL_CLIP_DISTANCE0);
    chunk->terrain->disableReflectionRefration();
    // glEnable(GL_CLIP_DISTANCE1);
    refractionBuffer-> bind();
    // rfract only terrain is needed
    chunk->draw_terrain(ResourceManager::getShader("terrainmesh"));
    tower->draw(ResourceManager::getShader("tower"));

    refractionBuffer->unbind(Context::window_width, Context::window_height);
    // glDisable(GL_CLIP_DISTANCE1);

    //-----------------------

    firstpass->bind();

    plane->draw(ResourceManager::getShader("plane"));
    tower->draw(ResourceManager::getShader("tower"));
    waterRenderer->render(ResourceManager::getShader("water"), water, *cam,
                          reflectionBuffer->getColorBuffer(),
                          refractionBuffer->getColorBuffer(),
                          refractionBuffer->getDepthBuffer());
    


    chunk->draw_terrain(ResourceManager::getShader("terrainmesh"));
    chunk->draw_grass();

    particle_sys->draw(ResourceManager::getShader("particle"));
    particle_sys_flare->draw(ResourceManager::getShader("particle_flare"));
    particle_sys_torch->draw(ResourceManager::getShader("particle_torch"));
    


    sun->draw(ResourceManager::getShader("entitysun"));
    skybox->draw();

    font->renderText("FPS:" + std::to_string(game_fps).substr(0, 4), 25.0f, 25.0f, 1.0f, glm::vec3(0.8, 0.8f, 0.8f));
    if (!gamestart) {
        font->renderText("Monoplane", Context::window_width / 2.0, Context::window_height / 2.0 + 100.0, 2.0f, glm::vec3(2.5, 2.5, 2.5));   
        font->renderText("Press F To Start", Context::window_width / 2.0, Context::window_height / 2.0, 1.2f, glm::vec3(1.8, 1.8, 1.8));
    }

    firstpass->unbind();

    bloom->bind();
    bloom->bindTexture(firstpass->texture_buffers[FirstPass::TEX_BRIGHT_BUF]);
    bloom->draw(ResourceManager::getShader("bloom"));
    bloom->unbind();

    // Texture testt; testt._id = reflectionBuffer->getColorBuffer();
    // firstpass->bindTexture(testt, FirstPass::TEX_BRIGHT_BUF);
    firstpass->bindTexture(bloom->bloom_textures[bloom->horizon], FirstPass::TEX_BRIGHT_BUF);
    firstpass->draw(ResourceManager::getShader("firstpass"));
}

void GameScene::update() {
    // variables
    game_time = Context::game_time - floor((Context::game_time / TURNAROUND_DURATION)) * TURNAROUND_DURATION;
    game_delat_time = Context::delta_time * 0.3;
    game_fps =  CalculateFrameRate();
    // plane camera 
    gameover_last = gameover;
    if(!gameover && gamestart) {
        plane->update(Context::delta_time);
        gameover = plane->aabbbox.checkCollision(chunk->terrain->terrainmap, chunk->terrain->terrain_height) ||
                plane->aabbbox.checkCollision(tower->aabbbox);
        
        glm::vec2 plane_front2d = glm::normalize(glm::vec2(plane->front.x, plane->front.z));
        cam->Position = plane->center + glm::vec3(-plane_front2d.x * 8.5, 4.0, -plane_front2d.y * 8.5);
        cam->Yaw -= (plane->yaw - plane_yaw);
        // cam->Pitch = plane->pitch;
        cam->updateCameraVectors();
        plane_yaw = plane->yaw;
    }
    
    
    //Camera
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
    particleshader.setVec3("color", glm::vec3(2.1, 2.1, 2.1));
    if(!gameover && gamestart) {
        particle_sys->setGenerator(
            plane->center + plane->right - plane->front * 0.5f,
            glm::vec3(0.0, -0.1, 0.0), 
            0.1, 0.1, 0.5, 6.0);
        particle_sys->update(Context::delta_time, 2);

        particle_sys->setGenerator(
            plane->center - plane->right - plane->front * 0.5f,
            glm::vec3(0.0, -0.1, 0.0), 
            0.1, 0.1, 0.5, 6.0);
        particle_sys->update(Context::delta_time, 2);
    }

    // particle sys flare
    auto particleshader_flare = ResourceManager::getShader("particle_flare");
    particleshader_flare.use();
    particleshader_flare.setMat4("projection", projection_matrix);
    particleshader_flare.setMat4("view", view_matrix);
    particleshader_flare.setVec3("campos", cam->GetViewPosition());
    particleshader_flare.setVec3("color", glm::vec3(4.0, 0.2, 0.2));
    particle_sys_flare->setGenerator(
        plane->center,
        glm::vec3(0.0, 0.1, 0.0), 
        2.0, 8.0, 2.5, 5.8);
    if(gameover && !gameover_last)particle_sys_flare->update(Context::delta_time, 1000, 0.27);
    else particle_sys_flare->update(Context::delta_time, 0);
    // particle sys torch
    auto particleshader_torch = ResourceManager::getShader("particle_torch");
    particleshader_torch.use();
    particleshader_torch.setMat4("projection", projection_matrix);
    particleshader_torch.setMat4("view", view_matrix);
    particleshader_torch.setVec3("campos", cam->GetViewPosition());
    particleshader_torch.setVec3("color", glm::vec3(4.0, 2.0, 0.3));
    particle_sys_torch->setGenerator(
        tower->center + glm::vec3(0.0, 13.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0), 
        0.5, 1.2, 0.5, 3.2);
    particle_sys_torch->update(Context::delta_time, 4, 0.55);
    // entity sun
    float sunlight_color_factor = glm::max(glm::dot(glm::normalize(sunpos_vec), glm::vec3(0.0, 1.0, 0.0)), 0.0f);   
    sun->update(normalize(sunpos_vec - glm::vec3(0.0, 0.1, 0.0)) * 0.8f, 
        suncolor_vec * 
        (game_time <= DAY_DURATION ?
        glm::vec3((0.6 + powf(sunlight_color_factor, 1.2) * 0.4), (0.3 + powf(sunlight_color_factor, 1.2) * 0.7), (0.2 + powf(sunlight_color_factor, 1.2) * 0.8) ) :
        glm::vec3(1.0))
        );
    auto sunshader = ResourceManager::getShader("entitysun");
    sunshader.use();
    sunshader.setMat4("projection", projection_matrix);
    sunshader.setMat4("view", view);
    // skymap
    skymap->update(sunpos_vec, game_time <= DAY_DURATION ? suncolor_vec : suncolor_vec * 0.1f);
    static float delta_time;
    delta_time = 0.0 <= delta_time && delta_time < 0.04 ? Context::delta_time + delta_time : 0.0;
    sky_should_update = delta_time == 0.0;
    cloud->update(game_delat_time, glm::dot(sunpos_vec, glm::vec3(0.0, 1.0, 0.0)) * (game_time <= DAY_DURATION ? 1.0 : 0.3));
    cloud->bind();
    cloud->render();
    cloud->unbind();
    if (sky_should_update) {
        skymap->bind();        
        skymap->render();
        skymap->unbind();
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
    chunk->setGrassMatrix(projection_matrix, view_matrix, cam->GetViewPosition(), glm::vec3(0.0, 1.0, 0.0));
    //plane
    Shader plane_shader = ResourceManager::getShader("plane");
    plane_shader.use();
    plane_shader.setMat4("projection", projection_matrix);
    plane_shader.setMat4("view", view_matrix);
    // tower
    Shader tower_shader = ResourceManager::getShader("tower");
    tower_shader.use();
    tower_shader.setMat4("projection", projection_matrix);
    tower_shader.setMat4("view", view_matrix);
    tower_shader.setVec3("viewpos", cam->GetViewPosition());
    sun_light->use(tower_shader);
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
    ResourceManager::loadVGF("particle_flare", "Resources/Shaders/Particle/particle_graph");
    ResourceManager::loadVGF("particle_torch", "Resources/Shaders/Particle/particle_graph");
    ResourceManager::loadVF("firstpass", "Resources/Shaders/FirstPass/firstPass");
    ResourceManager::loadVF("bloom", "Resources/Shaders/Bloom/bloom");
    ResourceManager::loadVF("cloud", "Resources/Shaders/Cloud/cloud");
    ResourceManager::loadVF("font", "Resources/Shaders/Font/font");
    ResourceManager::loadVF("water", "Resources/Shaders/Water/water");
    ResourceManager::loadVF("plane", "Resources/Shaders/Plane/plane");
    ResourceManager::loadVF("tower", "Resources/Shaders/Tower/tower");

    ResourceManager::GenALisht("global_sun_light", 0, glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0));

    ResourceManager::Load2D("sprite", "Resources/Textures/Particle/particle.png");

    ResourceManager::LoadFont("Resources/Fonts/arial.ttf");

    cam      = new Camera(glm::vec3(0.0f, 20.0f, -40.0f), glm::vec3(0.0, 1.0, 0.0), 90.0f);

    font     = new Font(ResourceManager::getShader("font"));
    font->initialize(Context::window_width, Context::window_height);

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

    particle_sys_flare = new ParticleSystem(ResourceManager::getTexture("sprite"), 1000);
    particle_sys_flare->initialize(glm::vec3(0.0), glm::vec3(0.0, -0.1, 0.0), 
        0.2, 0.5, 0.2, 1.0);

    particle_sys_torch = new ParticleSystem(ResourceManager::getTexture("sprite"), 200);
    particle_sys_torch->initialize(glm::vec3(0.0), glm::vec3(0.0, 0.1, 0.0), 
        0.5, 1.5, 0.5, 1.2);

    bloom     = new Bloom(Context::window_width, Context::window_height);  
    bloom->initialize();

    firstpass = new FirstPass(Context::window_width, Context::window_height, true, 1.0);
    firstpass->initialize();

    chunk = new Chunk(CHUNK_PLACE_X, CHUNK_PLACE_Z, CHUNK_WIDTH, CHUNK_HEIGHT);
    chunk->initialize_terrain(texture_vector{ }, TERRAIN_TESS, TERRAIN_HEIGHT_MAX, TERRAIN_OCTAVE);
    chunk->initialize_grass(ResourceManager::getShader("grassblade"));

    water = WaterGenerator::generate(50, 2.5, glm::vec2(-25.0f,-25.0f));
    waterRenderer = new WaterRenderer();
    reflectionBuffer = new FrameBuffer(800, 600, REFLECTION);
    refractionBuffer = new FrameBuffer(800, 600, REFRACTION);

    plane = new Plane();
    plane_yaw = plane->yaw;
    
    tower = new Tower();
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

void GameScene::keyF() { gamestart = true; }

void GameScene::keyA() {
    if(!gameover && gamestart)
        plane->ProcessKeyboard(Plane::Plane_Movement::LEFT, Context::delta_time);
    else
        cam->ProcessKeyboard(Camera::Camera_Movement::LEFT, Context::delta_time);
}

void GameScene::keyS() {
    if(!gameover && gamestart)
        plane->ProcessKeyboard(Plane::Plane_Movement::BACKWARD, Context::delta_time);
    else
        cam->ProcessKeyboard(Camera::Camera_Movement::BACKWARD, Context::delta_time);
    
}

void GameScene::keyW() {
    if(!gameover && gamestart)
        plane->ProcessKeyboard(Plane::Plane_Movement::FORWARD, Context::delta_time);
    else
        cam->ProcessKeyboard(Camera::Camera_Movement::FORWARD, Context::delta_time);
}

void GameScene::keyD() {
    if(!gameover && gamestart)
        plane->ProcessKeyboard(Plane::Plane_Movement::RIGHT, Context::delta_time);
    else
        cam->ProcessKeyboard(Camera::Camera_Movement::RIGHT, Context::delta_time);
}