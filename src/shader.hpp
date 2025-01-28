#ifndef SHADER_H
#define SHADER_H

#include "object.hpp"
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Shader {
public:
  // the program ID
  unsigned int ID;
  std::vector<class std::reference_wrapper<Object>> usedBy;

  // constructor reads and builds the shader
  Shader(const char *vertexPath, const char *fragmentPath);
  // use/activate the shader
  void use() const;
  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMat4(const std::string &name, glm::mat4 value) const;

private:
  static void checkCompileErrors(unsigned int shader, const std::string &type);
};

#endif