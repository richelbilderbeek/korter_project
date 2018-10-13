#include "qtmutualismbreakdownerparameterswidget.h"

#include <cassert>
#include <fstream>
#include <QFileDialog>

#include "ui_qtmutualismbreakdownerparameterswidget.h"

ribi::kp::QtMutualismBreakdownerParametersWidget::QtMutualismBreakdownerParametersWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtMutualismBreakdownerParametersWidget)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  /*
  {
    using Layout = QGridLayout;
    Layout * const my_layout{
      dynamic_cast<Layout*>(ui->page_poisoning->layout())
    };
    assert(my_layout);
    my_layout->addWidget(m_qtpoisoningwidget);
  }
  */


  QObject::connect(ui->box_spatial_height,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_spatial_width,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initial_loripes_density,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initial_seagrass_density,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initial_sulfide_concentration,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(m_qtpoisoningwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
}

ribi::kp::QtMutualismBreakdownerParametersWidget::~QtMutualismBreakdownerParametersWidget()
{
  delete ui;
}

ribi::kp::Parameters ribi::kp::QtMutualismBreakdownerParametersWidget::GetParameters() const
{
  const Parameters p(
    ui->box_spatial_height->value(),
    ui->box_spatial_width->value(),
    ui->box_initial_loripes_density->value(),
    ui->box_initial_seagrass_density->value(),
    ui->box_initial_sulfide_concentration->value()
  );

  return p;
}

void ribi::kp::QtMutualismBreakdownerParametersWidget::SetParameters(const Parameters& parameters)
{
  ui->box_spatial_height->setValue(parameters.GetSpatialHeight());
  ui->box_spatial_width->setValue(parameters.GetSpatialWidth());
  ui->box_initial_loripes_density->setValue(parameters.GetInitialLoripesDensity());
  ui->box_initial_seagrass_density->setValue(parameters.GetInitialSeagrassDensity());
  ui->box_initial_sulfide_concentration->setValue(parameters.GetInitialSulfidedouble());
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
  f << GetParameters();
}

void ribi::kp::QtMutualismBreakdownerParametersWidget::on_button_load_clicked()
{
  const std::string filename{
    QFileDialog::getOpenFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ifstream f(filename);
  Parameters parameters;
  f >> parameters;
  SetParameters(parameters);
}
