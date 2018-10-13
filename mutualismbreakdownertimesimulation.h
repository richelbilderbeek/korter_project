#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "mutualismbreakdownerparameters.h"

namespace ribi {
namespace mb {

struct TimeSimulation
{
  using SpeciesDensities = std::vector<double>;
  using doubles = std::vector<double>;

  TimeSimulation(const Parameters& parameters);

  const Parameters& GetParameters() const noexcept { return m_parameters; }
  const SpeciesDensities& GetSeagrassDensities() const noexcept { return m_seagrass_densities; }
  const doubles& GetSulfidedoubles() const noexcept { return m_sulfide_concentrations; }
  const std::vector<double>& GetTimeSeries() const noexcept { return m_timeseries; }

  void Run();

  private:
  const Parameters m_parameters;

  std::vector<double> m_seagrass_densities;
  std::vector<double> m_sulfide_concentrations;
  std::vector<double> m_timeseries;
};

std::ostream& operator<<(std::ostream& os, const TimeSimulation& simulation) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // SIMULATION_H
