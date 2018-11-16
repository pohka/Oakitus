#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>

#include "texture.h"

using namespace oak;

Texture::Texture(const char* src)
{
  //load the texture
  glGenTextures(1, &this->id);
  glBindTexture(GL_TEXTURE_2D, this->id);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int nrChannels;

  
  unsigned char *data = stbi_load(src, &width, &height, &nrChannels, 0);

  if (strstr(src, ".jpg") != NULL) {
    std::cout << "image is jpg" << std::endl;
  }
  
if (data)
  {
    if (strstr(src, ".jpg") != NULL) 
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
  }
  else
  {
    std::cout << "Failed load image: " << src << std::endl;
    stbi_image_free(data);
    unsigned char *data = stbi_load("default.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  }
  
  stbi_image_free(data);
}

Texture::~Texture() 
{

}

int Texture::getHeight()
{
  return height;
}

uint Texture::getID()
{
  return id;
}

int Texture::getWidth()
{
  return width;
}