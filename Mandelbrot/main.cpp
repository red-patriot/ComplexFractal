/*****************************************************************//**
 * \file   main.cpp
 * \brief  The main function for the Mandelbrot Plotter
 * 
 * \author bltan
 * \date   June 2020
 *********************************************************************/

#include <iostream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Mandelbrot.h"
#include "Julia.h"

int asdfasdfasdf();

int main() {
  Julia fractal;
  fractal.init();

  fractal.plot();

  fractal.shutdown();

  return 0;
}
 
////#if MODE == MANDELBROT
////  Shader shader("mandelbrot.vert", "mandelbrot.frag");
////#endif
////#if MODE == JULIA
////  Shader shader("julia.vert", "julia.frag");
////#endif
////  shader.use();
////#if MODE == JULIA
////  shader.set_uniform("c", -0.835f, -0.2321f);
////#endif
////  shader.set_uniform("max_iterations", max_iterations);
////  shader.set_uniform("div", 12.0f, 15.0f, 5.0f); 
