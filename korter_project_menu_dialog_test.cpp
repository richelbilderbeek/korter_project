#include "korter_project_menu_dialog.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::kp;

BOOST_AUTO_TEST_CASE(ribi_kp_menu_dialog_member)
{
  const menu_dialog p;
  BOOST_CHECK(!p.GetAbout().GetAuthor().empty());
  BOOST_CHECK(!p.GetHelp().GetVersion().empty());
  BOOST_CHECK(!p.GetVersion().empty());
  BOOST_CHECK(!p.GetVersionHistory().empty());
}
