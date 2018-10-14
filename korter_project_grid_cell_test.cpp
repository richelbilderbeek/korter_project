#include "korter_project_grid_cell.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::kp;

BOOST_AUTO_TEST_CASE(ribi_kp_grid_cell_operator_equals)
{
  {
    const grid_cell p;
    const grid_cell q;
    BOOST_CHECK_EQUAL(p, q);
  }
}
