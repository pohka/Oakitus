#ifndef TEXTURE_H
#define TEXTURE_H

namespace oak
{
  class Texture
  {
    unsigned int id;
    int width, height;

    public:
      Texture(const char* src);
      ~Texture();
      int getHeight();
      unsigned int getID();
      int getWidth();


  };
}

#endif