#include <QApplication>
#include "qtmutualismbreakdownermenudialog.h"
#include "mutualismbreakdownerpoisoningfunction.h"
#include "mutualismbreakdownersulfideconsumptionfunction.h"
#include "mutualismbreakdownerparameters.h"
#include "qtmutualismbreakdownerequilibriumdialog.h"
#include "qtmutualismbreakdownertimeplotdialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::mb::QtMutualismBreakdownerMenuDialog w;
  w.show();
  return a.exec();
}
