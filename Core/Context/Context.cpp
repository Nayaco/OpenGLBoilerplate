#include "Context.hpp"

GLFWwindow *Context::window;
std::string  Context::window_name;
unsigned int Context::window_width;
unsigned int Context::window_height;

float Context::game_time;
float Context::delta_time;
float Context::current_frame;
float Context::last_frame;

GLFWwindow *Context::getWindow() { return window; }

void Context::create(std::string w_name, unsigned int w_width, unsigned int w_height,
                     unsigned int gl_major, unsigned int gl_minor, unsigned int gl_sample) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major); // CONFIG_HPP DEFINES
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor); // CONFIG_HPP DEFINES
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, gl_sample);              // CONFIG_HPP DEFINES
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif
    window = glfwCreateWindow(w_width, w_height, w_name.c_str(), NULL, NULL);

    if (window == nullptr) {
        throw "CONTEXT: window " + window_name + " create failed";
        glfwTerminate();
    } else {
        window_height = w_height;
        window_width = w_width;
        window_name = w_name;

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            throw "GAMEENGINE: window " + window_name + " create failed when load glad";
            glfwTerminate();
        }
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
    game_time = 0.0f;
    delta_time = 0.0f;
    last_frame = 0.0f;
    current_frame = 0.0f;
}

void Context::close() { glfwSetWindowShouldClose(window, true); }

void Context::destroy() { glfwTerminate(); }

void Context::update() {
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    handleDeltaFrame();
}

bool Context::shouldClose() { return glfwWindowShouldClose(window); }

void Context::swapbuffer() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Context::updateWindow(unsigned int w_width, unsigned int w_height) {
    window_height = w_height;
    window_width = w_width;
    glViewport(0, 0, window_width, window_height);
}

void Context::handleDeltaFrame() {
    current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
    game_time += delta_time;
}