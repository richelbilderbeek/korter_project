#ifndef NDEBUG
#include "mutualismbreakdownerparameters.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include <boost/units/io.hpp>

#include "fileio.h"

void ribi::kp::Parameters::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
  }
  using ribi::fileio::FileIo;
  //operator==
  {
    Parameters p;
    Parameters q;
    assert(p == q);
  }
  //DeltaT
  //Change of n_nurse_plants
  {
    Parameters p;
    Parameters q;
    q.m_n_nurse_plants
      = p.m_n_nurse_plants
      + 1
    ;
    assert(p != q);

  }
  //File I/O, one Parameters
  {
    Parameters parameters;
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << parameters;
    }
    std::ifstream f(filename);
    Parameters parameters_too;
    f >> parameters_too;
    assert(parameters_too == parameters);
    FileIo().DeleteFile(filename);
  }
  //File I/O, two Parameters
  {
    Parameters parameters_a;
    Parameters parameters_b;
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << parameters_a << " " << parameters_b;
    }
    std::ifstream f(filename);
    Parameters parameters_a_too;
    Parameters parameters_b_too;
    f >> parameters_a_too >> parameters_b_too;
    assert(parameters_a_too == parameters_a);
    assert(parameters_b_too == parameters_b);
    FileIo().DeleteFile(filename);
  }
  //File I/O of initial_species_density
  {
    Parameters parameters;
    const int d{
      23
    };
    parameters.m_n_seeds = d;
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << parameters;
    }
    std::ifstream f(filename);
    Parameters parameters_too;
    f >> parameters_too;
    assert(parameters_too.m_n_seeds == d);
    assert(parameters_too == parameters);
    FileIo().DeleteFile(filename);
  }
}
#endif

