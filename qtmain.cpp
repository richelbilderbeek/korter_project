#include <QApplication>
#include "korter_project_qt_menu_dialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::kp::qt_menu_dialog w;
  w.show();
  return a.exec();
}
