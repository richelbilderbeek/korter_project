#include "korter_project_parameters.h"

#include <cassert>
#include <iostream>
#include <sstream>

ribi::kp::parameters::parameters(
  const fitness_parameters& fp,
  const double init_trait_mean,
  const double init_trait_stddev,
  const double mut_stddev,
  const int spatial_height,
  const int spatial_width,
  const int n_nurse_plants,
  const int n_seeds,
  const int n_trait_histogram_bins,
  const int rng_seed,
  const double trait_histogram_bin_width
) : m_fitness_parameters(fp),
    m_init_trait_mean{init_trait_mean},
    m_init_trait_stddev{init_trait_stddev},
    m_mut_stddev{mut_stddev},
    m_spatial_height{spatial_height},
    m_spatial_width{spatial_width},
    m_n_nurse_plants{n_nurse_plants},
    m_n_seeds{n_seeds},
    m_n_trait_histogram_bins{n_trait_histogram_bins},
    m_rng_seed{rng_seed},
    m_trait_histogram_bin_width{trait_histogram_bin_width}
{
  assert(m_init_trait_mean >= 0.0);
  assert(m_init_trait_stddev >= 0.0);
  assert(m_mut_stddev >= 0.0);
  assert(m_n_nurse_plants >= 0.0);
  assert(m_n_seeds >= 0.0);
  assert(m_n_trait_histogram_bins >= 1);
  assert(m_rng_seed >= 0.0);
  assert(m_spatial_height > 0);
  assert(m_spatial_width > 0);
  assert(m_trait_histogram_bin_width > 0.0);

  if (m_n_nurse_plants + m_n_seeds > m_spatial_width * m_spatial_height)
  {
    std::stringstream msg;
    msg
      << "Cannot have more nurse plants (" << m_n_nurse_plants << ") "
      << "and seeds (" << m_n_seeds << ") for a grid with "
      << (m_spatial_width * m_spatial_height ) << " cells ("
      << m_spatial_width << "x" << m_spatial_height
      << ")"
    ;
    throw std::invalid_argument(msg.str());
  }
}

ribi::kp::parameters ribi::kp::parameters::GetTest(const int /* i */)
{

  const parameters p(
    fitness_parameters(0.5, 0.1, 1.0, 0.1, 0.2, 1.0),
    10, //spatial_height
    10, //spatial_width
    0.1, //n_nurse_plants,
    0.1, //n_seeds,
    0.0 //any_n_nurse_plants,
  );
  return p;
}

void ribi::kp::parameters::set_n_nurse_plants(const int n_nurse_plants)
{
  assert(n_nurse_plants >= 0);
  m_n_nurse_plants = n_nurse_plants;
}

void ribi::kp::parameters::set_n_seeds(const int n_seeds)
{
  assert(n_seeds >= 0);
  m_n_seeds = n_seeds;
}

void ribi::kp::parameters::set_spatial_height(const int height)
{
  assert(height >= 1);
  m_spatial_height = height;
}

void ribi::kp::parameters::set_spatial_width(const int width)
{
  assert(width >= 1);
  m_spatial_width = width;
}

std::ostream& ribi::kp::operator<<(std::ostream& os, const parameters& parameter) noexcept
{
  os
    << parameter.get_spatial_height() << " "
    << parameter.get_spatial_width() << " "
    << parameter.get_n_nurse_plants() << " "
    << parameter.get_n_seeds() << " "
    << parameter.get_rng_seed() << " "
  ;
  return os;
}

std::istream& ribi::kp::operator>>(std::istream& is, parameters& parameter) noexcept
{
  is
    >> parameter.m_spatial_height
    >> parameter.m_spatial_width
    >> parameter.m_n_nurse_plants
    >> parameter.m_n_seeds
    >> parameter.m_rng_seed
  ;
  return is;
}

bool ribi::kp::operator==(const parameters& lhs, const parameters& rhs) noexcept
{
  return
       lhs.get_spatial_height() == rhs.get_spatial_height()
    && lhs.get_spatial_width() == rhs.get_spatial_width()
    && lhs.m_n_nurse_plants == rhs.m_n_nurse_plants
    && lhs.m_n_seeds == rhs.m_n_seeds
    && lhs.m_rng_seed == rhs.m_rng_seed
  ;

}

bool ribi::kp::operator!=(const parameters& lhs, const parameters& rhs) noexcept
{
  return !(lhs == rhs);
}
