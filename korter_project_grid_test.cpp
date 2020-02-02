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

BOOST_AUTO_TEST_CASE(ribi_kp_grid_size)
{
  const int width{2};
  const int height{3};
  const grid p(width, height);
  BOOST_CHECK_EQUAL(p.get_width(), width);
  BOOST_CHECK_EQUAL(p.get_height(), height);
}

BOOST_AUTO_TEST_CASE(ribi_kp_get)
{
  const int width{2};
  const int height{5};
  const grid p(width, height);
  const int x{1};
  const int y{4};
  BOOST_CHECK(p.get(x, y).is_empty());
}

BOOST_AUTO_TEST_CASE(ribi_kp_set)
{
  const int width{2};
  const int height{5};
  grid p(width, height);
  const int x{1};
  const int y{4};
  assert(p.get(x, y).is_empty());
  p.get(x, y).make_nurse();
  BOOST_CHECK(p.get(x, y).is_nurse());
}

BOOST_AUTO_TEST_CASE(ribi_kp_grid_is_empty)
{
  const int width{3};
  const int height{4};
  grid p(width, height);
  BOOST_CHECK(is_empty(p));
  p.get(1, 2).make_nurse();
  BOOST_CHECK(!is_empty(p));
}

BOOST_AUTO_TEST_CASE(ribi_kp_test_grid_is_setup_as_expected)
{
  /// Create a 4x3 (width x height) grid to be used in testing.
  /// This is the layout of the grid:
  ///
  ///   |0123|
  ///  -|----+-
  ///  0|....|0
  ///  1|.N.U|1
  ///  2|.F..|2
  ///  -|----+-
  ///   |0123|
  ///
  /// N: Nurse plant
  /// F: Facilitated plant/seed, because adjacent to nurse
  /// U: Unfacilitated plant/seed, because not adjacent to nurse
  const grid g = create_test_grid();
  BOOST_CHECK_EQUAL(4, g.get_width());
  BOOST_CHECK_EQUAL(3, g.get_height());
  BOOST_CHECK(g.get(0, 0).is_empty());
  BOOST_CHECK(g.get(1, 0).is_empty());
  BOOST_CHECK(g.get(2, 0).is_empty());
  BOOST_CHECK(g.get(3, 0).is_empty());

  BOOST_CHECK(g.get(0, 1).is_empty());
  BOOST_CHECK(g.get(1, 1).is_nurse()); //N
  BOOST_CHECK(g.get(2, 1).is_empty());
  BOOST_CHECK(g.get(3, 1).is_seed()); //U
  BOOST_CHECK_EQUAL(g.get(3, 1).get_trait(), 0.25); //U
  BOOST_CHECK_EQUAL(g.get(3, 1).get_neutral(), 0.1); //U

  BOOST_CHECK(g.get(0, 2).is_empty());
  BOOST_CHECK(g.get(1, 2).is_seed()); //F
  BOOST_CHECK_EQUAL(g.get(1, 2).get_trait(), 0.75); //F
  BOOST_CHECK_EQUAL(g.get(1, 2).get_neutral(), 0.9); //F
  BOOST_CHECK(g.get(2, 2).is_empty());
  BOOST_CHECK(g.get(3, 2).is_empty());
}

BOOST_AUTO_TEST_CASE(ribi_kp_test_grid_calc_frac_fac)
{
  const grid g = create_test_grid();
  BOOST_CHECK_EQUAL(1, count_n_facilitated_seeds(g));
  BOOST_CHECK_EQUAL(1, count_n_unfacilitated_seeds(g));
  BOOST_CHECK_EQUAL(0.5, calc_frac_fac_seeds(g));
}
