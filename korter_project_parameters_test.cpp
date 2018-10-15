#include "korter_project_parameters.h"
#include "fileio.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include <boost/test/unit_test.hpp>

using namespace ribi::kp;
using namespace ribi::fileio;

BOOST_AUTO_TEST_CASE(ribi_kp_parameters_construction)
{
  const fitness_parameters fp;
  const double init_trait_mean{0.12};
  const double init_trait_stddev{0.23};
  const double mut_stddev{0.34};
  const int spatial_height{4};
  const int spatial_width{5};
  const int n_nurse_plants{6};
  const int n_seeds{7};
  const int n_trait_histogram_bins{8};
  const int rng_seed{9};
  const double trait_histogram_bin_width{0.11};

  const parameters p(
    fp,
    init_trait_mean,
    init_trait_stddev,
    mut_stddev,
    spatial_height,
    spatial_width,
    n_nurse_plants,
    n_seeds,
    n_trait_histogram_bins,
    rng_seed,
    trait_histogram_bin_width
  );
  BOOST_CHECK_EQUAL(fp, p.get_fitness_parameters());
  BOOST_CHECK_EQUAL(init_trait_mean, p.get_init_trait_mean());
  BOOST_CHECK_EQUAL(init_trait_stddev, p.get_init_trait_stddev());
  BOOST_CHECK_EQUAL(mut_stddev, p.get_mut_stddev());
  BOOST_CHECK_EQUAL(spatial_height, p.get_spatial_height());
  BOOST_CHECK_EQUAL(spatial_width, p.get_spatial_width());
  BOOST_CHECK_EQUAL(n_nurse_plants, p.get_n_nurse_plants());
  BOOST_CHECK_EQUAL(n_seeds, p.get_n_seeds());
  BOOST_CHECK_EQUAL(n_trait_histogram_bins, p.get_n_trait_histogram_bins());
  BOOST_CHECK_EQUAL(rng_seed, p.get_rng_seed());
  BOOST_CHECK_EQUAL(trait_histogram_bin_width, p.get_trait_histogram_bin_width());

}


BOOST_AUTO_TEST_CASE(ribi_kp_parameters_operator_equals)
{
  {
    const parameters p;
    const parameters q;
    BOOST_CHECK_EQUAL(p, q);
  }
  //Change of n_nurse_plants
  {
    parameters p;
    parameters q;
    q.set_n_nurse_plants(p.get_n_nurse_plants() + 1);
    BOOST_CHECK_NE(p, q);
  }
}

BOOST_AUTO_TEST_CASE(ribi_kp_parameters_file_io_one)
{
  //File I/O, one Parameters
  {
    parameters p;
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << p;
    }
    std::ifstream f(filename);
    parameters p2;
    f >> p2;
    assert(p2 == p);
    FileIo().DeleteFile(filename);
  }
}

BOOST_AUTO_TEST_CASE(ribi_kp_parameters_file_io_two)
{
  //File I/O, two Parameters
  {
    parameters parameters_a;
    parameters parameters_b;
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << parameters_a << " " << parameters_b;
    }
    std::ifstream f(filename);
    parameters parameters_a_too;
    parameters parameters_b_too;
    f >> parameters_a_too >> parameters_b_too;
    assert(parameters_a_too == parameters_a);
    assert(parameters_b_too == parameters_b);
    FileIo().DeleteFile(filename);
  }
  //File I/O of initial_species_density
  {
    parameters p;
    const int d{
      23
    };
    p.set_n_seeds(d);
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << p;
    }
    std::ifstream f(filename);
    parameters p2;
    f >> p2;
    assert(p2.get_n_seeds() == d);
    assert(p2 == p);
    FileIo().DeleteFile(filename);
  }
}
