#include "korter_project_fitness_parameters.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::kp;

BOOST_AUTO_TEST_CASE(ribi_kp_fitness_parameters_operator_equals)
{
  {
    const fitness_parameters p;
    const fitness_parameters q;
    BOOST_CHECK_EQUAL(p, q);
  }
}
