#ifndef GRASS_ELEMENT_H
#define GRASS_ELEMENT_H

#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Utility/GrassUtils/Transform.hpp"

class GrassElement {
public:
   GrassElement(){
      all_transf[0] = &transf_0_front;
      all_transf[1] = &transf_0_back;
      all_transf[2] = &transf_1_front;
      all_transf[3] = &transf_1_back;

      wind_dir[0] = 2.0f;
      wind_dir[1] = 2.0f;
   }
   
   float *get_wind_dir(){
      return wind_dir;
   }

   void set_wind_dir(float wind_dir[2]){
      this->wind_dir[0] = wind_dir[0];
      this->wind_dir[1] = wind_dir[1];
   }

   void set_model_matrix(glm::mat4x4 model){
      this->model_matrix = model;
   }

   void init_matrices(){
      transf_0_front.rotate(0.0f, 1.0f, 0.0f, 3.1415f/4.0f);
      transf_0_front.rotate(1.0f, 0.0f, 0.0f, 3.1415f/2.0f);
      transf_0_back.rotate(0.0f, 1.0f, 0.0f,  5*3.1415f/4.0f);
      transf_0_back.rotate(1.0f, 0.0f, 0.0f,  3.1415f/2.0f);

      transf_1_front.rotate(0.0f, 1.0f, 0.0f, 3*3.1415f/4.0f);
      transf_1_front.rotate(1.0f, 0.0f, 0.0f, 3.1415f/2.0f);
      transf_1_back.rotate(0.0f, 1.0f, 0.0f,  7*3.1415f/4.0f);
      transf_1_back.rotate(1.0f, 0.0f, 0.0f,  3.1415f/2.0f);
   }

   glm::mat4 get_transf_0(){
      return model_matrix * transf_0_front.get_matrix();
   }

   glm::mat4 get_transf_1(){
      return model_matrix * transf_1_front.get_matrix();
   }
protected:
   float wind_dir[2];
   glm::mat4x4 model_matrix;
   Transform transf_0_front;
   Transform transf_0_back;
   Transform transf_1_front;
   Transform transf_1_back;
   Transform *all_transf[4];
};

#endif
