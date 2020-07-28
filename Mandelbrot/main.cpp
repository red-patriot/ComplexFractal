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

#include "Shader.h"

#define MANDELBROT 1
#define JULIA 2

#define MODE JULIA

#include "ComplexFractal.h"

/**
 * \brief the resize callback function, which is called whenever the window resizes
 */
void framebuffer_size(GLFWwindow* window, int width, int height);
/**
 * \brief a callback to to handle all keyboard input
 */
void process_input(GLFWwindow* window);

const int window_width{1800}, window_height{1800};


// Global variables
glm::vec3 pos(0.0, 0.0, 0.0);            // The translated position of the image
glm::vec3 correction(0.0, 0.0, 0.0);     // This factor ensures the image does 
                                         //    not shift as it zooms in/out
double zoom = 1.0;                       // The zoom of the image
int max_iterations = 500;                // limit on the number of iterations
bool lazy = false;                       // a toggle for faster drawing but 
                                         //    lower quality

int asdfasdfasdf();

int main() {
  ComplexFractal fractal(window_width, window_height);
  fractal.init(Fractal_mandelbrot);

  fractal.plot();

  fractal.shutdown();

  //asdfasdfasdf();

  return 0;
}
 
int asdfasdfasdf() {
  // initialize OpenGL
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create a window
  GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Mandelbrot Plot", NULL, NULL);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << '\n';
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << '\n';
    return -1;
  }

  glViewport(0, 0, window_width, window_height);
  glfwSetFramebufferSizeCallback(window, framebuffer_size);

  // shader
#if MODE == MANDELBROT
  Shader shader("mandelbrot.vert", "mandelbrot.frag");
#endif
#if MODE == JULIA
  Shader shader("julia.vert", "julia.frag");
#endif
  shader.use();
#if MODE == JULIA
  shader.set_uniform("c", -0.835f, -0.2321f);
#endif
  shader.set_uniform("max_iterations", max_iterations);
  shader.set_uniform("div", 12.0f, 15.0f, 5.0f);
  
  // graphics data
#if MODE == MANDELBROT
  double vertices[] = {
    // position       // coordinates
    1.0,  1.0,  1.0,  1.0,  1.5,
    -1.0, 1.0,  1.0,  -2.0, 1.5,
    -1.0, -1.0, 1.0,  -2.0, -1.5,
    1.0,  -1.0, 0.5,  1.0, -1.5,
  };
#endif
#if MODE == JULIA
  double vertices[] = {
    // position       // coordinates
    1.0,  1.0,  1.0,  2.0,  2.0,
    -1.0, 1.0,  1.0,  -2.0, 2.0,
    -1.0, -1.0, 1.0,  -2.0, -2.0,
    1.0,  -1.0, 0.5,  2.0, -2.0,
  };
#endif

  unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
  };

  unsigned int vbo, vao, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(3 * sizeof(double)));
  glEnableVertexAttribArray(1);

  while (!glfwWindowShouldClose(window)) {
    // handle input
    process_input(window);
    
    // clear the old screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // movement comands
    correction = glm::vec3(pos.x * (1-zoom), pos.y * (1-zoom), 0.0); 
    glm::mat4 trans(1.0);
    trans = glm::translate(trans, pos - correction);
    trans = glm::scale(trans, glm::vec3(zoom, zoom, 1.0));

    // rendering commands
    shader.use();
    shader.set_uniform("trans", trans);
    shader.set_uniform("lazy", lazy);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // display the screen
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}

void framebuffer_size(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    pos.y -= .001 / zoom;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    pos.y += .001 / zoom;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    pos.x += .001 / zoom;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    pos.x -= .001 / zoom;
  }
  if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
    zoom += .01 * zoom;
  }
  if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
    zoom -= .01 * zoom;
  }
  if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
    lazy = !lazy;
  }
}


/* TODO: Create classa(es) for management
 */
