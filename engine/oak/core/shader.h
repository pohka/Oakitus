#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include "types.h"

namespace oak
{
  ///<summary>Loads and manages a vertex and fragement shader for OpenGL</summary>
  class Shader
  {
    public:

      // constructor generates the shader on the fly
      // ------------------------------------------------------------------------
      Shader(std::string name, bool isOnHeap = true, const char* geometryPath = nullptr);

      void load();

      // activate the shader
      // ------------------------------------------------------------------------
      void use();

      // utility uniform functions
      // ------------------------------------------------------------------------
      void setBool(const std::string &name, bool value) const;
      void setInt(const std::string &name, int value) const;
      void setFloat(const std::string &name, float value) const;
      void setVec2(const std::string &name, const glm::vec2 &value) const;
      void setVec2(const std::string &name, float x, float y) const;
      void setVec3(const std::string &name, const glm::vec3 &value) const;
      void setVec3(const std::string &name, float x, float y, float z) const;
      void setVec4(const std::string &name, const glm::vec4 &value) const;
      void setVec4(const std::string &name, float x, float y, float z, float w);
      void setMat2(const std::string &name, const glm::mat2 &mat) const;
      void setMat3(const std::string &name, const glm::mat3 &mat) const;
      void setMat4(const std::string &name, const glm::mat4 &mat) const;

      uint getID() const;
      std::string getName() const;

    private:
      uint ID;
      std::string name;
      const char* geometryPath;
      // utility function for checking shader compilation/linking errors.
      // ------------------------------------------------------------------------
      void checkCompileErrors(GLuint shader, std::string type);
  };
}
#endif