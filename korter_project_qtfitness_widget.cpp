#include "korter_project_qtfitness_widget.h"
#include "ui_korter_project_qtfitness_widget.h"

ribi::kp::fitness_widget::fitness_widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::korter_project_qtfitness_widget)
{
  ui->setupUi(this);
  QObject::connect(ui->box_fac_opt, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_fac_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_unfac_opt, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_unfac_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
}

ribi::kp::fitness_widget::~fitness_widget()
{
  delete ui;
}

void ribi::kp::fitness_widget::OnAnyChange()
{
  emit signal_parameters_changed();
}

