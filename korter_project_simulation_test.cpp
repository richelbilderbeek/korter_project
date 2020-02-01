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

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_increases_number_of_histograms)
{
  const int n_seeds{1};
  parameters p;
  p.set_spatial_width(1);
  p.set_spatial_height(1);
  p.set_n_nurse_plants(0);
  p.set_n_seeds(n_seeds);
  simulation s(p);
  s.go_to_next_generation();
  BOOST_CHECK_EQUAL(2, s.get_trait_histograms().size());
}

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_with_test_grid)
{
  // The parameters for a test grid
  const parameters p = create_test_parameters();
  const simulation s(p);
  BOOST_CHECK_EQUAL(s.get_grid(), create_test_grid());
}

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_collect_traits)
{
  using namespace std;

  // The parameters for a test grid
  const parameters p = create_test_parameters();
  const simulation s(p);
  const std::vector<double> expected = { 0.25, 0.75 };
  const auto created = collect_traits(s.get_grid());
  BOOST_CHECK_EQUAL(2, created.size());
  BOOST_CHECK_EQUAL_COLLECTIONS(
    begin(created), end(created),
    begin(expected), end(expected)
  );
}

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_collect_is_facilitated)
{
  using namespace std;

  // The parameters for a test grid
  const parameters p = create_test_parameters();
  const simulation s(p);
  const std::vector<bool> expected = { false, true };
  const auto created = collect_is_facilitated(s.get_grid());
  BOOST_CHECK_EQUAL(2, created.size());
  BOOST_CHECK_EQUAL_COLLECTIONS(
    begin(created), end(created),
    begin(expected), end(expected)
  );
}

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_count)
{
  using namespace std;

  // The parameters for a test grid
  const parameters p = create_test_parameters();
  const simulation s(p);
  BOOST_CHECK_EQUAL(1, count_n_nurse(s));
  BOOST_CHECK_EQUAL(2, count_n_seeds(s));
  BOOST_CHECK_EQUAL(1, count_n_facilitated_seeds(s.get_grid()));
  BOOST_CHECK_EQUAL(1, count_n_unfacilitated_seeds(s.get_grid()));
  BOOST_CHECK_EQUAL(9, count_n_empty(s.get_grid()));
}

BOOST_AUTO_TEST_CASE(ribi_kp_simulation_calc_fitnesses)
{
  using namespace std;

  // The parameters for a test grid
  const parameters p = create_test_parameters();
  const simulation s(p);
  const auto traits = collect_traits(s.get_grid());
  BOOST_CHECK_EQUAL(traits[0], 0.25);
  BOOST_CHECK_EQUAL(traits[1], 0.75);
  const auto is_facilitated = collect_is_facilitated(s.get_grid());
  BOOST_CHECK_EQUAL(is_facilitated[0], false);
  BOOST_CHECK_EQUAL(is_facilitated[1], true);

  //The fitnesses
  const auto created = calc_fitnesses(s.get_grid(), p);
  BOOST_CHECK_EQUAL(2, created.size());
  const auto fitness_1 = get_fitness(
    p.get_fitness_parameters(),
    traits[0],
    is_facilitated[0]
  );
  const auto fitness_2 = get_fitness(
    p.get_fitness_parameters(),
    traits[1],
    is_facilitated[1]
  );
  const std::vector<double> expected = { fitness_1, fitness_2 };
  BOOST_CHECK_EQUAL_COLLECTIONS(
    begin(created), end(created),
    begin(expected), end(expected)
  );
}

BOOST_AUTO_TEST_CASE(ribi_kp_no_selection_for_max_zero)
{
  // We set a fitness of the facilitated plant
  // We set a zero fitness of the unfacilitated plant
  // We expect the simulation to go to the trait of the facilitated plant

  using namespace std;

  const fitness_parameters fp(
    0.7, //fac_opt
    0.1, //fac_stddev
    1.0, //fac_max <- awesome fitness here
    0.3, //unfac_opt
    0.1, //unfac_stddev
    0.0  //unfac_max <- there is no fitness here
  );
  const parameters p(
    fp,
    0.5, //const double init_trait_mean = 0.5,
    0.1, //const double init_trait_stddev = 0.1,
    0.01, //const double mut_stddev = 0.01,
    25, //const int spatial_height = 1,
    25, //const int spatial_width = 1,
    100, //const int n_nurse_plants = 0,
    200, //const int n_seeds = 0,
    10, //const int n_trait_histogram_bins = 10,
    0, //const int rng_seed = 0,
    0.1, //const double trait_histogram_bin_width = 0.1,
    1000, //const int max_n_generations = 1000,
    "results.csv" //const std::string& results_filename = "results.csv"
  );
  simulation s(p);
  for (int i = 0; i != 100; ++i) {
    s.go_to_next_generation();
  }
  const auto traits = collect_traits(s.get_grid());

  // 625 grid cells
  // 100 nurse plants
  // 200 seeds
  const int n_facilitated_seeds = count_n_facilitated_seeds(s.get_grid());
  const int n_unfacilitated_seeds = count_n_unfacilitated_seeds(s.get_grid());
  assert(p.get_n_seeds() == n_facilitated_seeds + n_unfacilitated_seeds);

  // No fitness at trait 0.3
  const auto n_low = count_if(
    begin(traits), end(traits),
    [](const double trait) { return trait < 0.5; }
  );
  // Awesome fitness at trait 0.7
  const auto n_high = count_if(
    begin(traits), end(traits),
    [](const double trait) { return trait >= 0.5; }
  );
  BOOST_CHECK(n_high > n_low);
}

