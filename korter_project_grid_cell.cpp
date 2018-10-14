#include "korter_project_grid_cell.h"

#include <iostream>
#include <sstream>

ribi::kp::grid_cell::grid_cell(const double trait)
  : m_trait{trait}
{

}

bool ribi::kp::is_nurse(const grid_cell& c) noexcept
{
  return c.is_nurse();
}

bool ribi::kp::operator==(const grid_cell& lhs, const grid_cell& rhs) noexcept
{
  return lhs.get_trait() == rhs.get_trait();
}

bool ribi::kp::operator!=(const grid_cell& lhs, const grid_cell& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::kp::operator<<(std::ostream& os, const grid_cell& parameter) noexcept
{
  os
    << parameter.get_trait() << " "
  ;
  return os;
}

std::istream& ribi::kp::operator>>(std::istream& is, grid_cell& parameter) noexcept
{
  is
    >> parameter.m_trait
  ;
  return is;
}


