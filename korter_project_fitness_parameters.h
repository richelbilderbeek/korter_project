#ifndef KORTER_PROJECT_FITNESS_PARAMETERS_H
#define KORTER_PROJECT_FITNESS_PARAMETERS_H

namespace ribi{
namespace kp {

class fitness_parameters
{
public:
  fitness_parameters(
    const double fac_opt,
    const double fac_stddev,
    const double unfac_opt,
    const double unfac_stddev
  );
  const double m_fac_opt;
  const double m_fac_stddev;
  const double m_unfac_opt;
  const double m_unfac_stddev;
};

} //~namespace kp
} //~namespace rib

#endif // KORTER_PROJECT_FITNESS_PARAMETERS_H
