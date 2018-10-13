#ifndef SPATIALSIMULATION_H
#define SPATIALSIMULATION_H

#include <vector>

#include "korter_project_parameters.h"
#include "korter_project_grid_cell.h"

namespace ribi {
namespace kp {

struct SpatialSimulation
{
  using Grid = std::vector<std::vector<grid_cell>>;

  SpatialSimulation(const parameters& parameters);

  void Change(const double delta_t);

  const Grid& GetGrid() const noexcept { return m_grid; }

  void KillSeagrass(const int x, const int y);

  private:

  Grid m_grid;
  const parameters m_parameters;
};

} //~namespace mb
} //~namespace ribi

#endif // SPATIALSIMULATION_H
