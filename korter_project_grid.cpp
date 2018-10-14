#include "korter_project_grid.h"

#include <iostream>

ribi::kp::grid::grid(
  const int width,
  const int height
) : m_cells(height, std::vector<grid_cell>(width))
{

}

std::ostream& ribi::kp::operator<<(std::ostream& os, const grid& g) noexcept
{
  //Number of rows
  os << g.m_cells.size() << " ";

  //Per row ...
  for (const auto& row: g.m_cells)
  {
    //Number of elements
    os << row.size() << " ";
    //Per element
    for (const auto& element: row)
    {
      os << element << " ";
    }
  }
  return os;
}

std::istream& ribi::kp::operator>>(std::istream& is, grid& g) noexcept
{
  //Number of rows
  int n_rows{-1};
  is >> n_rows;
  std::vector<std::vector<grid_cell>> cells;
  cells.reserve(n_rows);

  //Per row
  for (int row_index = 0; row_index != n_rows; ++row_index)
  {
    //Number of elements
    int n_elements{-1};
    is >> n_elements;
    std::vector<grid_cell> row;
    row.reserve(n_elements);

    for (int i = 0; i != n_elements; ++i)
    {
      grid_cell element;
      is >> element;
      row.push_back(element);
    }
    cells.push_back(row);
  }
  g.m_cells = cells;
  return is;
}

bool ribi::kp::operator==(const grid& lhs, const grid& rhs) noexcept
{
  return
    lhs.get_cells() == rhs.get_cells()
  ;

}

bool ribi::kp::operator!=(const grid& lhs, const grid& rhs) noexcept
{
  return !(lhs == rhs);
}
