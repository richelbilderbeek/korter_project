#include "korter_project_qt_fitness_widget.h"

#include <cassert>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

#include "ui_korter_project_qt_fitness_widget.h"

ribi::kp::qt_fitness_widget::qt_fitness_widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::korter_project_qt_fitness_widget),
  m_curve_fac(new QwtPlotCurve),
  m_curve_unfac(new QwtPlotCurve)
{
  ui->setupUi(this);
  m_curve_fac->attach(ui->fitness_plot);
  m_curve_fac->setStyle(QwtPlotCurve::Lines);
  m_curve_fac->setPen(QPen(QColor(0,255,0), 2));
  m_curve_unfac->attach(ui->fitness_plot);
  m_curve_unfac->setStyle(QwtPlotCurve::Lines);
  m_curve_unfac->setPen(QPen(QColor(255, 0, 0), 2));

  QObject::connect(ui->box_fac_opt, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_fac_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_fac_max, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_unfac_opt, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_unfac_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_unfac_max, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  OnAnyChange();
}

ribi::kp::qt_fitness_widget::~qt_fitness_widget()
{
  delete ui;
}

void ribi::kp::qt_fitness_widget::set(const fitness_parameters& p) noexcept
{
  ui->box_fac_opt->setValue(p.get_fac_opt());
  ui->box_fac_stddev->setValue(p.get_fac_stddev());
  ui->box_fac_max->setValue(p.get_fac_max());
  ui->box_unfac_opt->setValue(p.get_unfac_opt());
  ui->box_unfac_stddev->setValue(p.get_unfac_stddev());
  ui->box_unfac_max->setValue(p.get_unfac_max());
  assert(to_parameters() == p);
}

ribi::kp::fitness_parameters ribi::kp::qt_fitness_widget::to_parameters() const noexcept
{
  const fitness_parameters p(
    ui->box_fac_opt->value(),
    ui->box_fac_stddev->value(),
    ui->box_fac_max->value(),
    ui->box_unfac_opt->value(),
    ui->box_unfac_stddev->value(),
    ui->box_unfac_max->value()
  );
  assert(abs(p.get_fac_opt() - ui->box_fac_opt->value()) < 0.0001);
  assert(abs(p.get_fac_stddev() - ui->box_fac_stddev->value()) < 0.0001);
  assert(abs(p.get_fac_max() - ui->box_fac_max->value()) < 0.0001);
  assert(abs(p.get_unfac_opt() - ui->box_unfac_opt->value()) < 0.0001);
  assert(abs(p.get_unfac_stddev() - ui->box_unfac_stddev->value()) < 0.0001);
  assert(abs(p.get_unfac_max() - ui->box_unfac_max->value()) < 0.0001);
  return p;
}

void ribi::kp::qt_fitness_widget::OnAnyChange()
{
  plot();
  emit signal_parameters_changed();
}


void ribi::kp::qt_fitness_widget::plot()
{
  const auto params = to_parameters();
  const double upper_trait{
    calc_upper_trait(params)
  };
  const int n_points{100};

  std::vector<double> xs;
  for (int i=0; i!=n_points; ++i)
  {
    xs.push_back(
      upper_trait * static_cast<double>(i) / static_cast<double>(n_points)
    );
  }
  //Unfacilitated plant fitnesses
  std::vector<double> fitness_unfacs;
  for (int i=0; i!=n_points; ++i)
  {
    const double x{xs[i]};
    const double u_optimum = params.get_unfac_opt();
    const double u_sd = params.get_unfac_stddev();
    const double u_max = params.get_unfac_max();
    fitness_unfacs.push_back(u_max * normal(x, u_optimum, u_sd));
  }

  std::vector<double> fitness_facs;
  for (int i=0; i!=n_points; ++i)
  {
    const double x{xs[i]};
    const double f_optimum = params.get_fac_opt();
    const double f_sd = params.get_fac_stddev();
    const double f_max = params.get_fac_max();
    fitness_facs.push_back(f_max * normal(x, f_optimum, f_sd));
  }
  m_curve_fac->setData(
    new QwtPointArrayData(&xs[0], &fitness_facs[0], fitness_facs.size())
  );
  m_curve_unfac->setData(
    new QwtPointArrayData(&xs[0], &fitness_unfacs[0], fitness_unfacs.size())
  );
  ui->fitness_plot->replot();
}
