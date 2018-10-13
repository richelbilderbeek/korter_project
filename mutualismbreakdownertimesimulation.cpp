#include "mutualismbreakdownertimesimulation.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/units/systems/si.hpp>
#include <boost/units/io.hpp>

#include "mutualismbreakdownerseagrasssystem.h"

ribi::mb::TimeSimulation::TimeSimulation(const Parameters& parameters)
  : m_parameters{parameters},
    m_seagrass_densities{},
    m_sulfide_concentrations{},
    m_timeseries{}

{

}

void ribi::mb::TimeSimulation::Run()
{
  const int n_timesteps{100}; //STUB
  assert(n_timesteps >= 0);
  const double t_end = 1.0;

  const auto delta_t = 0.1;

  const int sz{static_cast<int>(t_end / delta_t)};
  assert(sz > 0);
  const int track_after{std::max(1,sz / 1000)};
  assert(track_after > 0);

  SeagrassSystem seagrass_system(m_parameters);

  int i=0;
  for (double t=0.0; t<t_end; t+=delta_t)
  {
    assert(i >= 0);
    try
    {
      seagrass_system.Change(delta_t);
    }
    catch (std::logic_error& e)
    {
      std::stringstream s;
      s << __func__ << ": Change: " << e.what();
      std::clog << s.str() << std::endl;
      return;
    }
    if (i % track_after == 0)
    {    
      m_timeseries.push_back(t);
      m_seagrass_densities.push_back(seagrass_system.GetSeagrassDensity());
      m_sulfide_concentrations.push_back(seagrass_system.GetSulfidedouble());
    }
    ++i;
  }

}

std::ostream& ribi::mb::operator<<(std::ostream& os, const TimeSimulation& simulation) noexcept
{
  const std::vector<double>& t{simulation.GetTimeSeries()};
  const auto& n = simulation.GetSeagrassDensities();
  const auto& s = simulation.GetSulfidedoubles();
  std::stringstream stream;
  assert(t.size() == n.size());
  assert(t.size() == s.size());
  const int sz{static_cast<int>(t.size())};
  for (int i = 0; i!=sz; ++i)
  {
    stream << t[i] << " " << n[i] << " " << s[i] <<  '\n';
  }
  std::string str{stream.str()};
  if (!str.empty()) str.pop_back();
  os << str;
  return os;
}
