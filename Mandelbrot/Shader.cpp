#include <fstream>
#include <sstream>
#include <iostream>

#include <glad\glad.h>

#include "Shader.h"

Shader::Shader(const char* vertex_path, const char* fragment_path) : _id(0) {
  // read in the shader source code
  std::string vert_str, frag_str;
  std::ifstream vert_file, frag_file;

  // allow the objects to throw exceptions
  vert_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  frag_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  // read in the source code from the shaders
  try {
    vert_file.open(vertex_path);
    frag_file.open(fragment_path);
    std::stringstream vert_stream, frag_stream;

    vert_stream << vert_file.rdbuf();
    frag_stream << frag_file.rdbuf();

    vert_file.close();
    frag_file.close();

    vert_str = vert_stream.str();
    frag_str = frag_stream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR: SHADER FILE NOT READ CORRECTLY" << '\n';
  }

  const char* vert_src = vert_str.c_str();
  const char* frag_src = frag_str.c_str();

  // compile the shaders
  unsigned int vertex_shader, fragment_shader;
  char info_log[512];
  int success;

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vert_src, nullptr);
  glCompileShader(vertex_shader);

  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
    std::cout << "ERROR COMPILING VERTEX SHADER: " << info_log << '\n';
  }

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &frag_src, nullptr);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
    std::cout << "ERROR COMPILING FRAGMENT SHADER: " << info_log << '\n';
  }

  // link and save the shaders into a program
  _id = glCreateProgram();
  glAttachShader(_id, vertex_shader);
  glAttachShader(_id, fragment_shader);
  glLinkProgram(_id);

  glGetProgramiv(_id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(_id, 512, nullptr, info_log);
    std::cout << "ERROR LINKING SHADER PROGRAM: " << info_log << '\n';
  }

  // delete the shaders that are already linked
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

Shader::~Shader() { }

unsigned int Shader::id() const {
  return _id;
}

void Shader::use() const { glUseProgram(_id); }

void Shader::set_uniform(const std::string& name, bool x) {
  glUniform1i(glGetUniformLocation(_id, name.c_str()), static_cast<int>(x));
}

void Shader::set_uniform(const std::string& name, int x) {
  glUniform1i(glGetUniformLocation(_id, name.c_str()), x);
}

void Shader::set_uniform(const std::string& name, float x) {
  glUniform1f(glGetUniformLocation(_id, name.c_str()), x);
}

void Shader::set_uniform(const std::string& name, double x) {
  glUniform1d(glGetUniformLocation(_id, name.c_str()), x);
}

void Shader::set_uniform(const std::string& name, bool x, bool y) {
  glUniform2i(glGetUniformLocation(_id, name.c_str()), static_cast<int>(x), static_cast<int>(y));
}

void Shader::set_uniform(const std::string& name, int x, int y) {
  glUniform2i(glGetUniformLocation(_id, name.c_str()), x, y);
}

void Shader::set_uniform(const std::string& name, float x, float y) {
  glUniform2f(glGetUniformLocation(_id, name.c_str()), x, y);
}

void Shader::set_uniform(const std::string& name, double x, double y) {
  glUniform2d(glGetUniformLocation(_id, name.c_str()), x, y);
}

void Shader::set_uniform(const std::string& name, const glm::vec2& A) { 
  glUniform2fv(glGetUniformLocation(_id, name.c_str()), 1, &A[0]);
}

void Shader::set_uniform(const std::string& name, bool x, bool y, bool z) {
  glUniform3i(glGetUniformLocation(_id, name.c_str()), static_cast<int>(x), static_cast<int>(y),
              static_cast<int>(z));
}

void Shader::set_uniform(const std::string& name, int x, int y, int z) {
  glUniform3i(glGetUniformLocation(_id, name.c_str()), x, y, z);
}

void Shader::set_uniform(const std::string& name, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z);
}

void Shader::set_uniform(const std::string& name, double x, double y, double z) {
  glUniform3d(glGetUniformLocation(_id, name.c_str()), x, y, z);
}

void Shader::set_uniform(const std::string& name, const glm::vec3& A) { 
  glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, &A[0]);
}

void Shader::set_uniform(const std::string& name, bool x, bool y, bool z, bool w) {
  glUniform4i(glGetUniformLocation(_id, name.c_str()), static_cast<int>(x), static_cast<int>(y),
              static_cast<int>(z), static_cast<int>(w));
}

void Shader::set_uniform(const std::string& name, int x, int y, int z, int w) {
  glUniform4i(glGetUniformLocation(_id, name.c_str()), x, y, z, w);
}

void Shader::set_uniform(const std::string& name, float x, float y, float z, float w) {
  glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w);
}

void Shader::set_uniform(const std::string& name, double x, double y, double z, double w) {
  glUniform4d(glGetUniformLocation(_id, name.c_str()), x, y, z, w);
}

void Shader::set_uniform(const std::string& name, const glm::vec4& A) {
  glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, &A[0]);
}

void Shader::set_uniform(const std::string& name, const glm::mat2& A) { 
  glUniformMatrix2fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &A[0][0]);
}

void Shader::set_uniform(const std::string& name, const glm::mat3& A) { 
  glUniformMatrix3fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &A[0][0]);
}

void Shader::set_uniform(const std::string& name, const glm::mat4& A) { 
  glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &A[0][0]);
}
