#include <QApplication>
#include "korter_project_qt_menu_dialog.h"
#include "mutualismbreakdownerparameters.h"
#include "qtmutualismbreakdownerequilibriumdialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::kp::qt_menu_dialog w;
  w.show();
  return a.exec();
}
