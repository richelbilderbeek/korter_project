#ifndef QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H
#define QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H

#include "mutualismbreakdownerparameters.h"
#include <QWidget>


namespace Ui {
  class QtMutualismBreakdownerParametersWidget;
}

namespace ribi {
namespace mb {

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
  Ui::QtMutualismBreakdownerParametersWidget *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace mb
} //~namespace ribi

#endif // QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H
