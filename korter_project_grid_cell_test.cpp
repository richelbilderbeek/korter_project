#include "korter_project_grid_cell.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::kp;

BOOST_AUTO_TEST_CASE(ribi_kp_grid_cell_is_empty_by_default)
{
  const grid_cell p;
  BOOST_CHECK(p.is_empty());
  BOOST_CHECK(!p.is_nurse());
  BOOST_CHECK(!p.is_seed());
  BOOST_CHECK(p.get_trait() < 0.0);
}

BOOST_AUTO_TEST_CASE(ribi_kp_grid_cell_is_constructed_with_a_trait)
{
  const double trait{0.5};
  const grid_cell p(trait);
  BOOST_CHECK(!p.is_empty());
  BOOST_CHECK(!p.is_nurse());
  BOOST_CHECK(p.is_seed());
  BOOST_CHECK_EQUAL(p.get_trait(), trait);
}

BOOST_AUTO_TEST_CASE(ribi_kp_grid_cell_is_constructed_with_a_neutral_marker)
{
  const double trait{0.1};
  const double neutral{0.2};
  const grid_cell p(trait, neutral);
  BOOST_CHECK(!p.is_empty());
  BOOST_CHECK(!p.is_nurse());
  BOOST_CHECK(p.is_seed());
  BOOST_CHECK_EQUAL(p.get_trait(), trait);
  BOOST_CHECK_EQUAL(p.get_neutral(), neutral);
}

BOOST_AUTO_TEST_CASE(ribi_kp_grid_cell_operator_equals)
{
  {
    const grid_cell p;
    const grid_cell q;
    BOOST_CHECK_EQUAL(p, q);
  }
  {
    const double trait{0.5};
    const grid_cell p(trait);
    const grid_cell q(trait);
    BOOST_CHECK_EQUAL(p, q);
  }
  // First is empty
  {
    const grid_cell p;
    const grid_cell q(0.2);
    BOOST_CHECK_NE(p, q);
  }
  // Second is empty
  {
    const grid_cell p(0.1);
    const grid_cell q;
    BOOST_CHECK_NE(p, q);
  }
  // Different traits
  {
    const grid_cell p(0.1);
    const grid_cell q(0.2);
    BOOST_CHECK_NE(p, q);
  }
  // Same trait, same neutral marker
  {
    const double trait{0.5};
    const double neutral{1.2};
    const grid_cell p(trait, neutral);
    const grid_cell q(trait, neutral);
    BOOST_CHECK_EQUAL(p, q);
  }
  // Same trait, different neutral marker
  {
    const double trait{0.5};
    const grid_cell p(trait, 0.2);
    const grid_cell q(trait, 0.6);
    BOOST_CHECK_NE(p, q);
  }
}
