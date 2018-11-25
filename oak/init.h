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

    Camera::init(
      glm::vec3(0.0f, 0.0f, 5.0f), //position
      glm::vec3(0.0f, 0.0f, -1.0f), //front
      glm::vec3(0.0f, 1.0f, 0.0f), //up
      90.0f, //field or view
      true
    );

   // Shader *shader = new Shader("default", "sample_texture.vs", "sample_texture.fs");
  //  Store::addShader(*shader);
    //Store::defaultShaderID = shader->getID();
  }
}

#endif