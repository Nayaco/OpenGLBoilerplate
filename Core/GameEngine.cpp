#include "GameEngine.hpp"

void GameEngine::initialize() {
}

void GameEngine::createWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GAME_GL_MAJOR_VERSION); // CONFIG_HPP DEFINES
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GAME_GL_MINOR_VERSION); // CONFIG_HPP DEFINES
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, GAME_GL_SAMPLE_RATE); // CONFIG_HPP DEFINES
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_name.c_str(), NULL, NULL);
    if (tool::isNull((void*)window)) {
        throw "GAMEENGINE: window " + window_name + " create failed";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window , resizeWindowCallback);
    glfwSetCursorPosCallback(window, Input::mouseMovecallback);
    glfwSetScrollCallback(window, Input::scrollcallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {    
        throw "GAMEENGINE: window " + window_name + " create failed when load glad";
        glfwTerminate(); 
    }
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void GameEngine::resizeWindowCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
