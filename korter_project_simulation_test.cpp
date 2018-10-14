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
  const int n_nurse_plants{6};
  parameters p;
  p.set_n_nurse_plants(n_nurse_plants);
  p.set_spatial_width(2);
  p.set_spatial_height(3);
  const simulation s(p);
  BOOST_CHECK_EQUAL(count_n_nurse(s), n_nurse_plants);
}

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_correct_n_seeds)
{
  const int n_seeds{6};
  parameters p;
  p.set_n_nurse_plants(0);
  p.set_n_seeds(n_seeds);
  p.set_spatial_width(3);
  p.set_spatial_height(2);
  const simulation s(p);
  BOOST_CHECK_EQUAL(count_n_seeds(s), n_seeds);
}

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_starts_with_one_histograms)
{
  const int n_seeds{1};
  parameters p;
  p.set_spatial_width(1);
  p.set_spatial_height(1);
  p.set_n_nurse_plants(0);
  p.set_n_seeds(1);
  const simulation s(p);
  BOOST_CHECK_EQUAL(1, s.get_trait_histograms().size());
}

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_increases_number_of__histograms)
{
  const int n_seeds{1};
  parameters p;
  p.set_spatial_width(1);
  p.set_spatial_height(1);
  p.set_n_nurse_plants(0);
  p.set_n_seeds(1);
  simulation s(p);
  s.go_to_next_generation();
  BOOST_CHECK_EQUAL(2, s.get_trait_histograms().size());
}
