/*****************************************************************//**
 * \file   Julia.h
 * \brief  
 * 
 * \author bltan
 * \date   July 2020
 *********************************************************************/

#include <glm\glm.hpp>

#include "ComplexFractal.h"

class Julia : public ComplexFractal { 
public:
  Julia();
  ~Julia() = default;

private:
  glm::vec2 _point;

  bool init_plot() override;
  void shutdown_plot() override;

  void process_plot_input() override;
  void update_plot() override;
  void render_plot() const override;
};

