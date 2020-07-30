#include <cmath>

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Julia.h"
#include "Shader.h"

Julia::Julia() :
  _point(0.0, 0.0),
  ComplexFractal(1800, 1800, "Julia Set Plot", 100) { }

bool Julia::init_plot() {
  _shader = new Shader("julia.vert", "julia.frag");
  _shader->use();
  _shader->set_uniform("max_iterations", _max_iterations);
  _shader->set_uniform("div", 12.0f, 15.0f, 5.0f);
  _shader->set_uniform("c", _point);

  return true;
}

void Julia::shutdown_plot() { }

void Julia::process_plot_input() { 
  if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) {
    _point.y += 0.001;
  }
  if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    _point.y -= 0.001;
  }
  if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    _point.x += 0.001;
  }
  if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    _point.x -= 0.001;
  }
  if (glfwGetKey(_window, GLFW_KEY_P) == GLFW_PRESS) {
    std::cout << '(' << _point.x << ", " << _point.y << ')' << '\n';
  }
}

void Julia::update_plot() { }

void Julia::render_plot() const {
  // TODO?: Allow the point to change every loop

  _shader->use();
  _shader->set_uniform("c", _point);
  _shader->set_uniform("trans", _transform);
}
