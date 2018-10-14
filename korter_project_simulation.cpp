#include "korter_project_simulation.h"

#include <algorithm>
#include <cassert>
#include <iostream>

ribi::kp::simulation::simulation(const parameters& p)
  : m_grid(p.get_spatial_width(), p.get_spatial_height()),
    m_parameters{p},
    m_rng_engine(p.get_rng_seed()),
    m_trait_histograms{}
{
  assert(m_grid.get_width() == p.get_spatial_width());
  assert(m_grid.get_height() == p.get_spatial_height());
  const int n_nurse{p.get_n_nurse_plants()};
  const int n_seeds{p.get_n_seeds()};
  const int width{p.get_spatial_width()};
  const int height{p.get_spatial_height()};
  assert(n_nurse + n_seeds <= width * height);

  m_grid = add_nurse_plants(m_grid, n_nurse, m_rng_engine);
  m_grid = add_seeds(
    m_grid,
    n_seeds,
    p.get_init_trait_mean(),
    p.get_init_trait_stddev(),
    m_rng_engine);

  add_trait_histogram();
}

ribi::kp::grid ribi::kp::add_nurse_plants(
  grid g,
  const int n_nurse,
  std::mt19937& rng_engine)
{
  assert(n_nurse <= count_n_empty(g));
  const int width{g.get_width()};
  const int height{g.get_height()};
  //Put nurse plants into position
  std::uniform_int_distribution<int> width_distr(0, width - 1);
  std::uniform_int_distribution<int> height_distr(0, height - 1);
  for (int i = 0; i != n_nurse; ++i)
  {
    const int x{width_distr(rng_engine)};
    const int y{height_distr(rng_engine)};
    assert(x >= 0);
    assert(x < g.get_width());
    assert(y >= 0);
    assert(y < g.get_height());
    if (g.get(x, y).is_empty())
    {
      g.get(x, y).make_nurse();
    }
    else
    {
      --i;
    }
  }
  return g;
}

ribi::kp::grid ribi::kp::add_seeds(
  grid g,
  const int n_seeds,
  const double init_trait_mean,
  const double init_trait_stddev,
  std::mt19937& rng_engine)
{
  assert(n_seeds <= count_n_empty(g));
  const int width{g.get_width()};
  const int height{g.get_height()};
  //Put nurse plants into position
  std::uniform_int_distribution<int> width_distr(0, width - 1);
  std::uniform_int_distribution<int> height_distr(0, height - 1);
  for (int i = 0; i != n_seeds; ++i)
  {
    const int x{width_distr(rng_engine)};
    const int y{height_distr(rng_engine)};
    assert(x >= 0);
    assert(x < g.get_width());
    assert(y >= 0);
    assert(y < g.get_height());
    if (g.get(x, y).is_empty())
    {
      std::normal_distribution<double> d(init_trait_mean, init_trait_stddev);
      g.get(x, y).set_trait(d(rng_engine));
    }
    else
    {
      --i;
    }
  }
  return g;
}

void ribi::kp::simulation::add_trait_histogram()
{
  const std::vector<int> histogram = create_trait_histogram(
    m_grid,
    m_parameters.get_n_trait_histogram_bins(),
    calc_upper_trait(m_parameters.get_fitness_parameters())
  );

  const std::vector<double> density = create_density_plot(histogram);

  m_trait_histograms.push_back(density);
}

int ribi::kp::count_n_nurse(const simulation& s) noexcept
{
  return count_n_nurse(s.get_grid());
}

int ribi::kp::count_n_seeds(const simulation& s) noexcept
{
  return count_n_seeds(s.get_grid());
}

std::vector<double> ribi::kp::create_density_plot(const std::vector<int>& histogram)
{
  std::vector<double> d;
  d.reserve(histogram.size());
  std::transform(
    std::begin(histogram), std::end(histogram),
    std::back_inserter(d), [](const int i){ return static_cast<double>(i); }
  );
  return d;
}

void ribi::kp::simulation::go_to_next_generation()
{
  /*
  for (auto& line: m_grid.get_cells())
  {
    for (auto& cell: line)
    {
      cell.set_trait(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX));
    }
  }
  */
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
