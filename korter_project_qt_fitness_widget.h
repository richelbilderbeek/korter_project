#ifndef KORTER_PROJECT_FITNESS_WIDGET_H
#define KORTER_PROJECT_FITNESS_WIDGET_H

#include "korter_project_fitness_parameters.h"
#include <QWidget>

class QwtPlotCurve;

namespace Ui {
  class korter_project_qt_fitness_widget;
}

namespace ribi {
namespace kp {

class qt_fitness_widget : public QWidget
{
  Q_OBJECT

public:
  explicit qt_fitness_widget(QWidget *parent = 0);
  ~qt_fitness_widget();
  fitness_parameters to_parameters() const noexcept;

signals:
  void signal_parameters_changed();

private slots:

  void OnAnyChange();

private:
  Ui::korter_project_qt_fitness_widget *ui;

  QwtPlotCurve * const m_curve_fac;
  QwtPlotCurve * const m_curve_unfac;

  void plot();
};

} //~namespace kp
} //~namespace ribi

#endif // KORTER_PROJECT_FITNESS_WIDGET_H
