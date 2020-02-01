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

BOOST_AUTO_TEST_CASE(ribi_kp_fitness_parameters_set_get)
{
  const double fac_opt = 0.5;
  const double fac_stddev = 0.1;
  const double fac_max = 1.0;
  const double unfac_opt = 0.1;
  const double unfac_stddev = 0.3;
  const double unfac_max = 0.5;

  const fitness_parameters p(
    fac_opt,
    fac_stddev,
    fac_max,
    unfac_opt,
    unfac_stddev,
    unfac_max
  );
  BOOST_CHECK_EQUAL(p.get_fac_opt(), fac_opt);
  BOOST_CHECK_EQUAL(p.get_fac_stddev(), fac_stddev);
  BOOST_CHECK_EQUAL(p.get_fac_max(), fac_max);
  BOOST_CHECK_EQUAL(p.get_unfac_opt(), unfac_opt);
  BOOST_CHECK_EQUAL(p.get_unfac_stddev(), unfac_stddev);
  BOOST_CHECK_EQUAL(p.get_unfac_max(), unfac_max);
}

BOOST_AUTO_TEST_CASE(ribi_kp_get_fitness)
{
  /*
  const double fac_opt = 0.5;
  const double fac_stddev = 0.1;
  const double fac_max = 1.0;
  const double unfac_opt = 0.1;
  const double unfac_stddev = 0.3;
  const double unfac_max = 0.5;

  const fitness_parameters p(
    fac_opt,
    fac_stddev,
    fac_max,
    unfac_opt,
    unfac_stddev,
    unfac_max
  )
  p.
  get_fitness(p, 0.5, true);
  */
}
