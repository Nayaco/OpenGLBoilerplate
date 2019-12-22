#include "GameEngine.hpp"

#include "Core/ExceptionHandle/ErrLog.hpp"
GLFWwindow  *GameEngine::window;
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
    game_time  = 0.0f;
    delta_time = 0.0f;
    last_frame = 0.0f;
    current_frame = 0.0f;
    scene->initialize();
}

void GameEngine::createWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GAME_GL_MAJOR_VERSION); // CONFIG_HPP DEFINES
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GAME_GL_MINOR_VERSION); // CONFIG_HPP DEFINES
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, GAME_GL_SAMPLE_RATE); // CONFIG_HPP DEFINES
    window = glfwCreateWindow(window_width, window_height, window_name.c_str(), NULL, NULL);
    if (tool::isNull((void*)window)) {
        throw "GAMEENGINE: window " + window_name + " create failed";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window , resizeWindowCallback);
    glfwSetCursorPosCallback(window, Input::mouseMoveCallback);
    glfwSetScrollCallback(window, Input::scrollCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {    
        throw "GAMEENGINE: window " + window_name + " create failed when load glad";
        glfwTerminate(); 
    }
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void GameEngine::start_render() {
    // Shader ourShader("Resources/Shaders/Test/Test.vert.glsl", "Resources/Shaders/Test/Test.frag.glsl");
    // float vertices[] = {
    //     // positions         // colors
    //      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
    //      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    // };

    // unsigned int VBO, VAO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) {
        handleDeltaFrame();
        glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->draw();
        // ourShader.use();
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}