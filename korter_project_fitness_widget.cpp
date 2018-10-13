#include "korter_project_fitness_widget.h"
#include "ui_korter_project_fitness_widget.h"

ribi::kp::fitness_widget::fitness_widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::korter_project_fitness_widget)
{
  ui->setupUi(this);
}

ribi::kp::fitness_widget::~fitness_widget()
{
  delete ui;
}
