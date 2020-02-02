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

  const std::vector<std::vector<double>>& get_trait_histograms() const noexcept { return m_trait_histograms; }
  const std::vector<std::vector<double>>& get_neutral_histograms() const noexcept { return m_neutral_histograms; }

  private:

  grid m_grid;
  parameters m_parameters;
  std::mt19937 m_rng_engine;
  std::vector<std::vector<double>> m_trait_histograms;
  std::vector<std::vector<double>> m_neutral_histograms;

  ///Measure the traits and neutral markers
  ///and add their distributions to their respective histograms
  void add_histograms();

  ///Measure the neutral markers and add a histogram of these
  void add_neutral_histogram();

  ///Measure the traits and add a histogram of these
  void add_trait_histogram();


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
  const parameters& p,
  std::mt19937& rng_engine
);

///Calculate all the seeds' fitnesses.
///Will return in the same order as 'collect_traits'
std::vector<double> calc_fitnesses(
  const grid& grid,
  const parameters& p
);

///Calculate all the seeds' fitnesses.
///Will return in the same order as 'collect_traits'
std::vector<double> calc_fitnesses(
  const simulation& s,
  const parameters& p
);

///Extract the booleans whether seeds are facilitated or not
std::vector<bool> collect_is_facilitated(const simulation& s);

///Collect the seeds
std::vector<grid_cell> collect_seeds(const simulation& s);

///Collect the seed neutral marker values,
///these markers (that are trait values) are not under selection
std::vector<double> collect_neutrals(const simulation& s);

///Extract the seed trait values
std::vector<double> collect_traits(const simulation& s);

///Count the number of empty grid cells in the simulation's grid
int count_n_empty(const simulation& s) noexcept;

///Count the number of facilitated seeds in the simulation's grid
int count_n_facilitated_seeds(const simulation& s) noexcept;

///Count the number of nurse plants in the simulation's grid
int count_n_nurse(const simulation& s) noexcept;

///Count the number of seed/non-nurse plants in the simulation's grid
int count_n_seeds(const simulation& s) noexcept;


///Count the number of unfacilitated seeds in the simulation's grid
int count_n_unfacilitated_seeds(const simulation& s) noexcept;

///Create a density plot from a histogram
///In practice, simply converts the int to double,
///as QwtSurfacePlotWidget will normalize anyways?
std::vector<double> create_density_plot(const std::vector<int>& histogram);

///Create the mutated set of traits
std::vector<grid_cell> create_new_seeds(
  const grid& g,
  const parameters& p,
  std::mt19937& rng_engine
);

bool operator==(const simulation& lhs, const simulation& rhs) noexcept;
bool operator!=(const simulation& lhs, const simulation& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const simulation& parameter) noexcept;
std::istream& operator>>(std::istream& is, simulation& parameter) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // SPATIALSIMULATION_H
