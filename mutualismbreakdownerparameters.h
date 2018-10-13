#ifndef KORTER_PROJECT_PARAMETERS_H
#define KORTER_PROJECT_PARAMETERS_H

#include <iosfwd>
#include <memory>

namespace ribi {
namespace kp {

struct Parameters
{
  Parameters();
  Parameters(
    const int spatial_height,
    const int spatial_width,
    const int n_nurse_plants,
    const int n_seeds,
    const int rng_seed
  );

  int GetSpatialHeight() const noexcept { return m_spatial_height; }
  int GetSpatialWidth() const noexcept { return m_spatial_width; }

  int get_n_nurse_plants() const noexcept { return m_n_nurse_plants; }
  int get_n_seeds() const noexcept { return m_n_seeds; }
  int get_rng_seed() const noexcept { return m_rng_seed; }

  ///Create a testing parameter set
  static Parameters GetTest(const int i);

  void SetTimeplotDeltaT(const double any_delta_t);
  void SetInitialSeagrassDensity(const double any_n_seeds);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif


  private:
  int m_spatial_height;
  int m_spatial_width;

  int m_n_nurse_plants;
  int m_n_seeds;
  int m_rng_seed;

  friend std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept;
  friend std::istream& operator>>(std::istream& is, Parameters& parameter) noexcept;
  friend bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept;
};

bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept;
bool operator!=(const Parameters& lhs, const Parameters& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept;
std::istream& operator>>(std::istream& is, Parameters& parameter) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // KORTER_PROJECT_PARAMETERS_H
