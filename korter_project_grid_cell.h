#ifndef KORTER_PROJECT_GRID_CELL_H
#define KORTER_PROJECT_GRID_CELL_H

#include "korter_project_parameters.h"

namespace ribi {
namespace kp {

struct grid_cell
{
  grid_cell(const parameters& parameters);

  void AddSeagrassDensity(const double seagrass_density) { m_seagrass_density += seagrass_density; }
  void Change(const double delta_t);

  const parameters& GetParameters() const noexcept { return m_parameters; }
  double GetSeagrassDensity() const noexcept { return m_seagrass_density; }
  double GetSulfidedouble() const noexcept { return m_sulfide_concentration; }
  void SetSeagrassDensity(const double seagrass_density) { m_seagrass_density = seagrass_density; }
  void SetSulfidedouble(const double sulfide_concentration) { m_sulfide_concentration = sulfide_concentration; }

  private:
  const parameters m_parameters;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  double m_seagrass_density;
  double m_sulfide_concentration;
};

} //~namespace mb
} //~namespace ribi

#endif // KORTER_PROJECT_GRID_CELL_H
