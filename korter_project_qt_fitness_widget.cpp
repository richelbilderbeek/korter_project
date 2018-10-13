#include "korter_project_qt_fitness_widget.h"

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
  QObject::connect(ui->box_unfac_opt, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_unfac_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  OnAnyChange();
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
  plot();
  emit signal_parameters_changed();
}


void ribi::kp::qt_fitness_widget::plot()
{
  const auto params = to_parameters();
  const double max_trait{
    std::max(
      params.m_fac_opt + (params.m_fac_stddev * 3.0),
      params.m_unfac_opt + (params.m_unfac_stddev * 3.0)
    )
  };
  const int n_points{100};

  std::vector<double> xs;
  for (int i=0; i!=n_points; ++i)
  {
    xs.push_back(
      max_trait * static_cast<double>(i) / static_cast<double>(n_points)
    );
  }
  //Unfacilitated plant fitnesses
  std::vector<double> fitness_unfacs;
  for (int i=0; i!=n_points; ++i)
  {
    const double x{xs[i]};
    const double u_optimum = params.m_unfac_opt;
    const double u_sd = params.m_unfac_stddev;
    fitness_unfacs.push_back(normal(x, u_optimum, u_sd));
  }

  std::vector<double> fitness_facs;
  for (int i=0; i!=n_points; ++i)
  {
    const double x{xs[i]};
    const double f_optimum = params.m_fac_opt;
    const double f_sd = params.m_fac_stddev;
    fitness_facs.push_back(normal(x, f_optimum, f_sd));
  }
  m_curve_fac->setData(
    new QwtPointArrayData(&xs[0], &fitness_facs[0], fitness_facs.size())
  );
  m_curve_unfac->setData(
    new QwtPointArrayData(&xs[0], &fitness_unfacs[0], fitness_unfacs.size())
  );
  ui->fitness_plot->replot();
}
