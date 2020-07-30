#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "Mandelbrot.h"
#include "Shader.h"

Mandelbrot::Mandelbrot() : 
  ComplexFractal(1800, 1800, "Mandelbrot Plot") { }

bool Mandelbrot::init_plot() {
  _shader = new Shader("mandelbrot.vert", "mandelbrot.frag");
  _shader->use();
  _shader->set_uniform("max_iterations", _max_iterations);
  _shader->set_uniform("div", 12.0f, 15.0f, 5.0f);

  return true;
}

void Mandelbrot::shutdown_plot() { }

void Mandelbrot::process_plot_input() { }

void Mandelbrot::update_plot() { }

void Mandelbrot::render_plot() const { 
  _shader->use();
  _shader->set_uniform("trans", _transform);
}
