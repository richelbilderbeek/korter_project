#ifndef SPATIALSIMULATION_H
#define SPATIALSIMULATION_H

#include <vector>

#include "korter_project_parameters.h"
#include "korter_project_grid.h"

namespace ribi {
namespace kp {

struct simulation
{
  simulation(const parameters& p = parameters());

  void go_to_next_generation();

  const grid& get_grid() const noexcept { return m_grid; }
  const parameters& get_parameters() const noexcept { return m_parameters; }

  private:

  grid m_grid;
  parameters m_parameters;

  friend std::ostream& operator<<(std::ostream& os, const simulation& parameter) noexcept;
  friend std::istream& operator>>(std::istream& is, simulation& parameter) noexcept;
};

bool operator==(const simulation& lhs, const simulation& rhs) noexcept;
bool operator!=(const simulation& lhs, const simulation& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const simulation& parameter) noexcept;
std::istream& operator>>(std::istream& is, simulation& parameter) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // SPATIALSIMULATION_H
