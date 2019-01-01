#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <oak/core/component.h>
#include <string>
#include <oak/core/types.h>



namespace oak
{
  class Animator;

  class SpriteAnimation
  {
    uint textureID;
    uint shaderID;
    uint frameW;
    uint frameH;
    uint displayW;
    uint displayH;
    float frameDuration;

    uint VAO;
    uint VBO;
    uint maxFramesX;
    uint maxFramesY;
    uint startFrameY;
    uint curFrameX;
    uint curFrameY;
    uint totalFrameCount;
    bool isLooping;
    uchar priority;
    

    public:
      SpriteAnimation(
        std::string src,
        uchar priority,
        uint frameW,
        uint frameH,
        uint displayW,
        uint displayH,
        float frameDuration,
        uint shaderID,
        uint totalFrameCount,
        uint startFrameY,
        bool isLooping
      );
      ~SpriteAnimation();

      //load the texcture
      void load();

      //render at world position
      void onRender(float positionX, float positionY) const;

      //returns the priority of the animation
      uchar getPriority() const;

      //returns a pointer to the animator which owns this animation
      Animator* animator;

      //returns the duration of a frame in the current animation
      float getFrameDuration() const;

      //returns the number of frames in the current animation
      uint getFrameCount() const;

      //returns true if the current animation is a looping animation
      bool getIsLooping() const;

      //generates and binds the VBO for the specified frame
      void setFrame(const uint frameIndex, const uchar direction);

    private:
      //setup of vertex attributes layout
      void setVertexAttrs() const;
  };
}
#endif