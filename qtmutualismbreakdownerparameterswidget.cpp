#include "qtmutualismbreakdownerparameterswidget.h"

#include <cassert>
#include <fstream>
#include <QFileDialog>

#include "korter_project_qt_fitness_widget.h"
#include "ui_qtmutualismbreakdownerparameterswidget.h"

ribi::kp::QtMutualismBreakdownerParametersWidget::QtMutualismBreakdownerParametersWidget(QWidget *parent) :
  QWidget(parent),
  m_fitness_widget(new qt_fitness_widget),
  ui(new Ui::QtMutualismBreakdownerParametersWidget)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  {
    using Layout = QGridLayout;
    Layout * const my_layout{
      dynamic_cast<Layout*>(ui->page_fitness->layout())
    };
    assert(my_layout);
    my_layout->addWidget(m_fitness_widget);
  }


  QObject::connect(ui->box_spatial_height,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_spatial_width,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_n_nurse_plants,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_n_seeds,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_rng_seed,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(m_fitness_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
}

ribi::kp::QtMutualismBreakdownerParametersWidget::~QtMutualismBreakdownerParametersWidget()
{
  delete ui;
}

ribi::kp::parameters ribi::kp::QtMutualismBreakdownerParametersWidget::to_parameters() const
{
  const parameters p(
    m_fitness_widget->to_parameters(),
    ui->box_spatial_height->value(),
    ui->box_spatial_width->value(),
    ui->box_n_nurse_plants->value(),
    ui->box_n_seeds->value(),
    ui->box_rng_seed->value()
  );

  return p;
}

void ribi::kp::QtMutualismBreakdownerParametersWidget::SetParameters(const parameters& parameters)
{
  ui->box_spatial_height->setValue(parameters.get_spatial_height());
  ui->box_spatial_width->setValue(parameters.get_spatial_width());
  ui->box_n_nurse_plants->setValue(parameters.get_n_nurse_plants());
  ui->box_n_seeds->setValue(parameters.get_n_seeds());
  ui->box_rng_seed->setValue(parameters.get_rng_seed());
}

void ribi::kp::QtMutualismBreakdownerParametersWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void ribi::kp::QtMutualismBreakdownerParametersWidget::on_button_save_clicked()
{
  const std::string filename{
    QFileDialog::getSaveFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ofstream f(filename);
  f << to_parameters();
}

void ribi::kp::QtMutualismBreakdownerParametersWidget::on_button_load_clicked()
{
  const std::string filename{
    QFileDialog::getOpenFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ifstream f(filename);
  parameters parameters;
  f >> parameters;
  SetParameters(parameters);
}
