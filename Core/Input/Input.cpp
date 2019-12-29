#include "Input.hpp"

std::list<std::function<void(float)>* > Input::scrollCallbacks;
std::list<std::function<void(float, float)>* > Input::mousemoveCallbacks;
std::list<Input::MouseClick> Input::clickCallbacks;
std::function<void()> *Input::onClick;

std::map<Input::Keys, std::list<std::function<void()>* > > Input::keyCallbacks;

static const Input::Keys KeyAll[] = {
    Input::Keys::KEY_W,
    Input::Keys::KEY_A,
    Input::Keys::KEY_S,
    Input::Keys::KEY_D,
    Input::Keys::KEY_F,

    Input::Keys::KEY_SPACE,
    Input::Keys::KEY_ESC,
    Input::Keys::KEY_ENTER,
    Input::Keys::KEY_Q,
    Input::Keys::KEY_P,

    Input::Keys::KEY_UP,
    Input::Keys::KEY_DOWN,
    Input::Keys::KEY_LEFT,
    Input::Keys::KEY_RIGHT,
};


void Input::bind() {
    glfwSetWindowSizeCallback(Context::getWindow() , resizeWindowCallback);
    glfwSetCursorPosCallback(Context::getWindow(), mouseMoveCallback);
    glfwSetScrollCallback(Context::getWindow(), scrollCallback);
    glfwSetInputMode(Context::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::bindMousemoveCallback(std::function<void(float, float)>* func) {
    mousemoveCallbacks.emplace_back(func);
}
void Input::bindScrollCallback(std::function<void(float)>* func) {
    scrollCallbacks.emplace_back(func);
}
void Input::bindKeydownCallback(Keys key, std::function<void()>* func) {
    auto keyInsertPos = keyCallbacks.find(key);
    if (keyInsertPos == keyCallbacks.end()) {
        keyCallbacks.emplace(std::make_pair(key, std::list<std::function<void()>*>{func} ));
    } else {
        keyInsertPos->second.emplace_back(func);
    }
}

void Input::resizeWindowCallback(GLFWwindow* window, int width, int height) {
    Context::updateWindow(width, height);
}

void Input::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    for (auto &mouseMoveFunc : mousemoveCallbacks) {
        (*mouseMoveFunc)(xpos, ypos);
    }
}
void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    for (auto &scrollFunc : scrollCallbacks) {
        (*scrollFunc)(yoffset);
    }
}
void Input::processKeyInput() {
    for(auto key : KeyAll) {
        if (glfwGetKey(Context::getWindow(), key) == GLFW_PRESS) {
        if (keyCallbacks.find(key) != keyCallbacks.end()) {
            for(auto keyFunc : keyCallbacks[key]) {
                (*keyFunc)();
            }
        }
        }
    }
}

