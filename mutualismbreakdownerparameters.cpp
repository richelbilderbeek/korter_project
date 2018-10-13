#include "mutualismbreakdownerparameters.h"

#include <cassert>
#include <iostream>
#include <boost/units/io.hpp>

ribi::kp::Parameters::Parameters()
  :
    m_spatial_height{10},
    m_spatial_width{10},
    m_n_nurse_plants{0},
    m_n_seeds{0},
    m_initial_sulfide_concentration{0.0}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::kp::Parameters::Parameters(
  const int spatial_height,
  const int spatial_width,
  const int n_nurse_plants,
  const int n_seeds,
  const double initial_sulfide_concentration
) :
    m_spatial_height{spatial_height},
    m_spatial_width{spatial_width},
    m_n_nurse_plants{n_nurse_plants},
    m_n_seeds{n_seeds},
    m_initial_sulfide_concentration{initial_sulfide_concentration}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_n_nurse_plants >= 0.0);
  assert(m_n_seeds >= 0.0);
  assert(m_initial_sulfide_concentration >= 0.0);
}

ribi::kp::Parameters ribi::kp::Parameters::GetTest(const int /* i */)
{

  const Parameters p(
    //0.1 * seconds, //spatial_delta_t,
    10, //spatial_height
    10, //spatial_width
    //0.1 * seconds, //timeplot_delta_t,
    0.1, //n_nurse_plants,
    0.1, //n_seeds,
    0.0 //any_n_nurse_plants,
    //100 //any_n_timesteps
  );
  return p;
}

/*
void ribi::kp::Parameters::SetTimeplotDeltaT(const Time any_delta_t)
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

void ribi::kp::Parameters::SetInitialSeagrassDensity(const double any_n_seeds)
{
  if (any_n_seeds < 0.0)
  {
    std::stringstream s;
    s << "SetInitialSeagrassDensity: "
      << "any_n_seeds cannot be less than zero, "
      << "obtained value " << any_n_seeds
    ;
    throw std::logic_error(s.str());
  }
  m_n_seeds = any_n_seeds;
}

std::ostream& ribi::kp::operator<<(std::ostream& os, const Parameters& parameter) noexcept
{
  os
    << parameter.GetSpatialHeight() << " "
    << parameter.GetSpatialWidth() << " "
    << parameter.get_n_nurse_plants() << " "
    << parameter.get_n_seeds() << " "
    << parameter.GetInitialSulfidedouble() << " "
  ;
  return os;
}

std::istream& ribi::kp::operator>>(std::istream& is, Parameters& parameter) noexcept
{
  is
    >> parameter.m_spatial_height
    >> parameter.m_spatial_width
    >> parameter.m_n_nurse_plants
    >> parameter.m_n_seeds
    >> parameter.m_initial_sulfide_concentration
  ;
  return is;
}

bool ribi::kp::operator==(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return
       lhs.GetSpatialHeight() == rhs.GetSpatialHeight()
    && lhs.GetSpatialWidth() == rhs.GetSpatialWidth()
    && lhs.m_n_nurse_plants == rhs.m_n_nurse_plants
    && lhs.m_n_seeds == rhs.m_n_seeds
    && lhs.m_initial_sulfide_concentration == rhs.m_initial_sulfide_concentration
  ;

}

bool ribi::kp::operator!=(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return !(lhs == rhs);
}
