#ifndef Complex_Fractal_h_INCLUDED
#define Complex_Fractal_h_INCLUDED

/*****************************************************************//**
 * \file   ComplexFractal.h
 * 
 *   A pure virtual class to manage plotting Complex Fractals
 *    Any class can inherit from this one to plot a fractal shape in the 
 *    complex plane by overriding the following protected methods:
 *      
 *      bool init_plot();
 *      void shutdown_plot();
 * 
 *      void process_plot_input();
 *      void update_plot();
 *      void render_plot();
 * 
 *    Additionally, it is necessary to provide shaders for the plot, these are
 *    where the calculation takes place.
 * 
 * \author bltan
 * \date   July 2020
 *********************************************************************/

#include <string>

#include <glm\glm.hpp>

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
  ComplexFractal(const int window_width, const int window_height, 
                 const std::string& window_title, int max_iterations=500);
  virtual ~ComplexFractal();

  /**
   * Initialize necessary systems for plotting and displaying a complex fractal.
   * 
   * \param options optional parameters to change the plotting method of ComplexFractal
   * \return false if there was an error during initialization, true otherwise.
   */
  virtual bool init();
  /**
   * Shut down all systems and clean up memory.
   * 
   */
  virtual void shutdown();

  /**
   * Plot the complex fractal
   */
  void plot();

protected:
  // OpenGL Parameters
  const int _window_width;
  const int _window_height;
  std::string _window_title;

  class GLFWwindow* _window;
  class Shader* _shader;

  // Plot Parameters
  double _vertices[20];
  unsigned int _indices[6];

  unsigned int _vbo;
  unsigned int _vao;
  unsigned int _ebo;

  double _zoom;
  int _max_iterations;

  glm::vec3 _camera_position;
  glm::vec3 _position_correction;
  glm::mat4 _transform;

  // Helper functions
  /**
   * Process user input during plotting. 
   */
  virtual void process_input();
  void process_base_input();
  virtual void process_plot_input() = 0;
  /**
   * Update the internal plot according to stored values.
   */
  virtual void update();
  void update_base();
  virtual void update_plot() = 0;
  /**
   * Render the plot surface.
   */
  virtual void render() const;
  void render_base() const;
  virtual void render_plot() const = 0;
  void display() const;

  bool init_base_systems();
  virtual bool init_plot() = 0;

  void shutdown_base_systems();
  virtual void shutdown_plot() = 0;
};

/**
 * The resize callback function, which is called whenever the window is resized 
 *   by the user.
 */
void complex_fractal_framebuffer_size(class GLFWwindow* window, int width, int height);

#endif
