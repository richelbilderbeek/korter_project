#include "korter_project_simulation.h"

#include <iostream>

ribi::kp::simulation::simulation(const parameters& p)
  : m_grid(p.get_spatial_height(), p.get_spatial_width()),
    m_parameters{p}
{

}

void ribi::kp::simulation::go_to_next_generation()
{
  for (auto& line: m_grid.get_cells())
  {
    for (auto& cell: line)
    {
      cell.set_trait(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX));
    }
  }
}


std::ostream& ribi::kp::operator<<(std::ostream& os, const simulation& s) noexcept
{
  os
    << s.m_grid << " "
    << s.m_parameters << " "
  ;
  return os;
}

std::istream& ribi::kp::operator>>(std::istream& is, simulation& s) noexcept
{
  is
    >> s.m_grid
    >> s.m_parameters
  ;
  return is;
}

bool ribi::kp::operator==(const simulation& lhs, const simulation& rhs) noexcept
{
  return
       lhs.get_grid() == rhs.get_grid()
    && lhs.get_parameters() == rhs.get_parameters()
  ;

}

bool ribi::kp::operator!=(const simulation& lhs, const simulation& rhs) noexcept
{
  return !(lhs == rhs);
}
