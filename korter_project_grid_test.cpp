#include "korter_project_grid.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::kp;

BOOST_AUTO_TEST_CASE(ribi_kp_grid_operator_equals)
{
  {
    const grid p;
    const grid q;
    BOOST_CHECK_EQUAL(p, q);
  }
}
