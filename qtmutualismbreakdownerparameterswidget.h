#ifndef QTKORTER_PROJECT_PARAMETERSWIDGET_H
#define QTKORTER_PROJECT_PARAMETERSWIDGET_H

#include "mutualismbreakdownerparameters.h"
#include <QWidget>


namespace Ui {
  class QtMutualismBreakdownerParametersWidget;
}

namespace ribi {
namespace kp {

class fitness_widget;

class QtMutualismBreakdownerParametersWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtMutualismBreakdownerParametersWidget(QWidget *parent = 0);
  ~QtMutualismBreakdownerParametersWidget();
  Parameters GetParameters() const;
  void SetParameters(const Parameters& parameters);

signals:
  void signal_parameters_changed() const;


private slots:

  void OnAnyChange();

  void on_button_load_clicked();
  void on_button_save_clicked();

private:
  fitness_widget * const m_fitness_widget;
  Ui::QtMutualismBreakdownerParametersWidget *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace mb
} //~namespace ribi

#endif // QTKORTER_PROJECT_PARAMETERSWIDGET_H
