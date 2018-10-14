#include "korter_project_simulation.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::kp;

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_operator_equals)
{
  {
    const simulation p;
    const simulation q;
    BOOST_CHECK_EQUAL(p, q);
  }
}

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_correct_n_nurse)
{
  const int n_nurse_plants{42};
  parameters p;
  p.set_n_nurse_plants(n_nurse_plants);
  p.set_spatial_width(100);
  p.set_spatial_height(100);
  const simulation s(p);
  BOOST_CHECK_EQUAL(count_n_nurse(s), n_nurse_plants);
}
