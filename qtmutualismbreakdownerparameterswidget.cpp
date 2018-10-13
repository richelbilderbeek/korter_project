#include "qtmutualismbreakdownerparameterswidget.h"

#include <cassert>
#include <fstream>
#include <QFileDialog>

#include "qtpoisoningfunctionwidget.h"
#include "qtseagrasscolonisationfunctionwidget.h"
#include "qtseagrassgrowthfunctionwidget.h"
#include "qtsulfideconsumptionfunctionwidget.h"
#include "qtsulfidedetoxificationfunctionwidget.h"
#include "qtsulfidediffusionfunctionwidget.h"
#include "qtsulfideproductionfunctionwidget.h"
#include "ui_qtmutualismbreakdownerparameterswidget.h"

ribi::mb::QtMutualismBreakdownerParametersWidget::QtMutualismBreakdownerParametersWidget(QWidget *parent) :
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

ribi::mb::QtMutualismBreakdownerParametersWidget::~QtMutualismBreakdownerParametersWidget()
{
  delete ui;
}

ribi::mb::Parameters ribi::mb::QtMutualismBreakdownerParametersWidget::GetParameters() const
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

void ribi::mb::QtMutualismBreakdownerParametersWidget::SetParameters(const Parameters& parameters)
{
  ui->box_spatial_height->setValue(parameters.GetSpatialHeight());
  ui->box_spatial_width->setValue(parameters.GetSpatialWidth());
  ui->box_initial_loripes_density->setValue(parameters.GetInitialLoripesDensity());
  ui->box_initial_seagrass_density->setValue(parameters.GetInitialSeagrassDensity());
  ui->box_initial_sulfide_concentration->setValue(parameters.GetInitialSulfidedouble());
}

void ribi::mb::QtMutualismBreakdownerParametersWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}



void ribi::mb::QtMutualismBreakdownerParametersWidget::on_button_save_clicked()
{
  const std::string filename{
    QFileDialog::getSaveFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ofstream f(filename);
  f << GetParameters();
}

void ribi::mb::QtMutualismBreakdownerParametersWidget::on_button_load_clicked()
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
