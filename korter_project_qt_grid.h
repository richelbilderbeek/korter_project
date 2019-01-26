#ifndef QTKORTER_PROJECT_SPATIALWIDGET_H
#define QTKORTER_PROJECT_SPATIALWIDGET_H

#include <QWidget>
#include <QImage>

namespace Ui {
  class korter_project_qt_grid;
}

struct QImage;

namespace ribi {
namespace kp {

///The visual representation of a spatial grid,
///allowing to set and get pixels.
class korter_project_qt_grid : public QWidget
{
  Q_OBJECT

public:
  explicit korter_project_qt_grid(
    const int width = 600,
    const int height = 400,
    QWidget *parent = 0
  );
  korter_project_qt_grid(const korter_project_qt_grid&) = delete;
  korter_project_qt_grid& operator=(const korter_project_qt_grid&) = delete;
  ~korter_project_qt_grid();

  void set_pixel(const int x, const int y, const QColor color);
  void set_size(const int width, const int height);

protected:
  void paintEvent(QPaintEvent *);
private:
  Ui::korter_project_qt_grid *ui;
  QImage m_image;
};

} //~namespace mb
} //~namespace ribi

#endif // QTKORTER_PROJECT_SPATIALWIDGET_H
