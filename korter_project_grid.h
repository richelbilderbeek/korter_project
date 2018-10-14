#ifndef KORTER_PROJECT_GRID_H
#define KORTER_PROJECT_GRID_H

#include <iosfwd>
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

///Count the number of nurse plants
int count_n_nurse(const grid& g) noexcept;

bool operator==(const grid& lhs, const grid& rhs) noexcept;
bool operator!=(const grid& lhs, const grid& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const grid& parameter) noexcept;
std::istream& operator>>(std::istream& is, grid& parameter) noexcept;

} //~namespace kp
} //~namespace ribi

#endif // KORTER_PROJECT_GRID_H
