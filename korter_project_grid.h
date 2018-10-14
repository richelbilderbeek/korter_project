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

///Extract the seeds that are facilitated
std::vector<bool> collect_is_facilitated(const grid& g);

///Extract the seed trait values
std::vector<double> collect_traits(const grid& g);

///Count the number of empty grid cells
int count_n_empty(const grid& g) noexcept;

///Count the number of nurse plants
int count_n_nurse(const grid& g) noexcept;

///Count the number of seeds/non-nurse plants
int count_n_seeds(const grid& g) noexcept;

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

///Is the cell adjacent to a nurse plant?
///Assumes the cell is a seed/non-nurse plant
bool is_facilitated(const grid& g, const int x, const int y);

///Is this grid cell a seed/non-nurse plant?
bool is_seed(const grid& g, const int x, const int y);

///Empty all grid cells with a seed/non-nurse plant
void remove_seeds(grid& g);

bool operator==(const grid& lhs, const grid& rhs) noexcept;
bool operator!=(const grid& lhs, const grid& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const grid& parameter) noexcept;
std::istream& operator>>(std::istream& is, grid& parameter) noexcept;

} //~namespace kp
} //~namespace ribi

#endif // KORTER_PROJECT_GRID_H
