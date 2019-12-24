#include "DemoScene.hpp"

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

    render_shader.use();
    render_shader.setMat4("projection", projection);
    render_shader.setMat4("view", view);

    terrain->draw(render_shader);
    
    sky_shader.use();
    view = glm::mat4(glm::mat3(view));
    sky_shader.setMat4("projection", projection);
    sky_shader.setMat4("view", view);
    skybox->draw(sky_shader);
}

void DemoScene::initialize() {
    ResourceManager::loadVF(TER_SHADER_NAME, TER_SHADER);
    ResourceManager::loadVF(SKY_SHADER_NAME, SKY_SHADER);
    ResourceManager::Load3D(SKY_TEX_NAME, SKYMAP_NAMES);

    Texture sky_tex = ResourceManager::getTexture(SKY_TEX_NAME);

    terrain = new Terrain(0.0f, 0.0f, 50.0f, 50.0f, 10.0f, 8);
    skybox = new Skybox(sky_tex);
    cam = new Camera(glm::vec3(0.0f, 15.0f, 50.0f));
    terrain->setOctave(10);
    terrain->generate(texture_vector{ });
    
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