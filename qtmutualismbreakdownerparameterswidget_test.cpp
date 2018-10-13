#ifndef NDEBUG
#include "qtmutualismbreakdownerparameterswidget.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include "fileio.h"

#include "ui_qtmutualismbreakdownerparameterswidget.h"

void ribi::kp::QtMutualismBreakdownerParametersWidget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::fileio::FileIo;
  {
    const QtMutualismBreakdownerParametersWidget d;
    const auto p = d.to_parameters();
    const auto q = d.to_parameters();
    assert(p == q);
  }
}
#endif



