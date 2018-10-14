#include "korter_project_qt_parameters_widget.h"

#include <cassert>
#include <fstream>
#include <QFileDialog>

#include "korter_project_qt_fitness_widget.h"
#include "ui_korter_project_qt_parameters_widget.h"


ribi::kp::korter_project_qt_parameters_widget::korter_project_qt_parameters_widget(QWidget *parent) :
  QWidget(parent),
  m_fitness_widget(new qt_fitness_widget),
  ui(new Ui::korter_project_qt_parameters_widget)
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
  QObject::connect(ui->box_init_trait_mean, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_init_trait_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_mut_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
}

ribi::kp::korter_project_qt_parameters_widget::~korter_project_qt_parameters_widget()
{
  delete ui;
}

ribi::kp::parameters ribi::kp::korter_project_qt_parameters_widget::to_parameters() const
{
  const parameters p(
    m_fitness_widget->to_parameters(),
    ui->box_init_trait_mean->value(),
    ui->box_init_trait_stddev->value(),
    ui->box_mut_stddev->value(),
    ui->box_spatial_height->value(),
    ui->box_spatial_width->value(),
    ui->box_n_nurse_plants->value(),
    ui->box_n_seeds->value(),
    ui->box_rng_seed->value()
  );

  return p;
}

void ribi::kp::korter_project_qt_parameters_widget::set(const parameters& parameters)
{
  m_fitness_widget->set(parameters.get_fitness_parameters());

  ui->box_init_trait_mean->setValue(parameters.get_init_trait_mean());
  ui->box_init_trait_stddev->setValue(parameters.get_init_trait_stddev());
  ui->box_mut_stddev->setValue(parameters.get_mut_stddev());
  ui->box_n_nurse_plants->setValue(parameters.get_n_nurse_plants());
  ui->box_n_seeds->setValue(parameters.get_n_seeds());
  ui->box_rng_seed->setValue(parameters.get_rng_seed());
  ui->box_spatial_height->setValue(parameters.get_spatial_height());
  ui->box_spatial_width->setValue(parameters.get_spatial_width());


}

void ribi::kp::korter_project_qt_parameters_widget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void ribi::kp::korter_project_qt_parameters_widget::on_button_save_clicked()
{
  const std::string filename{
    QFileDialog::getSaveFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ofstream f(filename);
  f << to_parameters();
}

void ribi::kp::korter_project_qt_parameters_widget::on_button_load_clicked()
{
  const std::string filename{
    QFileDialog::getOpenFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ifstream f(filename);
  parameters parameters;
  f >> parameters;
  set(parameters);
}
