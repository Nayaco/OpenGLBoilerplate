#include "Context.hpp"
GLFWwindow  *Context::window;
std::string  Context::window_name;
unsigned int Context::window_width;
unsigned int Context::window_height;

void Context::create(std::string w_name, unsigned int w_width, unsigned int w_height, 
                    unsigned int gl_major, unsigned int gl_minor, unsigned int gl_sample) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major); // CONFIG_HPP DEFINES
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor); // CONFIG_HPP DEFINES
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, gl_sample);              // CONFIG_HPP DEFINES
    window = glfwCreateWindow(w_width, w_height, w_name.c_str(), NULL, NULL);
    
    if (window == nullptr) {
        throw "CONTEXT: window " + window_name + " create failed";
        glfwTerminate();
    } else {
        window_height = w_width;
        window_width = w_height;
        window_name = w_name;

        glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {    
            throw "GAMEENGINE: window " + window_name + " create failed when load glad";
            glfwTerminate(); 
        }
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
}

GLFWwindow* Context::getWindow() { return window; }

void Context::destroy() { glfwTerminate(); }

void Context::updateWindow(unsigned int w_width, unsigned int w_height) {
    window_height = w_width;
    window_width = w_height;
    glViewport(0, 0, window_width, window_height);
}