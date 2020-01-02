#include "Tower.hpp"
Tower::Tower() 
    :aabbbox(glm::vec3(2.0f, 12.0f, 2.0f))
    , model("Resources/Models/LightHouse/lightHouse.obj") {
    position = glm::vec3(9.5, 1.0, 9.5);
    center = glm::vec3(10.0, 1.0, 10.0);
    aabbbox.update(position);
}

void Tower::draw(Shader const &shader) {
    glm::mat4 model_matrix(1.0);
    model_matrix = glm::translate(model_matrix, center);
    model_matrix = glm::scale(model_matrix, glm::vec3(1.0, 1.0, 1.0) );
    shader.use();
    shader.setMat4("model", model_matrix);
    model.draw(shader);
}