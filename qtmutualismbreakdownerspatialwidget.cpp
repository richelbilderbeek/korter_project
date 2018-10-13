#include "qtmutualismbreakdownerspatialwidget.h"

#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "ui_qtmutualismbreakdownerspatialwidget.h"

ribi::kp::QtMutualismBreakdownerSpatialWidget::QtMutualismBreakdownerSpatialWidget(
  const int width,
  const int height,
  QWidget *parent
)
  : QWidget(parent),
    ui(new Ui::QtMutualismBreakdownerSpatialWidget),
    m_image(width,height,QImage::Format_RGB32)
{
  ui->setupUi(this);
}

ribi::kp::QtMutualismBreakdownerSpatialWidget::~QtMutualismBreakdownerSpatialWidget()
{
  delete ui;
}

void ribi::kp::QtMutualismBreakdownerSpatialWidget::SetPixel(const int x, const int y, const QColor color)
{
  m_image.setPixel(x,y,color.rgb());
}

void ribi::kp::QtMutualismBreakdownerSpatialWidget::SetResolution(const int width, const int height)
{
  m_image = QImage(width,height,QImage::Format_RGB32);
}

void ribi::kp::QtMutualismBreakdownerSpatialWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(
    this->rect(),
    QPixmap::fromImage(m_image)
  );
}
