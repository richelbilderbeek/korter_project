#ifndef QTKORTER_PROJECT_PARAMETERSWIDGET_H
#define QTKORTER_PROJECT_PARAMETERSWIDGET_H

#include "korter_project_parameters.h"
#include <QWidget>


namespace Ui {
  class korter_project_qt_parameters_widget;
}

namespace ribi {
namespace kp {

class qt_fitness_widget;

///The widget in which the user can set parameters
class korter_project_qt_parameters_widget : public QWidget
{
  Q_OBJECT

public:
  explicit korter_project_qt_parameters_widget(QWidget *parent = 0);
  ~korter_project_qt_parameters_widget();
  parameters to_parameters() const;
  void set(const parameters& parameters);

  ///Show the fraction of the facilitated cells in the realized grid.
  ///This fraction goes from 0.0 (no nurse plants) to 1.0 (all grid cells
  ///are connected to a nurse plant)
  void show_frac_fac(const double f_fac);

signals:
  void signal_parameters_changed() const;


private slots:

  void OnAnyChange();

  void on_button_load_clicked();
  void on_button_save_clicked();

  void on_button_save_results_clicked();

private:
  qt_fitness_widget * const m_fitness_widget;
  Ui::korter_project_qt_parameters_widget *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace mb
} //~namespace ribi

#endif // QTKORTER_PROJECT_PARAMETERSWIDGET_H
