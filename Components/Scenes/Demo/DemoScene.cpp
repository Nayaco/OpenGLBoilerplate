#include "DemoScene.hpp"

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};
unsigned int quadVAO, quadVBO;
imap2d staticmap;
float skymap_time = 0;
static vector<string> SKYMAP_NAMES = {
    string(SKY_TEX) + string("_rt.jpg"),
    string(SKY_TEX) + string("_lf.jpg"),
    string(SKY_TEX) + string("_up.jpg"),
    string(SKY_TEX) + string("_dn.jpg"),
    string(SKY_TEX) + string("_ft.jpg"),
    string(SKY_TEX) + string("_bk.jpg"),
};

DemoScene::DemoScene() { }
void DemoScene::draw() const {
    // glm::mat4 projection = cam->GetProjectionMatrix();
    // glm::mat4 view = cam->GetViewMatrix();
    
    // Shader render_shader = ResourceManager::getShader(TER_SHADER_NAME);
    // auto light = reinterpret_cast<ALight*>(ResourceManager::getLight(ALIGHT_NAME));
    
    // skymap_time += Context::delta_time; 
    // if (skymap_time > 0.05) {
    //     skymap_time = 0;
    //     skymap->bind();
    //     glm::vec3 sun_poss(0.0, 0.0, -1.0);
    //     glm::mat4 sunposx = glm::mat4(1.0f);
    //     int k = 0.1f * Context::game_time / (M_PI);
    //     sunposx  = glm::rotate(sunposx, 0.1f * Context::game_time - (float)k * (float)M_PI, glm::vec3(0.4f, 0.9f, 0.0f));
    //     skymap->update(glm::vec3(sunposx * glm::vec4(sun_poss, 1.0)), glm::vec3(1.0, 1.0, 1.0));
    //     skymap->render();
    //     skymap->unbind();
    //     light->setUpALight(glm::vec3(sunposx * glm::vec4(sun_poss, 1.0)), glm::vec3(1.0, 1.0, 1.0));
    // }

    // render_shader.use();
    // render_shader.setMat4("projection", projection);
    // render_shader.setMat4("view", view);
    // render_shader.setVec3("viewpos", cam->GetViewPosition());
    // light->enable();
    // light->use(render_shader);

    // // terrain->draw(render_shader);
    // // terrain2->draw(render_shader);
    // // terrain3->draw(render_shader);
    // // terrain4->draw(render_shader);
    // grass->setViewMatrix(view);
    // grass->setProjectionMatrix(projection);
    // grass->render();
    
    // view = glm::mat4(glm::mat3(view));
    // // skybox->skybox_shader.use();
    // skybox->skybox_shader.setMat4("projection", projection);
    // skybox->skybox_shader.setMat4("view", view);
    // skybox->draw();
    testmap->draw(ResourceManager::getShader("tests"));
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // glClearColor(1.0, 1.0, 1.0, 1.0);

}

void DemoScene::initialize() {
    // ResourceManager::loadVGF(TER_SHADER_NAME, TER_SHADER);
    // // ResourceManager::loadVF("test2", "Resources/Shaders/Test2/sc");
    // // ResourceManager::loadVF(SKY_SHADER_NAME, SKY_SHADER);
    // ResourceManager::loadVF("skymap", 
    //                         "Resources/Shaders/SkyMap/skymap");
    // ResourceManager::loadVF("skybox", 
    //                         "Resources/Shaders/Skybox/skybox");
    // ResourceManager::loadVF("grassblade", 
    //                         "Resources/Shaders/GrassBlade/grassBlades");
    ResourceManager::loadVF("tests", "Resources/Shaders/Tests/test");
    // ResourceManager::GenALisht(ALIGHT_NAME, 0, glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0));
    // // ResourceManager::Load3D(SKY_TEX_NAME, SKYMAP_NAMES);
    // // Texture sky_tex = ResourceManager::getTexture(SKY_TEX_NAME);
    // staticmap = noise::getFile("Resources/Textures/DemoTerrainTestaticmap = noise::getFile("Resources/Textures/DemoTerrainTexture/TerrainMesh-bak3.ppm");
    
    // texture_vector sky_texs;
    // skymap = new Skymap(ResourceManager::getShader("skymap"));
    // skymap->setTextureSize(80, 80);
    // skymap->initialize();
    // skymap->bind();
    // skymap->update(glm::vec3(0.0, 0.1, -1.0), glm::vec3(1.0, 1.0, 1.0));
    // skymap->render();
    // skymap->unbind();
        
    // terrain  = new Terrain(0.0f, 0.0f, 50.0f, 50.0f, 20.0f, 8);
    // terrain2 = new Terrain(-50.0f, 0.0f, 50.0f, 50.0f, 20.0f, 8);
    // terrain3 = new Terrain(-50.0f, -50.0f, 50.0f, 50.0f, 20.0f, 8);
    // terrain4 = new Terrain(0.0f, -50.0f, 50.0f, 50.0f, 20.0f, 8);
    
    // skybox   = new Skybox(skymap->skymap_texture, ResourceManager::getShader("skybox"));
    
    // cam      = new Camera(glm::vec3(0.0f, 15.0f, 50.0f));
    
    // grass = new GrassBlade(glm::vec3(.2f, .8f, .2f), glm::vec2(0.0), glm::vec2(10.0, 10.0), 2.0, ResourceManager::getShader("grassblade"));

    // terrain->setOctave( 11);
    // terrain2->setOctave(11);
    // terrain3->setOctave(11);
    // terrain4->setOctave(11);

    // terrain2->setEdge(Terrain::PLACEMENT::POSX, terrain);
    // terrain3->setEdge(Terrain::PLACEMENT::POSZ, terrain2);
    // terrain4->setEdge(Terrain::PLACEMENT::NEGX, terrain3);    
    // terrain4->setEdge(Terrain::PLACEMENT::POSZ, terrain);
    
    // terrain->staticGenerate(staticmap, texture_vector{ }, 3.0);
    // // terrain->generate(texture_vector{ } , 1.0);
    // terrain2->generate(texture_vector{ }, 3.0);
    // terrain3->generate(texture_vector{ }, 3.0);
    // terrain4->generate(texture_vector{ }, 3.0);
    
    testmap = new NPMT();
    testmap->init();

    mmove = std::bind(&DemoScene::mouseMovecallback, this, std::placeholders::_1, std::placeholders::_2);
    mscroll = std::bind(&DemoScene::scrollcallback, this, std::placeholders::_1);
    kup = std::bind(&DemoScene::keyUp, this);
    kdn = std::bind(&DemoScene::keyDown, this);
    klf = std::bind(&DemoScene::keyLeft, this);
    krt = std::bind(&DemoScene::keyRight, this);
    Input::bindMousemoveCallback(&mmove);
    Input::bindScrollCallback(&mscroll);
    Input::bindKeydownCallback(Input::Keys::KEY_W, &kup);
    Input::bindKeydownCallback(Input::Keys::KEY_S, &kdn);
    Input::bindKeydownCallback(Input::Keys::KEY_A, &klf);
    Input::bindKeydownCallback(Input::Keys::KEY_D, &krt);
}

void DemoScene::destory() {
    terrain->destroy();
    delete terrain;
    delete cam;
}

void DemoScene::update() { }

void DemoScene::mouseMovecallback(float xpos, float ypos) {
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

void DemoScene::scrollcallback(float yoffset) {
    cam->ProcessMouseScroll(yoffset);
}

void DemoScene::keyUp() {
    cam->ProcessKeyboard(Camera::Camera_Movement::FORWARD, Context::delta_time);
}
void DemoScene::keyDown() {
    cam->ProcessKeyboard(Camera::Camera_Movement::BACKWARD, Context::delta_time);
}
void DemoScene::keyLeft() {
    cam->ProcessKeyboard(Camera::Camera_Movement::LEFT, Context::delta_time);
}
void DemoScene::keyRight() {
    cam->ProcessKeyboard(Camera::Camera_Movement::RIGHT, Context::delta_time);
}