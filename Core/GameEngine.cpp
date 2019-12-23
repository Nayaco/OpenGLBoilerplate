#include "GameEngine.hpp"

#include "Core/ExceptionHandle/ErrLog.hpp"
std::string  GameEngine::window_name;
unsigned int GameEngine::window_width;
unsigned int GameEngine::window_height;

float GameEngine::game_time;
float GameEngine::delta_time;
float GameEngine::current_frame;
float GameEngine::last_frame;

BaseScene* GameEngine::scene;

void GameEngine::resizeWindowCallback(GLFWwindow* window, int width, int height) {
    window_width = width;
    window_height = height;
    glViewport(0, 0, width, height);
}

void GameEngine::handleDeltaFrame() {
    current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
    game_time += delta_time;
}

void GameEngine::setname(std::string w_name) {
    window_name = w_name;
}

void GameEngine::setsize(unsigned int w_width, unsigned int w_height) {
    window_width = w_width;
    window_height = w_height;
}

void GameEngine::bindScene(BaseScene* _scene) {
    scene = _scene;
}

void GameEngine::initialize() {
    game_time     = 0.0f;
    delta_time    = 0.0f;
    last_frame    = 0.0f;
    current_frame = 0.0f;
    Input::bind();
    scene->initialize();
}

void GameEngine::createContex() {
    Context::create(window_name, window_width, window_height, 
                    GAME_GL_MAJOR_VERSION, GAME_GL_MINOR_VERSION, GAME_GL_SAMPLE_RATE);
}

void GameEngine::start_render() {
    while (!glfwWindowShouldClose(Context::getWindow())) {
        handleDeltaFrame();
        glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->draw();

        glfwSwapBuffers(Context::getWindow());
        glfwPollEvents();
    }
    glfwTerminate();
}