#include "GameEngine.hpp"

GameEngine::GameEngine(string w_name)
    :window_width(DEFAULT_SCREEN_WIDTH), window_height(DEFAULT_SCREEN_HEIGHT), window_name(w_name) {    
}

GameEngine::GameEngine(unsigned int w_width, unsigned int w_height, string w_name)
    :window_width(w_width), window_height(w_height), window_name(w_name) {
}

void GameEngine::init() {
}

void GameEngine::createWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 16);
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_name.c_str(), NULL, NULL);
    if (isNull((void*)window)) {
        throw "GAMEENGINE: window " + window_name + " create failed";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window ,resizeWindowCallback);
    glfwSetCursorPosCallback(window, mouseMovecallback);
    glfwSetScrollCallback(window, scrollcallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {    
        glfwTerminate(); 
    }
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void mouseMovecallback(GLFWwindow* window, double xpos, double ypos) {
}

void resizeWindowCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void scrollcallback(GLFWwindow* window, double xoffset, double yoffset) {
}