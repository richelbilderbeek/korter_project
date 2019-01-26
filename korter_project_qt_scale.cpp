#include "korter_project_qt_scale.h"
#include "ui_korter_project_qt_scale.h"

ribi::kp::qt_scale::qt_scale(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::korter_project_qt_scale)
{
  ui->setupUi(this);
}

ribi::kp::qt_scale::~qt_scale()
{
  delete ui;
}

void ribi::kp::qt_scale::set_min(const double min) noexcept
{
  ui->label_min->setText(QString::number(min));
}

void ribi::kp::qt_scale::set_max(const double max) noexcept
{
  ui->label_max->setText(QString::number(max));
}

void ribi::kp::qt_scale::set_text(const QString& text) noexcept
{
  ui->label_text->setText(text);
}
