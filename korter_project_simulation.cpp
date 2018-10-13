#include "korter_project_simulation.h"


ribi::kp::simulation::simulation(const parameters& p)
  : m_grid{
      grid(p.get_spatial_height(),
      std::vector<grid_cell>(p.get_spatial_width(),
      grid_cell(p)))
    },
    m_parameters{p}
{

}

void ribi::kp::simulation::Change(const double delta_t)
{
  for (auto& line: m_grid)
  {
    for (auto& system: line)
    {
      system.Change(delta_t);
    }
  }

  using Density = double;
  const int height{static_cast<int>(m_grid.size())};
  const int width{static_cast<int>(m_grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      const std::vector<Density> neigbour_seagrass_densities
        =
        {
          m_grid[y][(x-1+width)%width].GetSeagrassDensity(),
          m_grid[y][(x+1+width)%width].GetSeagrassDensity(),
          m_grid[(y-1+height)%height][x].GetSeagrassDensity(),
          m_grid[(y+1+height)%height][x].GetSeagrassDensity()
        }
      ;
      const double colonization
        = 0.1
      ;
      m_grid[y][x].AddSeagrassDensity(colonization * delta_t);
    }
  }
}

void ribi::kp::simulation::KillSeagrass(const int x, const int y)
{
  m_grid[y][x].SetSeagrassDensity(0.0);
}
