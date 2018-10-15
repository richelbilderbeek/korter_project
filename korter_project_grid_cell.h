#ifndef KORTER_PROJECT_GRID_CELL_H
#define KORTER_PROJECT_GRID_CELL_H

#include "korter_project_parameters.h"

namespace ribi {
namespace kp {

struct grid_cell
{
  ///A grid cell is empty by default
  grid_cell(const double trait = sm_empty);

  bool is_empty() const noexcept { return m_trait == sm_empty; }
  bool is_nurse() const noexcept { return m_trait == sm_nurse; }
  bool is_seed() const noexcept { return m_trait >= 0.0; }
  void make_empty() { m_trait = sm_empty; }
  void make_nurse() { m_trait = sm_nurse; }
  double get_trait() const noexcept { return m_trait; }
  void set_trait(const double trait);

  private:

  static constexpr double sm_empty{-12.34};
  static constexpr double sm_nurse{-23.45};
  /// * 0.0 or bigger if occupied
  /// * less than zero if empty
  double m_trait;




  friend std::ostream& operator<<(std::ostream& os, const grid_cell& g) noexcept;
  friend std::istream& operator>>(std::istream& is, grid_cell& g) noexcept;
};

///Is the grid cell empty?
bool is_empty(const grid_cell& c) noexcept;

///Is the grid cell a nurse plant?
bool is_nurse(const grid_cell& c) noexcept;

///Is the grid cell a seed/non-nurse plant?
bool is_seed(const grid_cell& c) noexcept;

bool operator==(const grid_cell& lhs, const grid_cell& rhs) noexcept;
bool operator!=(const grid_cell& lhs, const grid_cell& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const grid_cell& g) noexcept;
std::istream& operator>>(std::istream& is, grid_cell& g) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // KORTER_PROJECT_GRID_CELL_H
