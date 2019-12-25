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
    glm::mat4 projection = cam->GetProjectionMatrix();
    glm::mat4 view = cam->GetViewMatrix();
    
    Shader render_shader = ResourceManager::getShader(TER_SHADER_NAME);
    Shader sky_shader = ResourceManager::getShader(SKY_SHADER_NAME);
    // Shader test_shader = ResourceManager::getShader("test2");
    auto light = ResourceManager::getLight(ALIGHT_NAME);

    render_shader.use();
    render_shader.setMat4("projection", projection);
    render_shader.setMat4("view", view);
    render_shader.setVec3("viewpos", cam->GetViewPosition());
    light->enable();
    light->use(render_shader);

    terrain->draw(render_shader);
    terrain2->draw(render_shader);
    terrain3->draw(render_shader);
    terrain4->draw(render_shader);
    
    view = glm::mat4(glm::mat3(view));
    skybox->skybox_shader.use();
    skybox->skybox_shader.setMat4("projection", projection);
    skybox->skybox_shader.setMat4("view", view);
    skybox->draw();

    // sky_shader.use();
    // sky_shader.setMat4("projection", projection);
    // sky_shader.setMat4("view", view);
    // skybox->draw(sky_shader);

    // skymap->bind();
    // skymap->render(glm::vec3(0.0, 0.1, -1.0), glm::vec3(1.0, 1.0, 1.0));
    // skymap->unbind();

    // test_shader.use();
    // glBindVertexArray(quadVAO);
    // glBindTexture(GL_TEXTURE_2D, skymap->skymap_texture[0]._id);	// use the color attachment texture as the texture of the quad plane
    // glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DemoScene::initialize() {
    ResourceManager::loadVGF(TER_SHADER_NAME, TER_SHADER);
    ResourceManager::loadVF("test2", "Resources/Shaders/Test2/sc");
    ResourceManager::loadVF(SKY_SHADER_NAME, SKY_SHADER);
    ResourceManager::Load3D(SKY_TEX_NAME, SKYMAP_NAMES);
    ResourceManager::GenALisht(ALIGHT_NAME, 0, glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0));
    Texture sky_tex = ResourceManager::getTexture(SKY_TEX_NAME);
    
    texture_vector sky_texs;

    // ResourceManager::Load2D("001", "Resources/Textures/DemoSkyTexture/SkyTexture_rt.jpg");
    // ResourceManager::Load2D("002", "Resources/Textures/DemoSkyTexture/SkyTexture_lf.jpg");
    // ResourceManager::Load2D("003", "Resources/Textures/DemoSkyTexture/SkyTexture_up.jpg");
    // ResourceManager::Load2D("004", "Resources/Textures/DemoSkyTexture/SkyTexture_dn.jpg");
    // ResourceManager::Load2D("005", "Resources/Textures/DemoSkyTexture/SkyTexture_ft.jpg");
    // ResourceManager::Load2D("006", "Resources/Textures/DemoSkyTexture/SkyTexture_bk.jpg");
    
    
    // sky_texs.push_back(ResourceManager::getTexture("002"));
    // sky_texs.push_back(ResourceManager::getTexture("001"));
    // sky_texs.push_back(ResourceManager::getTexture("003"));
    // sky_texs.push_back(ResourceManager::getTexture("004"));
    // sky_texs.push_back(ResourceManager::getTexture("005"));
    // sky_texs.push_back(ResourceManager::getTexture("006"));

    skymap = new Skymap();
    skymap->initialize();
    skymap->bind();
    skymap->render(glm::vec3(0.0, 1.0, -1.0), glm::vec3(3.0, 3.0, 3.0));
    skymap->unbind();
    
    // logger.error("here");
    
    terrain = new Terrain(0.0f, 0.0f, 50.0f, 50.0f, 20.0f, 8);
    terrain2 = new Terrain(-50.0f, 0.0f, 50.0f, 50.0f, 20.0f, 8);
    terrain3 = new Terrain(-50.0f, -50.0f, 50.0f, 50.0f, 20.0f, 8);
    terrain4 = new Terrain(0.0f, -50.0f, 50.0f, 50.0f, 20.0f, 8);
    skybox = new Skybox(skymap->skymap_texture);
    // skybox = new Skybox(sky_texs);
    // skybox = new Skybox(sky_tex);
    cam = new Camera(glm::vec3(0.0f, 15.0f, 50.0f));
    
    terrain->setOctave(10);
    terrain2->setOctave(10);
    terrain3->setOctave(10);
    terrain4->setOctave(10);

    terrain2->setEdge(Terrain::PLACEMENT::POSX, terrain);
    terrain3->setEdge(Terrain::PLACEMENT::POSZ, terrain2);
    terrain4->setEdge(Terrain::PLACEMENT::NEGX, terrain3);    
    terrain4->setEdge(Terrain::PLACEMENT::POSZ, terrain);
    
    terrain->generate(texture_vector{ } , 1.0);
    terrain2->generate(texture_vector{ }, 1.0);
    terrain3->generate(texture_vector{ }, 1.0);
    terrain4->generate(texture_vector{ }, 1.0);
    
    
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

    
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void DemoScene::destory() {
    terrain->destroy();
    delete terrain;
    delete cam;
}

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