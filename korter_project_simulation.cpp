#include "korter_project_simulation.h"

#include <iostream>

ribi::kp::simulation::simulation(const parameters& p)
  : m_grid(p.get_spatial_height(), p.get_spatial_width()),
    m_parameters{p},
    m_rng_engine(p.get_rng_seed())
{
  //Put nurse plants into position
  const int width{p.get_spatial_width()};
  const int height{p.get_spatial_height()};
  std::uniform_int_distribution<int> width_distr(0, width - 1);
  std::uniform_int_distribution<int> height_distr(0, height - 1);
  const int n_nurse{p.get_n_nurse_plants()};
  for (int i = 0; i != n_nurse; ++i)
  {
    const int x{width_distr(m_rng_engine)};
    const int y{height_distr(m_rng_engine)};
    m_grid.get(x, y).make_nurse();
  }
}

int ribi::kp::count_n_nurse(const simulation& s) noexcept
{
  return count_n_nurse(s.get_grid());
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
