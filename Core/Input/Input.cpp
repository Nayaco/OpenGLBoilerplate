#include "Input.hpp"

std::list<std::function<void(float)>* > Input::scrollCallbacks;
std::list<std::function<void(float, float)>* > Input::mousemoveCallbacks;
std::list<Input::MouseClick> Input::clickCallbacks;
std::function<void()> *Input::onClick;

std::map<Input::Keys, std::list<std::function<void(float, float)>* > > Input::keyCallbacks;

void Input::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    // DO NOTHING
}
void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    // DO NOTHING
}
void Input::processKeyInput(GLFWwindow* window) {
    // DO NOTHING
}