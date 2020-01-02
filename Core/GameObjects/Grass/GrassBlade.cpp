#include "GrassBlade.h"

GLfloat GrassBlade::vertices[] =  {
             0.0f, 0.0f, -2.0f, // 0
            -1.0f, 0.0f,  0.0f, // 1
             1.0f, 0.0f,  0.0f, // 2
            -1.0f, 0.0f,  1.0f, // 3
             1.0f, 0.0f,  1.0f, // 4
            -1.0f, 0.0f,  2.0f, // 5
             1.0f, 0.0f,  2.0f, // 6
        };

GLint GrassBlade::indices[] = {
            0, 1, 2,
            2, 1, 3,
            2, 3, 4,
            4, 3, 5,
            4, 5, 6,
        };

GLfloat GrassBlade::normals[] = {
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
};

GLfloat GrassBlade::texCoord[] = {
    0.5f,  0.0f, // 0
    0.0f,  0.5f, // 1
    1.0f,  0.5f, // 2
    0.0f, 0.75f, // 3
    1.0f, 0.75f, // 4
    0.0f,  1.0f, // 5
    1.0f,  1.0f  // 6
};

GrassBlade::GrassBlade(glm::vec3 _scale, glm::vec3 center, glm::vec2 size, float density, Shader const& shader, imap2d const &heightmap, float y_axis_offset) 
    :grassShader(shader)
    {
    srand(time(0));
    // generate the noise
    imap2d noise_val = noise_gen.get_2D_noise(256, 256, -1.0f, 1.0f, -1.0f, 1.0f);
    tex_wind_noise.set_data(noise_val);

    initBuffers();
    // init the instances 
    glm::vec2 grassPerSide = density * size;

    for (size_t i = 0; i < grassPerSide.x; i++) {
        for (size_t j = 0; j < grassPerSide.y; j++) {
        GrassElement *ge = new GrassElement();
        ge->init_matrices(); //load the matrices

        Transform t;
        float pos_x = -(size.x / 2.0f) * (1 - (float(i) / (grassPerSide.x - 1))) 
                    + (size.x / 2.0f) * (float(i) / (grassPerSide.x - 1));
        float pos_y = -(size.y / 2.0f) * (1 - (float(j) / (grassPerSide.y - 1))) 
                    + (size.y / 2.0f) * (float(j) / (grassPerSide.y - 1));

        int val_rand = rand() % 1000;
        float frand = float(val_rand) / 1000.0f;

        pos_x += frand / 10.0f - 0.05;
        pos_y += frand / 10.0f - 0.05;
        
        float the_x = (float)i / density;
        float the_y = (float)j / density;
        float the_left = floor(the_x);
        float the_right = ceil(the_x);
        float the_down = floor(the_y);
        float the_top = ceil(the_y);

        if (the_left >= size.x) the_left = size.x - 1;
        if (the_right >= size.x) the_right = size.x - 1;
        if (the_down >= size.y) the_down = size.y - 1;
        if (the_top >=  size.y) the_top = size.y - 1;
        
        float the_horizon_down = noise::lerp(heightmap[(int)the_left][(int)the_down], heightmap[(int)the_right][(int)the_down], glm::min(the_x - the_left, 1.0f));
        float the_horizon_up = noise::lerp(heightmap[(int)the_left][(int)the_top], heightmap[(int)the_right][(int)the_top], glm::min(the_x - the_left, 1.0f));

        float the_verticle = noise::lerp(the_horizon_down, the_horizon_up, glm::min(the_y - the_down, 1.0f));

        t.translate(center);
        if (the_verticle > 0.05) {
            t.translate(pos_x, the_verticle * y_axis_offset - 3.8, pos_y);
        } else {
            t.translate(pos_x, the_verticle * y_axis_offset - 3.8 - the_verticle * 10.0, pos_y);
        }
        t.rotate(0.0, 1.0, 0.0, pos_x * pos_y * 5.244);
        t.scale(_scale);
        t.scale(1.0, 1.0 + frand, 1.0);
        t.translate(0, 2.0, 0);
        ge->set_model_matrix(t.get_matrix());
        
        //the matrix given by ge has the transfor and the grass model transforms
        if (the_verticle < 0.13)
            modelMats.push_back(ge->get_transf_0());
        }
    }
    //texture data definition
    //perlin noise for the wind
    glGenTextures(1, &_tex_wind_noise);
    glBindTexture(GL_TEXTURE_2D, _tex_wind_noise);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, tex_wind_noise.get_width(), tex_wind_noise.get_height(), 0, GL_RED, GL_FLOAT, tex_wind_noise.get_tex_data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //can be clamp to edge, clamp to border or gl repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    GLuint tex_id = glGetUniformLocation(grassShader.ID, "tex_wind");
    glUniform1i(tex_id, 1 /*GL_TEXTURE1*/);

    glBindTexture(GL_TEXTURE_2D, 0);

    wind_dir[0] = wind_dir[1] = 0.0f;

    //list of matrices for instanced drawing
    //   printf("will draw %lu grass\n", modelMats.size());
    grassNumber = modelMats.size();

    glm::mat4x4 *matArrayBuffer = new glm::mat4x4[modelMats.size()];
    for (size_t i = 0; i < grassNumber; i++) {
        matArrayBuffer[i] = modelMats[i];
    }

    //buffers the matrices
    GLuint _vbo_transf;
    glGenBuffers(1, &_vbo_transf);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo_transf);
    glBufferData(GL_ARRAY_BUFFER, grassNumber * sizeof(glm::mat4x4), matArrayBuffer, GL_STATIC_DRAW);

    uint32_t vec4_size = sizeof(glm::vec4);

    //tells opengl about the format of matrix (4x4), have to be done for each rows
    GLuint modelMatAttrib0 = glGetAttribLocation(grassShader.ID, "model_mat");

    glEnableVertexAttribArray(modelMatAttrib0);
    glVertexAttribPointer(modelMatAttrib0, 4, GL_FLOAT, GL_FALSE, 4 * vec4_size, (void*)0);

    glEnableVertexAttribArray(modelMatAttrib0+1);
    glVertexAttribPointer(modelMatAttrib0 + 1, 4, GL_FLOAT, GL_FALSE, 4 * vec4_size, (void*)(uintptr_t)(vec4_size));

    glEnableVertexAttribArray(modelMatAttrib0+2);
    glVertexAttribPointer(modelMatAttrib0 + 2, 4, GL_FLOAT, GL_FALSE, 4 * vec4_size, (void*)(uintptr_t)(2 * vec4_size));

    glEnableVertexAttribArray(modelMatAttrib0+3);
    glVertexAttribPointer(modelMatAttrib0 + 3, 4, GL_FLOAT, GL_FALSE, 4 * vec4_size, (void*)(uintptr_t)(3 * vec4_size));

    glVertexAttribDivisor(modelMatAttrib0, 1);
    glVertexAttribDivisor(modelMatAttrib0 + 1, 1);
    glVertexAttribDivisor(modelMatAttrib0 + 2, 1);
    glVertexAttribDivisor(modelMatAttrib0 + 3, 1);

    glBindVertexArray(0);

    grassNumber = modelMats.size();
    modelMats.clear();
    delete[] matArrayBuffer;
}

void GrassBlade::initBuffers(){
    //  gen & bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // bind position buffer
    glGenBuffers(1, &VBO_Pos);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // set position buffer
    GLuint posID = glGetAttribLocation(grassShader.ID, "position");
    glEnableVertexAttribArray(posID);
    glVertexAttribPointer(posID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint idxID;
    glGenBuffers(1, &idxID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // bind uv buffer
    GLuint uvVBO;
    glGenBuffers(1, &uvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);
    // set uv buffer
    GLuint uvID = glGetAttribLocation(grassShader.ID, "uv");
    glEnableVertexAttribArray(uvID);
    glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GrassBlade::setupShader() {
    grassShader.use();
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _tex_wind_noise);

    GLuint tex_id = glGetUniformLocation(grassShader.ID, "tex_wind");
    glUniform1i(tex_id, 1 /*GL_TEXTURE1*/);
    glUniform2fv( glGetUniformLocation(grassShader.ID, "wind_dir"), 1,this->wind_dir);
    grassShader.setFloat("min_pos", -20.0f);
    grassShader.setFloat("manx_pos", 20.0f);
    grassShader.setMat4("view", view_matrix);
    grassShader.setMat4("projection", projection_matrix);
    grassShader.setVec3("light_position", light_position);
    grassShader.setVec3("camera_position", camera_position);
}

void GrassBlade::render() {

    //coutner for the grass blades (which pixel to access)
    wind_dir[0] += 0.0004f;
    if(wind_dir[0] > 40.0f){
        wind_dir[0] = 0;
    }

    wind_dir[1] += 0.0002f;
    if(wind_dir[1] > 40.0f){
        wind_dir[1] = 0;
    }

    glDisable(GL_CULL_FACE);
    glBindVertexArray(VAO);

    setupShader();

    //one call for all the grass with instance drawing
    glDrawElementsInstanced(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0, grassNumber);

    // reset to default
    glEnable(GL_CULL_FACE);
    glBindVertexArray(0);
    glUseProgram(0);
}

void GrassBlade::setLightPos(glm::vec3 position){
    this->light_position = position;
}

void GrassBlade::setCameraPos(glm::vec3 position){
    this->camera_position = position;
}

void GrassBlade::setViewMatrix(glm::mat4 view){
      this->view_matrix = view;
}

void GrassBlade::setProjectionMatrix(glm::mat4 projection){
      this->projection_matrix = projection;
}