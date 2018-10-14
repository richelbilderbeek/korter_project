#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "korter_project_qt_menu_dialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "korter_project_menu_dialog.h"
#include "korter_project_qt_simulation_dialog.h"
#include "ui_korter_project_qt_menu_dialog.h"
#pragma GCC diagnostic pop


ribi::kp::qt_menu_dialog::qt_menu_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qt_menu_dialog)
{
  ui->setupUi(this);
}

ribi::kp::qt_menu_dialog::~qt_menu_dialog() noexcept
{
  delete ui;
}

void ribi::kp::qt_menu_dialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}


void ribi::kp::qt_menu_dialog::on_button_about_clicked()
{
  About a = ribi::kp::menu_dialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::kp::qt_menu_dialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::kp::qt_menu_dialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  qt_menu_dialog();
}
#endif

void ribi::kp::qt_menu_dialog::on_button_start_clicked()
{
  korter_project_qt_simulation_dialog d;
  this->hide();
  d.exec();
  this->show();
}
