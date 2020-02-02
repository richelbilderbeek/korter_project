


#include "korter_project_menu_dialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

//#include <boost/lexical_cast.hpp>

#include <QFile>

#include "korter_project_menu_dialog.h"
#include "fileio.h"


ribi::kp::menu_dialog::menu_dialog()
{

}

int ribi::kp::menu_dialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1 || argc > 4)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  return 0;
}

ribi::About ribi::kp::menu_dialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Korter Project",
    "simulation",
    "the 2nd of February 2020",
    "2018-2020",
    "https://github.com/richelbilderbeek/korter_project",
    GetVersion(),
    GetVersionHistory()
  );
  return a;
}

std::string ribi::kp::menu_dialog::GetVersion() const noexcept
{
  return "1.2.1";
}

std::vector<std::string> ribi::kp::menu_dialog::GetVersionHistory() const noexcept
{
  return {
    "2018-10-13: Version 0.1: initial version",
    "2018-10-20: Version 0.2: allow to set fitness maximum, "
      "correctly calculate fitness, no crashes, use correct pics"
    "2018-10-21: Version 1.0: first complete version",
    "2020-02-01: Version 1.1: fixed bug",
    "2020-02-02: Version 1.2: added neutral trait",
    "2020-02-02: Version 1.2.1: fix histogram crash"
  };
}

ribi::Help ribi::kp::menu_dialog::GetHelp() const noexcept
{
  return ribi::Help(
    "Korter Project",
    "model",
    {
      //No additional options
    },
    {
    }
  );
}
