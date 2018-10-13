#include "korter_project_qt_fitness_widget.h"
#include "ui_korter_project_qtfitness_widget.h"

ribi::kp::qt_fitness_widget::qt_fitness_widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::korter_project_qt_fitness_widget)
{
  ui->setupUi(this);
  QObject::connect(ui->box_fac_opt, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_fac_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_unfac_opt, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_unfac_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
}

ribi::kp::qt_fitness_widget::~qt_fitness_widget()
{
  delete ui;
}

ribi::kp::fitness_parameters ribi::kp::qt_fitness_widget::to_parameters() const noexcept
{
  return fitness_parameters(
    ui->box_fac_opt->value(),
    ui->box_fac_stddev->value(),
    ui->box_unfac_opt->value(),
    ui->box_unfac_stddev->value()
  );
}

void ribi::kp::qt_fitness_widget::OnAnyChange()
{
  emit signal_parameters_changed();
}

