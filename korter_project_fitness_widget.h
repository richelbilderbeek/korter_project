#ifndef KORTER_PROJECT_FITNESS_WIDGET_H
#define KORTER_PROJECT_FITNESS_WIDGET_H

#include <QWidget>

namespace Ui {
  class korter_project_fitness_widget;
}

namespace ribi {
namespace kp {

class fitness_widget : public QWidget
{
  Q_OBJECT

public:
  explicit fitness_widget(QWidget *parent = 0);
  ~fitness_widget();

signals:
  void signal_parameters_changed();

private:
  Ui::korter_project_fitness_widget *ui;
};

} //~namespace kp
} //~namespace ribi

#endif // KORTER_PROJECT_FITNESS_WIDGET_H
