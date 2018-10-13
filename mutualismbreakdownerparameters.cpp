#include "mutualismbreakdownerparameters.h"

#include <cassert>
#include <iostream>
#include <boost/units/io.hpp>

ribi::mb::Parameters::Parameters()
  :
    m_spatial_height{10},
    m_spatial_width{10},
    m_initial_loripes_density{0.0},
    m_initial_seagrass_density{0.0},
    m_initial_sulfide_concentration{0.0}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::mb::Parameters::Parameters(
  const int spatial_height,
  const int spatial_width,
  const double initial_loripes_density,
  const double initial_seagrass_density,
  const double initial_sulfide_concentration
) :
    m_spatial_height{spatial_height},
    m_spatial_width{spatial_width},
    m_initial_loripes_density{initial_loripes_density},
    m_initial_seagrass_density{initial_seagrass_density},
    m_initial_sulfide_concentration{initial_sulfide_concentration}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_initial_loripes_density >= 0.0);
  assert(m_initial_seagrass_density >= 0.0);
  assert(m_initial_sulfide_concentration >= 0.0);
}

ribi::mb::Parameters ribi::mb::Parameters::GetTest(const int /* i */)
{

  const Parameters p(
    //0.1 * seconds, //spatial_delta_t,
    10, //spatial_height
    10, //spatial_width
    //0.1 * seconds, //timeplot_delta_t,
    0.1, //initial_loripes_density,
    0.1, //initial_seagrass_density,
    0.0 //any_initial_loripes_density,
    //100 //any_n_timesteps
  );
  return p;
}

/*
void ribi::mb::Parameters::SetTimeplotDeltaT(const Time any_delta_t)
{
  if (any_delta_t <= 0.0 * boost::units::si::seconds)
  {
    std::stringstream s;
    s << "Parameters::SetDeltaT: "
      << "any_delta_t cannot be less or equal to zero, "
      << "obtained value " << any_delta_t;
    throw std::logic_error(s.str());
  }
  m_timeplot_delta_t = any_delta_t;
}
*/

void ribi::mb::Parameters::SetInitialSeagrassDensity(const double any_initial_seagrass_density)
{
  if (any_initial_seagrass_density < 0.0)
  {
    std::stringstream s;
    s << "SetInitialSeagrassDensity: "
      << "any_initial_seagrass_density cannot be less than zero, "
      << "obtained value " << any_initial_seagrass_density
    ;
    throw std::logic_error(s.str());
  }
  m_initial_seagrass_density = any_initial_seagrass_density;
}

std::ostream& ribi::mb::operator<<(std::ostream& os, const Parameters& parameter) noexcept
{
  os
    << parameter.GetSpatialHeight() << " "
    << parameter.GetSpatialWidth() << " "
    << parameter.GetInitialLoripesDensity() << " "
    << parameter.GetInitialSeagrassDensity() << " "
    << parameter.GetInitialSulfidedouble() << " "
  ;
  return os;
}

std::istream& ribi::mb::operator>>(std::istream& is, Parameters& parameter) noexcept
{
  is
    >> parameter.m_spatial_height
    >> parameter.m_spatial_width
    >> parameter.m_initial_loripes_density
    >> parameter.m_initial_seagrass_density
    >> parameter.m_initial_sulfide_concentration
  ;
  return is;
}

bool ribi::mb::operator==(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return
       lhs.GetSpatialHeight() == rhs.GetSpatialHeight()
    && lhs.GetSpatialWidth() == rhs.GetSpatialWidth()
    && lhs.m_initial_loripes_density == rhs.m_initial_loripes_density
    && lhs.m_initial_seagrass_density == rhs.m_initial_seagrass_density
    && lhs.m_initial_sulfide_concentration == rhs.m_initial_sulfide_concentration
  ;

}

bool ribi::mb::operator!=(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return !(lhs == rhs);
}
