#ifndef MUTUALISMBREAKDOWNER_PARAMETERS_H
#define MUTUALISMBREAKDOWNER_PARAMETERS_H

#include <iosfwd>
#include <memory>

namespace ribi {
namespace mb {

struct Parameters
{
  Parameters();
  Parameters(
    const int spatial_height,
    const int spatial_width,
    const double m_initial_loripes_density,
    const double m_initial_seagrass_density,
    const double any_initial_loripes_density
  );

  int GetSpatialHeight() const noexcept { return m_spatial_height; }
  int GetSpatialWidth() const noexcept { return m_spatial_width; }

  const double& GetInitialLoripesDensity() const noexcept { return m_initial_loripes_density; }
  const double& GetInitialSeagrassDensity() const noexcept { return m_initial_seagrass_density; }
  const double& GetInitialSulfidedouble() const noexcept { return m_initial_sulfide_concentration; }

  ///Create a testing parameter set
  static Parameters GetTest(const int i);

  void SetTimeplotDeltaT(const double any_delta_t);
  void SetInitialSeagrassDensity(const double any_initial_seagrass_density);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif


  private:
  int m_spatial_height;
  int m_spatial_width;

  double m_initial_loripes_density;
  double m_initial_seagrass_density;
  double m_initial_sulfide_concentration;

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

#endif // MUTUALISMBREAKDOWNER_PARAMETERS_H
