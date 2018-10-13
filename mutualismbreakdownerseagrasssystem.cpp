#include "mutualismbreakdownerseagrasssystem.h"

#include <iostream>
#include <sstream>

ribi::mb::SeagrassSystem::SeagrassSystem(const Parameters& parameters)
  : m_parameters{parameters},
    m_seagrass_density{parameters.GetInitialSeagrassDensity()},
    m_sulfide_concentration{parameters.GetInitialSulfidedouble()}
{

}

void ribi::mb::SeagrassSystem::Change(const double delta_t)
{
  //Seagrass
  try
  {
    const auto delta_n = 0.1;
    m_seagrass_density += (delta_n * delta_t);
  }
  catch (std::logic_error& e)
  {
    std::stringstream s;
    s << __func__ << ": calculating seagrass density: " << e.what();
    std::clog << s.str() << std::endl;
    return;
  }
  //Sulfide
  try
  {
    const auto delta_s = 0.1;

    m_sulfide_concentration += (delta_s * delta_t);

  }
  catch (std::logic_error& e)
  {
    std::stringstream s;
    s << __func__ << ":, calculating sulfide concentration: " << e.what();
    std::clog << s.str() << std::endl;
    return;
  }
}
