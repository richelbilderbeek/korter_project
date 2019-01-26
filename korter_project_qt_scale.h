#ifndef KORTER_PROJECT_QT_SCALE_H
#define KORTER_PROJECT_QT_SCALE_H

#include <QWidget>

namespace Ui {
  class korter_project_qt_scale;
}

namespace ribi {
namespace kp {

class qt_scale : public QWidget
{
  Q_OBJECT

public:
  explicit qt_scale(QWidget *parent = 0);
  ~qt_scale();
  void set_min(const double min) noexcept;
  void set_max(const double max) noexcept;
  void set_text(const QString& text) noexcept;

private:
  Ui::korter_project_qt_scale *ui;
};

} //~namespace kp
} //~namespace ribi

#endif // KORTER_PROJECT_QT_SCALE_H
