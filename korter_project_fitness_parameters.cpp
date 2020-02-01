#include "korter_project_fitness_parameters.h"

#include <iostream>
#include <cassert>
#include <cmath>

ribi::kp::fitness_parameters::fitness_parameters(
  const double fac_opt,
  const double fac_stddev,
  const double fac_max,
  const double unfac_opt,
  const double unfac_stddev,
  const double unfac_max
) :
    m_fac_max{fac_max},
    m_fac_opt{fac_opt},
    m_fac_stddev{fac_stddev},
    m_unfac_max{unfac_max},
    m_unfac_opt{unfac_opt},
    m_unfac_stddev{unfac_stddev}
{
  assert(m_fac_max >= 0.0);
  assert(m_fac_opt >= 0.0);
  assert(m_fac_stddev >= 0.0);
  assert(m_unfac_max >= 0.0);
  assert(m_unfac_opt >= 0.0);
  assert(m_unfac_stddev >= 0.0);
}

double ribi::kp::calc_upper_trait(const fitness_parameters& params, const double n_stddevs)
{
  assert(n_stddevs >= 0.0);
  return std::max(
      params.get_fac_opt() + (params.get_fac_stddev() * n_stddevs),
      params.get_unfac_opt() + (params.get_unfac_stddev() * n_stddevs)
    )
  ;
}

double ribi::kp::gauss(const double x, const double sd) noexcept
{
  return std::exp(-(x * x) / (2.0 * sd * sd));
}

double ribi::kp::get_fitness(
  const fitness_parameters& params,
  const double trait,
  const bool is_facilitated
)
{
  double mean = params.get_unfac_opt();
  double stddev = params.get_unfac_stddev();
  double max = params.get_unfac_max();
  if (is_facilitated)
  {
    mean = params.get_fac_opt();
    stddev = params.get_fac_stddev();
    max = params.get_fac_max();
  }
  return max * normal(trait, mean, stddev);
}

double ribi::kp::normal(const double x, const double mean, const double sd) noexcept
{
  return gauss(x - mean, sd);
}

bool ribi::kp::operator==(const fitness_parameters& lhs, const fitness_parameters& rhs) noexcept
{
  return
       lhs.get_fac_max() == rhs.get_fac_max()
    && lhs.get_fac_opt() == rhs.get_fac_opt()
    && lhs.get_fac_stddev() == rhs.get_fac_stddev()
    && lhs.get_unfac_max() == rhs.get_unfac_max()
    && lhs.get_unfac_opt() == rhs.get_unfac_opt()
    && lhs.get_unfac_stddev() == rhs.get_unfac_stddev()
  ;
}

bool ribi::kp::operator!=(const fitness_parameters& lhs, const fitness_parameters& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::kp::operator<<(std::ostream& os, const fitness_parameters& parameter) noexcept
{
  os
    << parameter.m_fac_max << " "
    << parameter.m_fac_opt << " "
    << parameter.m_fac_stddev << " "
    << parameter.m_unfac_max << " "
    << parameter.m_unfac_opt << " "
    << parameter.m_unfac_stddev << " "
  ;
  return os;
}

std::istream& ribi::kp::operator>>(std::istream& is, fitness_parameters& parameter) noexcept
{
  is
    >> parameter.m_fac_max
    >> parameter.m_fac_opt
    >> parameter.m_fac_stddev
    >> parameter.m_unfac_max
    >> parameter.m_unfac_opt
    >> parameter.m_unfac_stddev
  ;
  return is;
}
