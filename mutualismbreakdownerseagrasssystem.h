#ifndef SEAGRASSSYSTEM_H
#define SEAGRASSSYSTEM_H

#include "mutualismbreakdownerparameters.h"

namespace ribi {
namespace mb {

struct SeagrassSystem
{
  SeagrassSystem(const Parameters& parameters);

  void AddSeagrassDensity(const double seagrass_density) { m_seagrass_density += seagrass_density; }
  void Change(const double delta_t);

  const Parameters& GetParameters() const noexcept { return m_parameters; }
  double GetSeagrassDensity() const noexcept { return m_seagrass_density; }
  double GetSulfidedouble() const noexcept { return m_sulfide_concentration; }
  void SetSeagrassDensity(const double seagrass_density) { m_seagrass_density = seagrass_density; }
  void SetSulfidedouble(const double sulfide_concentration) { m_sulfide_concentration = sulfide_concentration; }

  private:
  const Parameters m_parameters;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  double m_seagrass_density;
  double m_sulfide_concentration;
};

} //~namespace mb
} //~namespace ribi

#endif // SEAGRASSSYSTEM_H
