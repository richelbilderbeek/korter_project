#ifndef KORTER_PROJECT_FITNESS_PARAMETERS_H
#define KORTER_PROJECT_FITNESS_PARAMETERS_H

#include <iosfwd>

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
  ///Get the optimum trait value for a facilitated plant
  double get_fac_opt() const noexcept { return m_fac_opt; }

  ///Get the standard deviation around the optimal trait value for a facilitated plant
  double get_fac_stddev() const noexcept { return m_fac_stddev; }

  ///Get the optimum trait value for an unfacilitated plant
  double get_unfac_opt() const noexcept { return m_unfac_opt; }

  ///Get the standard deviation around the optimal trait value for an unfacilitated plant
  double get_unfac_stddev() const noexcept { return m_unfac_stddev; }

private:
  double m_fac_opt;
  double m_fac_stddev;
  double m_unfac_opt;
  double m_unfac_stddev;

  friend std::ostream& operator<<(std::ostream& os, const fitness_parameters& fp) noexcept;
  friend std::istream& operator>>(std::istream& is, fitness_parameters& parameter) noexcept;
};

///Density of Gauss curve with mean zero, standard deviation of sd,
///at position x
double gauss(const double x, const double sd) noexcept;

///Density of normal with mean 'mean', standard deviation'sd',
///at position x
double normal(const double x, const double mean, const double sd) noexcept;

bool operator==(const fitness_parameters& lhs, const fitness_parameters& rhs) noexcept;
bool operator!=(const fitness_parameters& lhs, const fitness_parameters& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const fitness_parameters& fp) noexcept;
std::istream& operator>>(std::istream& is, fitness_parameters& parameter) noexcept;

} //~namespace kp
} //~namespace rib

#endif // KORTER_PROJECT_FITNESS_PARAMETERS_H
