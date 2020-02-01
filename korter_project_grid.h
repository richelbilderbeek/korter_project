#ifndef KORTER_PROJECT_GRID_H
#define KORTER_PROJECT_GRID_H

#include <iosfwd>
#include <random>
#include <vector>
#include "korter_project_grid_cell.h"

namespace ribi {
namespace kp {

class grid
{
public:
  grid(const int width = 1, const int height = 1);

  const grid_cell& get(const int x, const int y) const;
  grid_cell& get(const int x, const int y);

  int get_height() const noexcept { return m_cells.size(); }
  int get_width() const;

  const auto& get_cells() const noexcept { return m_cells; }
  auto& get_cells() noexcept { return m_cells; }

private:
  ///Y-X-ordered, rows-wise order
  std::vector<std::vector<grid_cell>> m_cells;


  friend std::ostream& operator<<(std::ostream& os, const grid& parameter) noexcept;
  friend std::istream& operator>>(std::istream& is, grid& parameter) noexcept;
};

///Add seeds again with the trait
grid add_seeds(
  grid g,
  const std::vector<double>& traits,
  std::mt19937& rng_engine
);


///Calculate the fraction of the facilitated cells in the realized grid.
///This fraction goes from 0.0 (no nurse plants) to 1.0 (all grid cells
///are connected to a nurse plant)
double calc_frac_fac(const grid& g);

///Extract the seeds that are facilitated
std::vector<bool> collect_is_facilitated(const grid& g);

///Extract the seed trait values
std::vector<double> collect_traits(const grid& g);

///Count the number of empty grid cells
int count_n_empty(const grid& g) noexcept;

///Count the number of facilitated plants
int count_n_facilitated_seeds(const grid& g) noexcept;

///Count the number of nurse plants
int count_n_nurse(const grid& g) noexcept;

///Count the number of seeds/non-nurse plants
int count_n_seeds(const grid& g) noexcept;

///Count the number of unfacilitated plants
int count_n_unfacilitated_seeds(const grid& g) noexcept;

/// Create a 4x3 (width x height) grid to be used in testing.
/// This is the layout of the grid:
///
///   |0123|
///  -|----+-
///  0|....|0
///  1|.N.U|1
///  2|.F..|2
///  -|----+-
///   |0123|
///
/// N: Nurse plant
/// F: Facilitated plant/seed, because adjacent to nurse
/// U: Unfacilitated plant/seed, because not adjacent to nurse
grid create_test_grid() noexcept;

///Create a histogram of the traits
///Traits are assumed to be zero or more
std::vector<int> create_trait_histogram(
  const grid& g,
  const int n_bins,
  const double bin_width
);

///From an grid, remove the seeds, keep the nurse plants
///and add seeds again with the trait
grid create_next_grid(
  grid g,
  const std::vector<double>& traits,
  std::mt19937& rng_engine
);

///Return true if all cells are empty
bool is_empty(const grid& g) noexcept;

///Is the cell empty?
bool is_empty(const grid& g, const int x, const int y);

///Is the cell adjacent to a nurse plant?
///Assumes the cell is a non-nurse plant,
///i.e. either the cell is empty or contains a seed
bool is_facilitated(const grid& g, const int x, const int y);

///Is the cell containing a nurse plant?
bool is_nurse(const grid& g, const int x, const int y);

///Is this grid cell a seed/non-nurse plant?
bool is_seed(const grid& g, const int x, const int y);

///Is the cell not adjacent to a nurse plant?
///Assumes the cell is a non-nurse plant,
///i.e. either the cell is empty or contains a seed
bool is_unfacilitated(const grid& g, const int x, const int y);

///Empty all grid cells with a seed/non-nurse plant
void remove_seeds(grid& g);

bool operator==(const grid& lhs, const grid& rhs) noexcept;
bool operator!=(const grid& lhs, const grid& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const grid& parameter) noexcept;
std::istream& operator>>(std::istream& is, grid& parameter) noexcept;

} //~namespace kp
} //~namespace ribi

#endif // KORTER_PROJECT_GRID_H
