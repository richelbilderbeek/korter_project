#include "korter_project_qt_grid.h"

#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "ui_korter_project_qt_grid.h"

ribi::kp::korter_project_qt_grid::korter_project_qt_grid(
  const int width,
  const int height,
  QWidget *parent
)
  : QWidget(parent),
    ui(new Ui::korter_project_qt_grid),
    m_image(width,height,QImage::Format_RGB32)
{
  ui->setupUi(this);
}

ribi::kp::korter_project_qt_grid::~korter_project_qt_grid()
{
  delete ui;
}

void ribi::kp::korter_project_qt_grid::set_pixel(const int x, const int y, const QColor color)
{
  m_image.setPixel(x,y,color.rgb());
}

void ribi::kp::korter_project_qt_grid::set_size(const int width, const int height)
{
  m_image = QImage(width, height, QImage::Format_RGB32);
}

void ribi::kp::korter_project_qt_grid::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(
    this->rect(),
    QPixmap::fromImage(m_image)
  );
}
