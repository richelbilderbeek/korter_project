#ifndef QTKORTER_PROJECT_PARAMETERSWIDGET_H
#define QTKORTER_PROJECT_PARAMETERSWIDGET_H

#include "korter_project_parameters.h"
#include <QWidget>


namespace Ui {
  class QtMutualismBreakdownerParametersWidget;
}

namespace ribi {
namespace kp {

class qt_fitness_widget;

class QtMutualismBreakdownerParametersWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtMutualismBreakdownerParametersWidget(QWidget *parent = 0);
  ~QtMutualismBreakdownerParametersWidget();
  parameters to_parameters() const;
  void SetParameters(const parameters& parameters);

signals:
  void signal_parameters_changed() const;


private slots:

  void OnAnyChange();

  void on_button_load_clicked();
  void on_button_save_clicked();

private:
  qt_fitness_widget * const m_fitness_widget;
  Ui::QtMutualismBreakdownerParametersWidget *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace mb
} //~namespace ribi

#endif // QTKORTER_PROJECT_PARAMETERSWIDGET_H
