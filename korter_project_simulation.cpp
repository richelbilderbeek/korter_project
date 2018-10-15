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
      const double trait{d(rng_engine)};
      g.get(x, y).set_trait(std::max(0.0, trait));
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
    m_parameters.get_trait_histogram_bin_width()
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
  std::vector<double> traits = collect_traits(m_grid);
  std::vector<bool> is_facilitated = collect_is_facilitated(m_grid);
  assert(traits.size() == is_facilitated.size());
  const int n = traits.size();
  std::vector<double> fitnesses;
  fitnesses.reserve(n);
  for (int i = 0; i != n; ++i)
  {
    const double fitness = get_fitness(
      m_parameters.get_fitness_parameters(),
      traits[i],
      is_facilitated[i]
    );
    fitnesses.push_back(fitness);
  }
  std::discrete_distribution<int> d(std::begin(fitnesses), std::end(fitnesses));
  const int n_seeds{m_parameters.get_n_seeds()};
  std::vector<double> new_traits;
  new_traits.reserve(n_seeds);
  for (int i = 0; i != n_seeds; ++i)
  {
    const int seed_index{d(m_rng_engine)};
    assert(seed_index >= 0);
    assert(seed_index < static_cast<int>(traits.size()));
    const double cur_trait{traits[seed_index]};
    std::normal_distribution<double> normal_distr(0.0, m_parameters.get_mut_stddev());
    const double new_trait{cur_trait + normal_distr(m_rng_engine)};
    new_traits.push_back(std::max(0.0, new_trait));
  }
  assert(n_seeds == static_cast<int>(new_traits.size()));
  m_grid = create_next_grid(m_grid, new_traits, m_rng_engine);
  add_trait_histogram();
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
