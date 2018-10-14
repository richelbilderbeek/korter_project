#include "korter_project_fitness_parameters.h"

#include <iostream>
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
  return lhs.get_fac_opt() == rhs.get_fac_opt()
    &&  lhs.get_fac_stddev() == rhs.get_fac_stddev()
    &&  lhs.get_unfac_opt() == rhs.get_unfac_opt()
    &&  lhs.get_unfac_stddev() == rhs.get_unfac_stddev()
  ;
}

bool ribi::kp::operator!=(const fitness_parameters& lhs, const fitness_parameters& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::kp::operator<<(std::ostream& os, const fitness_parameters& parameter) noexcept
{
  os
    << parameter.m_fac_opt << " "
    << parameter.m_fac_stddev << " "
    << parameter.m_unfac_opt << " "
    << parameter.m_unfac_stddev << " "
  ;
  return os;
}

std::istream& ribi::kp::operator>>(std::istream& is, fitness_parameters& parameter) noexcept
{
  is
    >> parameter.m_fac_opt
    >> parameter.m_fac_stddev
    >> parameter.m_unfac_opt
    >> parameter.m_unfac_stddev
  ;
  return is;
}
