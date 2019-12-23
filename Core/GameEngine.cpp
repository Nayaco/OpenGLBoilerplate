#include "GameEngine.hpp"

#include "Core/ExceptionHandle/ErrLog.hpp"
std::string  GameEngine::window_name;
unsigned int GameEngine::window_width;
unsigned int GameEngine::window_height;

BaseScene* GameEngine::scene;

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
    Input::bind();
    scene->initialize();
}

void GameEngine::createContext() {
    Context::create(window_name, window_width, window_height, 
                    GAME_GL_MAJOR_VERSION, GAME_GL_MINOR_VERSION, 
                    GAME_GL_SAMPLE_RATE);
}

void GameEngine::start_render() {
    while (!glfwWindowShouldClose(Context::getWindow())) {
        Context::update();
        Input::processKeyInput();
        glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->draw();

        glfwSwapBuffers(Context::getWindow());
        glfwPollEvents();
    }
    glfwTerminate();
}