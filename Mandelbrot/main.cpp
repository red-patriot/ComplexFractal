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
