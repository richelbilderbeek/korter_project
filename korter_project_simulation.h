#ifndef SPATIALSIMULATION_H
#define SPATIALSIMULATION_H

#include <random>
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
  std::mt19937 m_rng_engine;

  friend std::ostream& operator<<(std::ostream& os, const simulation& parameter) noexcept;
  friend std::istream& operator>>(std::istream& is, simulation& parameter) noexcept;
};

///Add nurse plants to a grid
grid add_nurse_plants(
  grid g,
  const int n_nurse,
  std::mt19937& rng_engine
);

///Add seeds/non-nurse plants to a grid
grid add_seeds(
  grid g,
  const int n_seeds,
  const double init_trait_mean,
  const double init_trait_stddev,
  std::mt19937& rng_engine
);

///Count the number of nurse plants in the simulation's grid
int count_n_nurse(const simulation& s) noexcept;

///Count the number of seed/non-nurse plants in the simulation's grid
int count_n_seeds(const simulation& s) noexcept;

bool operator==(const simulation& lhs, const simulation& rhs) noexcept;
bool operator!=(const simulation& lhs, const simulation& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const simulation& parameter) noexcept;
std::istream& operator>>(std::istream& is, simulation& parameter) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // SPATIALSIMULATION_H
