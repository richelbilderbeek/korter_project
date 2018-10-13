#include "korter_project_fitness_parameters.h"

#include <cassert>

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
