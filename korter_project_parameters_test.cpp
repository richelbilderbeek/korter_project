#include "korter_project_parameters.h"
#include "fileio.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include <boost/test/unit_test.hpp>

using namespace ribi::kp;
using namespace ribi::fileio;

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
