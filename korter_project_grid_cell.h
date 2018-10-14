#ifndef KORTER_PROJECT_GRID_CELL_H
#define KORTER_PROJECT_GRID_CELL_H

#include "korter_project_parameters.h"

namespace ribi {
namespace kp {

struct grid_cell
{
  ///A grid cell is empty by default
  grid_cell(const double trait = -1.0);

  bool is_empty() const noexcept { return m_trait < 0.0; }
  void clear() { m_trait = -1.0; }
  double get_trait() const noexcept { return m_trait; }
  void set_trait(const double trait) { m_trait = trait; }

  private:

  /// * 0.0 or bigger if occupied
  /// * less than zero if empty
  double m_trait;


  friend std::ostream& operator<<(std::ostream& os, const grid_cell& g) noexcept;
  friend std::istream& operator>>(std::istream& is, grid_cell& g) noexcept;
};

bool operator==(const grid_cell& lhs, const grid_cell& rhs) noexcept;
bool operator!=(const grid_cell& lhs, const grid_cell& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const grid_cell& g) noexcept;
std::istream& operator>>(std::istream& is, grid_cell& g) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // KORTER_PROJECT_GRID_CELL_H
