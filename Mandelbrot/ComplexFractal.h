#ifndef Complex_Fractal_h_INCLUDED
#define Complex_Fractal_h_INCLUDED

/*****************************************************************//**
 * \file   ComplexFractal.h
 * \brief  A class to manage plotting Complex Fractals
 * 
 * \author bltan
 * \date   July 2020
 *********************************************************************/

#include <glm\glm.hpp>

namespace {
  struct _FractalOptions {
    std::string window_title;
    std::string shader_name;
  };
};

enum FractalParam {
  Fractal_mandelbrot = 0b0001,
  Fractal_julia = 0b0010,
};

/**
 * \class ComplexFractal A class to manage the plotting of a fractal shape
 *   in the complex plane.
 */
class ComplexFractal { 
public:
  /**
   * \brief Construct a ComplexFractal
   * 
   * \param window_width the width in pixels of the window
   * \param window_height the height in pixels of the window
   */
  ComplexFractal(const int window_width, const int window_height);
  ~ComplexFractal();

  /**
   * Initialize necessary systems for plotting and displaying a complex fractal.
   * 
   * \param options optional parameters to change the plotting method of ComplexFractal
   * \return false if there was an error during initialization, true otherwise.
   */
  bool init(int options);
  /**
   * Shut down all systems and clean up memory.
   * 
   */
  void shutdown();

  /**
   * Plot the complex fractal
   */
  void plot();

private:
  /// OpenGL Parameters
  const int _window_width;
  const int _window_height;

  class GLFWwindow* _window;
  class Shader* _shader;

  /// Plot Parameters
  double _vertices[20];
  unsigned int _indices[6];

  unsigned int _vbo;
  unsigned int _vao;
  unsigned int _ebo;

  double _zoom;
  const int _max_iterations;

  glm::vec3 _camera_position;
  glm::vec3 _position_correction;
  glm::mat4 _transform;

  /// Helper functions
  /**
   * Set the correct settings for the class based on user options
   */
  _FractalOptions setup_options(int options);

  /**
   * Process user input during plotting. 
   */
  void process_input();
  /**
   * Update the internal plot according to stored values.
   */
  void update_plot();
  /**
   * Render the plot surface.
   */
  void render_plot() const;
};

/**
 * The resize callback function, which is called whenever the window is resized 
 *   by the user.
 */
void complex_fractal_framebuffer_size(class GLFWwindow* window, int width, int height);

#endif
