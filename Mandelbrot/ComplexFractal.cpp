#include <iostream>
#include <algorithm>
#include <string>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>

#include "ComplexFractal.h"
#include "Shader.h"



ComplexFractal::ComplexFractal(const int window_width, const int window_height) :
  _window_width(window_width),
  _window_height(window_height),
  _window(nullptr),
  _shader(nullptr),
  _vertices{-1.0, -1.0, 0.0, -2.0, -2.0,
             1.0, -1.0, 0.0,  2.0, -2.0,
             1.0,  1.0, 0.0,  2.0,  2.0,
            -1.0,  1.0, 0.0, -2.0,  2.0},
  _indices{0, 1, 3, 
           1, 2, 3},
  _vbo(0),
  _vao(0),
  _ebo(0),
  _zoom(1.0),
  _max_iterations(500),
  _camera_position(0.0, 0.0, 0.0),
  _position_correction(0.0, 0.0, 0.0),
  _transform(1.0) { }

ComplexFractal::~ComplexFractal() { }

bool ComplexFractal::init(int options) {
  // Change the settings according to user Options
  _FractalOptions opt = setup_options(options);

  // initialize OpenGL
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create a window
  _window = glfwCreateWindow(_window_width, _window_height, opt.window_title.c_str(), NULL, NULL);
  if (_window == nullptr) {
    std::cout << "Failed to create GLFW window" << '\n';
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(_window);

  // initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << '\n';
    return false;
  }

  glViewport(0, 0, _window_width, _window_height);
  glfwSetFramebufferSizeCallback(_window, complex_fractal_framebuffer_size);

  // build and compile the shader
  _shader = new Shader((opt.shader_name + ".vert").c_str(), (opt.shader_name + ".frag").c_str());
  _shader->use();
  _shader->set_uniform("max_iterations", _max_iterations);
  _shader->set_uniform("div", 12.0f, 15.0f, 5.0f);

  // get the vertex information
  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &_vbo);
  glGenBuffers(1, &_ebo);

  glBindVertexArray(_vao);

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(3 * sizeof(double)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return true;
}

void ComplexFractal::shutdown() { 
  glDeleteVertexArrays(1, &_vao);
  glDeleteBuffers(1, &_vbo);

  glfwTerminate();
}

void ComplexFractal::plot() { 
  while (!glfwWindowShouldClose(_window)) {
    process_input();
    update_plot();
    render_plot();
  }
}

_FractalOptions ComplexFractal::setup_options(int options) {
  _FractalOptions ret;
  if (options & FractalParam::Fractal_mandelbrot) {
    ret.window_title = "Mandelbrot Plot";
    ret.shader_name = "mandelbrot";
  } else if (options & FractalParam::Fractal_julia) {
    ret.window_title = "Julia Plot";
    ret.shader_name = "julia";
  }
  return ret;
}

void ComplexFractal::process_input() {

  if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(_window, true);
  }
  if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
    _camera_position.y -= .001 / _zoom;
  }
  if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
    _camera_position.y += .001 / _zoom;
  }
  if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
    _camera_position.x += .001 / _zoom;
  }
  if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
    _camera_position.x -= .001 / _zoom;
  }
  if (glfwGetKey(_window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
    _zoom += .01 * _zoom;
  }
  if (glfwGetKey(_window, GLFW_KEY_MINUS) == GLFW_PRESS) {
    _zoom -= .01 * _zoom;
  }
}

void ComplexFractal::update_plot() { 
  glm::vec3 correction = glm::vec3(_camera_position.x * (1-_zoom), 
                                   _camera_position.y * (1-_zoom), 
                                   0.0);
  _transform = glm::mat4(1.0);
  _transform = glm::translate(_transform, _camera_position - correction);
  _transform = glm::scale(_transform, glm::vec3(_zoom, _zoom, 1.0));
}

void ComplexFractal::render_plot() const { 
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  _shader->use();
  _shader->set_uniform("trans", _transform);
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void complex_fractal_framebuffer_size(class GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
