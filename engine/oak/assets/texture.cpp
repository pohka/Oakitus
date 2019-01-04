#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "stb_image.h"

#include "texture.h"
#include <oak/oak_def.h>
#include <oak/build_def.h>
#ifdef DEBUG_MODE
  #include <oak/debug.h>
#endif
#include <oak/core/resources.h>

using namespace oak;

Texture::Texture(std::string src, bool isEngineAsset) : Asset(src, isEngineAsset)
{
  load();
}

void Texture::load()
{
  std::string fullPath;

  if (isEngineAsset)
  {
    fullPath += ENGINE_RESOURCES_ROOT_PATH;
  }
  else
  {
    fullPath += Resources::rootPath;
  }
  fullPath += name;

  //load the texture
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int nrChannels;

  unsigned char *data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);

  if (data)
  {
    if (strstr(fullPath.c_str(), ".jpg") != NULL)
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
#ifdef DEBUG_MODE
    std::cout << "Failed load image: " << name << std::endl;
#endif
    stbi_image_free(data);
    unsigned char *data = stbi_load("../resources/default.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  }

  stbi_image_free(data);
}

Texture::~Texture() 
{
  glDeleteTextures(1, &id);
}

int Texture::getHeight() const
{
  return height;
}

int Texture::getWidth() const
{
  return width;
}
