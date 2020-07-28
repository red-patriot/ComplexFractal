#ifndef Shader_h_INCLUDED
#define Shader_h_INCLUDED

#include <string>

#include <glm\glm.hpp>

/**
 * \class Shader An object which compiles and stores a shader for rendering
 */
class Shader {
public:
  Shader(const char* vertex_path, const char* fragment_path);
  ~Shader();

  unsigned int id() const;

  void use() const;

  void set_uniform(const std::string& name, bool x);
  void set_uniform(const std::string& name, int x);
  void set_uniform(const std::string& name, float x);
  void set_uniform(const std::string& name, double x);

  void set_uniform(const std::string& name, bool x, bool y);
  void set_uniform(const std::string& name, int x, int y);
  void set_uniform(const std::string& name, float x, float y);
  void set_uniform(const std::string& name, double x, double y);
  void set_uniform(const std::string& name, const glm::vec2& A);

  void set_uniform(const std::string& name, bool x, bool y, bool z);
  void set_uniform(const std::string& name, int x, int y, int z);
  void set_uniform(const std::string& name, float x, float y, float z);
  void set_uniform(const std::string& name, double x, double y, double z);
  void set_uniform(const std::string& name, const glm::vec3& A);

  void set_uniform(const std::string& name, bool x, bool y, bool z, bool w);
  void set_uniform(const std::string& name, int x, int y, int z, int w);
  void set_uniform(const std::string& name, float x, float y, float z, float w);
  void set_uniform(const std::string& name, double x, double y, double z, double w);
  void set_uniform(const std::string& name, const glm::vec4& A);

  void set_uniform(const std::string& name, const glm::mat2& A);
  void set_uniform(const std::string& name, const glm::mat3& A);
  void set_uniform(const std::string& name, const glm::mat4& A);

private:
  unsigned int _id;
};

#endif
