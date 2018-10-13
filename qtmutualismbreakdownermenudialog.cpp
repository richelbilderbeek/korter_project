#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmutualismbreakdownermenudialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "mutualismbreakdownermenudialog.h"
#include "qtmutualismbreakdownerspatialplotdialog.h"
#include "qtmutualismbreakdownerequilibriumdialog.h"
#include "ui_qtmutualismbreakdownermenudialog.h"
#pragma GCC diagnostic pop


ribi::kp::QtMutualismBreakdownerMenuDialog::QtMutualismBreakdownerMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtMutualismBreakdownerMenuDialog)
{
  ui->setupUi(this);
}

ribi::kp::QtMutualismBreakdownerMenuDialog::~QtMutualismBreakdownerMenuDialog() noexcept
{
  delete ui;
}

void ribi::kp::QtMutualismBreakdownerMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}


void ribi::kp::QtMutualismBreakdownerMenuDialog::on_button_about_clicked()
{
  About a = ribi::kp::MenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::kp::QtMutualismBreakdownerMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::kp::QtMutualismBreakdownerMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtMutualismBreakdownerMenuDialog();
}
#endif

void ribi::kp::QtMutualismBreakdownerMenuDialog::on_button_start_clicked()
{
  QtMutualismBreakdownerSpatialPlotDialog d;
  ShowChild(&d);
}
