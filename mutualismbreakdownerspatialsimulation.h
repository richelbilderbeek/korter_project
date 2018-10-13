#ifndef SPATIALSIMULATION_H
#define SPATIALSIMULATION_H

#include <vector>

#include "mutualismbreakdownerparameters.h"
#include "mutualismbreakdownerseagrasssystem.h"

namespace ribi {
namespace mb {

struct SpatialSimulation
{
  using System = SeagrassSystem;
  using Grid = std::vector<std::vector<System>>;

  SpatialSimulation(const Parameters& parameters);

  void Change(const double delta_t);

  const Grid& GetGrid() const noexcept { return m_grid; }

  void KillSeagrass(const int x, const int y);

  private:

  Grid m_grid;
  const Parameters m_parameters;
};

} //~namespace mb
} //~namespace ribi

#endif // SPATIALSIMULATION_H
