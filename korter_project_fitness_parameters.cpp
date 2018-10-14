#include "korter_project_fitness_parameters.h"

#include <cassert>
#include <cmath>

ribi::kp::fitness_parameters::fitness_parameters(
  const double fac_opt,
  const double fac_stddev,
  const double unfac_opt,
  const double unfac_stddev
) : m_fac_opt{fac_opt},
    m_fac_stddev{fac_stddev},
    m_unfac_opt{unfac_opt},
    m_unfac_stddev{unfac_stddev}
{
  assert(m_fac_opt >= 0.0);
  assert(m_fac_stddev >= 0.0);
  assert(m_unfac_opt >= 0.0);
  assert(m_unfac_stddev >= 0.0);
}

double ribi::kp::gauss(const double x, const double sd) noexcept
{
  return std::exp(-(x * x) / (2.0 * sd * sd));
}

double ribi::kp::normal(const double x, const double mean, const double sd) noexcept
{
  return gauss(x - mean, sd);
}

bool ribi::kp::operator==(const fitness_parameters& lhs, const fitness_parameters& rhs) noexcept
{
  return lhs.m_fac_opt == rhs.m_fac_opt
    &&  lhs.m_fac_stddev == rhs.m_fac_stddev
    &&  lhs.m_unfac_opt == rhs.m_unfac_opt
    &&  lhs.m_unfac_stddev == rhs.m_unfac_stddev
  ;
}

bool ribi::kp::operator!=(const fitness_parameters& lhs, const fitness_parameters& rhs) noexcept
{
  return !(lhs == rhs);
}
