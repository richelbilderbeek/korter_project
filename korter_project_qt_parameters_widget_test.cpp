#ifndef NDEBUG
#include "korter_project_qt_parameters_widget.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include "fileio.h"

#include "ui_korter_project_qt_parameters_widget.h"

void ribi::kp::korter_project_qt_parameters_widget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::fileio::FileIo;
  {
    const korter_project_qt_parameters_widget d;
    const auto p = d.to_parameters();
    const auto q = d.to_parameters();
    assert(p == q);
  }
}
#endif



