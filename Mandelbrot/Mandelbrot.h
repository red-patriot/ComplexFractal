#ifndef Mandelbrot_h_INCLUDED
#define Mandelbrot_h_INCLUDED

/*****************************************************************//**
 * \file   Mandelbrot.h
 * \brief
 *
 * \author bltan
 * \date   July 2020
 *********************************************************************/

#include "ComplexFractal.h"

class Mandelbrot: public ComplexFractal{ 
public:
  Mandelbrot();
  ~Mandelbrot() = default;

private:
  bool init_plot() override;
  void shutdown_plot() override;

  void process_plot_input() override;
  void update_plot() override;
  void render_plot() const override;
};

#endif
