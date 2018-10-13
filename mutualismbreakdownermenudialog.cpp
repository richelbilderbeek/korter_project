#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "mutualismbreakdownermenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include <QFile>

#include "mutualismbreakdownermenudialog.h"
#include "fileio.h"
#pragma GCC diagnostic pop

ribi::mb::MenuDialog::MenuDialog()
{

}

int ribi::mb::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1 || argc > 4)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  return 0;
}

ribi::About ribi::mb::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "korter_project",
    "simulation",
    "the 13th of October 2018",
    "2018",
    "https://github.com/richelbilderbeek/korter_project",
    GetVersion(),
    GetVersionHistory()
  );
  return a;
}

std::string ribi::mb::MenuDialog::GetVersion() const noexcept
{
  return "0.1";
}

std::vector<std::string> ribi::mb::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2018-10-13: Version 0.1: initial version "
  };
}

ribi::Help ribi::mb::MenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    "korter_project",
    "model",
    {
      //No additional options
    },
    {
    }
  );
}
