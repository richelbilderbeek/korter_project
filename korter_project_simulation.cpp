#include "korter_project_simulation.h"

#include <algorithm>
#include <cassert>
#include <iostream>

ribi::kp::simulation::simulation(const parameters& p)
  : m_grid(p.get_spatial_width(), p.get_spatial_height()),
    m_parameters{p},
    m_rng_engine(static_cast<unsigned long>(p.get_rng_seed())),
    m_trait_histograms{}
{
  assert(m_grid.get_width() == p.get_spatial_width());
  assert(m_grid.get_height() == p.get_spatial_height());
  if (p.use_test_grid()) {
    m_grid = create_test_grid();
  }
  const int n_nurse{p.get_n_nurse_plants()};
  const int n_seeds{p.get_n_seeds()};
  const int width{p.get_spatial_width()};
  const int height{p.get_spatial_height()};
  assert(n_nurse + n_seeds <= width * height);

  m_grid = add_nurse_plants(m_grid, n_nurse, m_rng_engine);
  m_grid = add_seeds(m_grid, m_parameters, m_rng_engine);

  add_histograms();
  assert(m_trait_histograms.size() == m_neutral_histograms.size());
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
  const parameters& p,
  std::mt19937& rng_engine)
{
  const int n_seeds{p.get_n_seeds()};

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
      const double init_trait_mean{p.get_init_trait_mean()};
      const double init_trait_stddev{p.get_init_trait_stddev()};
      std::normal_distribution<double> d_trait(init_trait_mean, init_trait_stddev);
      const double unconstrained_trait{d_trait(rng_engine)};
      const double trait{std::max(0.0, unconstrained_trait)};
      assert(trait >= 0.0);
      g.get(x, y).set_trait(trait);

      const double init_neutral_mean{p.get_init_neutral_mean()};
      const double init_neutral_stddev{p.get_init_neutral_stddev()};
      std::normal_distribution<double> d_neutral(init_neutral_mean, init_neutral_stddev);
      const double neutral{d_neutral(rng_engine)};
      g.get(x, y).set_neutral(neutral);
    }
    else
    {
      --i;
    }
  }
  return g;
}

void ribi::kp::simulation::add_histograms()
{
  assert(m_trait_histograms.size() == m_neutral_histograms.size());
  add_neutral_histogram();
  add_trait_histogram();
  assert(m_trait_histograms.size() == m_neutral_histograms.size());
}

void ribi::kp::simulation::add_neutral_histogram()
{
  const std::vector<int> histogram = create_neutral_histogram(
    m_grid,
    m_parameters.get_n_trait_histogram_bins(),
    m_parameters.get_trait_histogram_bin_width()
  );

  const std::vector<double> density = create_density_plot(histogram);

  m_neutral_histograms.push_back(density);
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

std::vector<double> ribi::kp::calc_fitnesses(
  const grid& grid,
  const parameters& p
)
{
  using namespace std;
  vector<double> traits = collect_traits(grid);
  vector<bool> is_facilitated = collect_is_facilitated(grid);
  assert(traits.size() == is_facilitated.size());
  const int n{static_cast<int>(traits.size())};
  std::vector<double> fitnesses;
  fitnesses.reserve(static_cast<size_t>(n));
  for (int i = 0; i != n; ++i)
  {
    const size_t index = static_cast<size_t>(i);
    const double fitness = get_fitness(
      p.get_fitness_parameters(),
      traits[index],
      is_facilitated[index]
    );
    fitnesses.push_back(fitness);
  }
  return fitnesses;
}

std::vector<double> ribi::kp::calc_fitnesses(
  const simulation& s,
  const parameters& p
)
{
  return calc_fitnesses(s.get_grid(), p);
}

std::vector<bool> ribi::kp::collect_is_facilitated(const simulation& s)
{
  return collect_is_facilitated(s.get_grid());
}

std::vector<double> ribi::kp::collect_neutrals(const simulation& s)
{
  return collect_neutrals(s.get_grid());
}

std::vector<ribi::kp::grid_cell> ribi::kp::collect_seeds(const simulation& s)
{
  return collect_seeds(s.get_grid());
}

std::vector<double> ribi::kp::collect_traits(const simulation& s)
{
  return collect_traits(s.get_grid());
}

int ribi::kp::count_n_empty(const simulation& s) noexcept
{
  return count_n_empty(s.get_grid());
}

int ribi::kp::count_n_facilitated_seeds(const simulation& s) noexcept
{
  return count_n_facilitated_seeds(s.get_grid());
}

int ribi::kp::count_n_nurse(const simulation& s) noexcept
{
  return count_n_nurse(s.get_grid());
}

int ribi::kp::count_n_seeds(const simulation& s) noexcept
{
  return count_n_seeds(s.get_grid());
}

int ribi::kp::count_n_unfacilitated_seeds(const simulation& s) noexcept
{
  return count_n_unfacilitated_seeds(s.get_grid());
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

std::vector<ribi::kp::grid_cell> ribi::kp::create_new_seeds(
  const grid& g,
  const parameters& p,
  std::mt19937& rng_engine
)
{
  using namespace std;

  const std::vector<grid_cell> seeds{collect_seeds(g)};
  const std::vector<double> fitnesses{calc_fitnesses(g, p)};

  // Weight chance of an index being picked by the fitness
  discrete_distribution<int> d(begin(fitnesses), end(fitnesses));

  const int n_seeds{p.get_n_seeds()};
  vector<grid_cell> new_seeds;
  new_seeds.reserve(static_cast<size_t>(n_seeds));
  for (int i = 0; i != n_seeds; ++i)
  {
    const int seed_index{d(rng_engine)};
    assert(seed_index >= 0);
    assert(seed_index < static_cast<int>(seeds.size()));
    const auto& seed = seeds[seed_index];
    const grid_cell new_seed{
      create_new_seed(
        seed,
        p,
        rng_engine
      )
    };
    new_seeds.push_back(new_seed);
  }
  assert(n_seeds == static_cast<int>(new_seeds.size()));
  return new_seeds;
}

void ribi::kp::simulation::go_to_next_generation()
{
  using namespace std;
  const auto new_seeds = create_new_seeds(m_grid, m_parameters, m_rng_engine);
  m_grid = create_next_grid(m_grid, new_seeds, m_rng_engine);
  add_histograms();
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
