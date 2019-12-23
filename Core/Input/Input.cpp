#include "Input.hpp"

std::list<std::function<void(float)>* > Input::scrollCallbacks;
std::list<std::function<void(float, float)>* > Input::mousemoveCallbacks;
std::list<Input::MouseClick> Input::clickCallbacks;
std::function<void()> *Input::onClick;

std::map<Input::Keys, std::list<std::function<void(float, float)>* > > Input::keyCallbacks;

void Input::bind() {
    glfwSetWindowSizeCallback(Context::getWindow() , resizeWindowCallback);
    glfwSetCursorPosCallback(Context::getWindow(), mouseMoveCallback);
    glfwSetScrollCallback(Context::getWindow(), scrollCallback);
    glfwSetInputMode(Context::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

// static void bindMousemoveCallback(std::function<void(float, float)>* func);
// static void bindScrollCallback(std::function<void(float)>* func);
// static void bindKeydownCallback(Keys key, std::function<void(float, float)>* func);


void Input::resizeWindowCallback(GLFWwindow* window, int width, int height) {
    Context::updateWindow(width, height);
}

void Input::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    // DO NOTHING
}
void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    // DO NOTHING
}
void Input::processKeyInput(GLFWwindow* window) {
    // DO NOTHING
}

