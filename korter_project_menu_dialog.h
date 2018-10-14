#ifndef KORTER_PROJECT_MENUDIALOG_H
#define KORTER_PROJECT_MENUDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include "about.h"
#include "menudialog.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace kp {

struct menu_dialog final : public ::ribi::MenuDialog
{
  menu_dialog();
  ~menu_dialog() noexcept {}
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;

  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;
};

} //~namespace mb
} //~namespace ribi

#endif // KORTER_PROJECT_MENUDIALOG_H
