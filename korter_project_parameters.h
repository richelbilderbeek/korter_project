#ifndef KORTER_PROJECT_PARAMETERS_H
#define KORTER_PROJECT_PARAMETERS_H

#include <iosfwd>
#include <memory>

#include "korter_project_fitness_parameters.h"

namespace ribi {
namespace kp {

struct parameters
{
  explicit parameters(
    const fitness_parameters& fp = fitness_parameters(),
    const int spatial_height = 1,
    const int spatial_width = 1,
    const int n_nurse_plants = 0,
    const int n_seeds = 0,
    const int rng_seed = 0
  );

  int get_spatial_height() const noexcept { return m_spatial_height; }
  int get_spatial_width() const noexcept { return m_spatial_width; }
  int get_n_nurse_plants() const noexcept { return m_n_nurse_plants; }
  int get_n_seeds() const noexcept { return m_n_seeds; }
  int get_rng_seed() const noexcept { return m_rng_seed; }

  ///Create a testing parameter set
  static parameters GetTest(const int i);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif


  private:
  const fitness_parameters m_fitness_parameters;
  int m_spatial_height;
  int m_spatial_width;

  int m_n_nurse_plants;
  int m_n_seeds;
  int m_rng_seed;

  friend std::ostream& operator<<(std::ostream& os, const parameters& parameter) noexcept;
  friend std::istream& operator>>(std::istream& is, parameters& parameter) noexcept;
  friend bool operator==(const parameters& lhs, const parameters& rhs) noexcept;
};

bool operator==(const parameters& lhs, const parameters& rhs) noexcept;
bool operator!=(const parameters& lhs, const parameters& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const parameters& parameter) noexcept;
std::istream& operator>>(std::istream& is, parameters& parameter) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // KORTER_PROJECT_PARAMETERS_H
