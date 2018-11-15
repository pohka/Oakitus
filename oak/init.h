#ifndef OAK_INIT_H
#define OAK_INIT_H


#define STB_IMAGE_IMPLEMENTATION
#include "oak.h"

namespace oak
{
  void initOak()
  {
    oak::Time::init();
    oak::Input::init();

    Oakitus::camera = new Camera(
      glm::vec3(0.0f, 0.0f, 3.0f), //position
      glm::vec3(0.0f, 0.0f, -1.0f), //front
      glm::vec3(0.0f, 1.0f, 0.0f), //up
      90.0f //field or view
    );

   // Shader *shader = new Shader("default", "sample_texture.vs", "sample_texture.fs");
  //  Oakitus::addShader(*shader);
    //Oakitus::defaultShaderID = shader->getID();
  }
}

#endif