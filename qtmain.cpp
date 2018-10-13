#include <QApplication>
#include "qtmutualismbreakdownermenudialog.h"
#include "mutualismbreakdownerparameters.h"
#include "qtmutualismbreakdownerequilibriumdialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::kp::QtMutualismBreakdownerMenuDialog w;
  w.show();
  return a.exec();
}
