#ifndef SPATIALSIMULATION_H
#define SPATIALSIMULATION_H

#include <vector>

#include "korter_project_parameters.h"
#include "korter_project_grid_cell.h"

namespace ribi {
namespace kp {

struct simulation
{
  using grid = std::vector<std::vector<grid_cell>>;

  simulation(const parameters& p);

  void Change(const double delta_t);

  const grid& GetGrid() const noexcept { return m_grid; }

  void KillSeagrass(const int x, const int y);

  private:

  grid m_grid;
  const parameters m_parameters;
};

} //~namespace mb
} //~namespace ribi

#endif // SPATIALSIMULATION_H
