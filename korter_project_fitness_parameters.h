#ifndef KORTER_PROJECT_FITNESS_PARAMETERS_H
#define KORTER_PROJECT_FITNESS_PARAMETERS_H

namespace ribi{
namespace kp {

class fitness_parameters
{
public:
  explicit fitness_parameters(
    const double fac_opt = 0.0,
    const double fac_stddev = 0.0,
    const double unfac_opt = 0.0,
    const double unfac_stddev = 0.0
  );
  const double m_fac_opt;
  const double m_fac_stddev;
  const double m_unfac_opt;
  const double m_unfac_stddev;
};

///Density of Gauss curve with mean zero, standard deviation of sd,
///at position x
double gauss(const double x, const double sd) noexcept;

///Density of normal with mean 'mean', standard deviation'sd',
///at position x
double normal(const double x, const double mean, const double sd) noexcept;

bool operator==(const fitness_parameters& lhs, const fitness_parameters& rhs) noexcept;
bool operator!=(const fitness_parameters& lhs, const fitness_parameters& rhs) noexcept;

} //~namespace kp
} //~namespace rib

#endif // KORTER_PROJECT_FITNESS_PARAMETERS_H
