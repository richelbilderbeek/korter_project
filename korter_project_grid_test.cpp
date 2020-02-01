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
}
