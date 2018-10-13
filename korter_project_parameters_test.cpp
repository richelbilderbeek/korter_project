#ifndef NDEBUG
#include "korter_project_parameters.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include "fileio.h"

void ribi::kp::parameters::Test() noexcept
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
    parameters p;
    parameters q;
    assert(p == q);
  }
  //DeltaT
  //Change of n_nurse_plants
  {
    parameters p;
    parameters q;
    q.m_n_nurse_plants
      = p.m_n_nurse_plants
      + 1
    ;
    assert(p != q);

  }
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
    p.m_n_seeds = d;
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
    assert(p2.m_n_seeds == d);
    assert(p2 == p);
    FileIo().DeleteFile(filename);
  }
}
#endif

