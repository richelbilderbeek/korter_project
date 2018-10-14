#include "korter_project_qt_simulation_dialog.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>

#include <QDesktopWidget>
#include <QGridLayout>
#include <QTimer>

#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "korter_project_qt_parameters_widget.h"
#include "qtmutualismbreakdownerspatialwidget.h"
#include "ui_korter_project_qt_simulation_dialog.h"
#include "korter_project_simulation.h"

ribi::kp::korter_project_qt_simulation_dialog::korter_project_qt_simulation_dialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::korter_project_qt_simulation_dialog),
  m_curve_sulfide_concentration(new QwtPlotCurve),
  m_parameters_widget{new korter_project_qt_parameters_widget},
  m_seagrass_widget{new QtMutualismBreakdownerSpatialWidget(10,10)},
  m_timer{new QTimer(this)},
  m_simulation{nullptr}
{
  ui->setupUi(this);

  {
    const auto my_layout = ui->widget_left->layout();
    assert(my_layout);
    my_layout->addWidget(m_parameters_widget);
    //m_parameters_widget->HideTimeplot();
  }
  {
    const auto my_layout = ui->widget_mid->layout();
    assert(my_layout);
    my_layout->addWidget(m_seagrass_widget);
  }
  {
    ui->plot_sulfide_concentration->setMaximumWidth(400);
    m_curve_sulfide_concentration->attach(ui->plot_sulfide_concentration);
    m_curve_sulfide_concentration->setStyle(QwtPlotCurve::Lines);
    m_curve_sulfide_concentration->setPen(QPen(QColor(255,0,0)));
  }

  QObject::connect(m_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(StartRun()));
  QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(NextTimestep()));

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10,screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }
  StartRun();
}

ribi::kp::korter_project_qt_simulation_dialog::~korter_project_qt_simulation_dialog()
{
  delete ui;
}

void ribi::kp::korter_project_qt_simulation_dialog::DisplayGrid()
{
  const auto k = 10.0;
  const auto max_s = 1.0;

  assert(m_simulation);
  const auto grid = m_simulation->GetGrid();
  const int height{static_cast<int>(grid.size())};
  const int width{static_cast<int>(grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    const auto& line = grid[y];
    for (int x=0; x!=width; ++x)
    {
      const auto& cell = line[x];
      //Seagrass
      {
        const auto n = cell.GetSeagrassDensity();
        int g = static_cast<int>(255.0 * n / k);
        if (g < 0) g = 0;
        else if (g > 255) g = 255;
        m_seagrass_widget->SetPixel(x,y,qRgb(0,g,0));
      }
      //Sulfide
      {
        const auto s = cell.GetSulfidedouble();
        int r = static_cast<int>(255.0 * s / max_s);
        if (r < 0) r = 0;
        else if (r > 255) r = 255;
        //m_sulfide_widget->SetPixel(x,y,qRgb(r,0,0));
      }
    }
  }
  m_seagrass_widget->update();
  //m_sulfide_widget->update();
}

ribi::kp::parameters ribi::kp::korter_project_qt_simulation_dialog::to_parameters() const
{
  assert(m_parameters_widget);
  return m_parameters_widget->to_parameters();
}

void ribi::kp::korter_project_qt_simulation_dialog::NextTimestep()
{
  const auto parameters = to_parameters();
  const auto dt = 0.1; //STUB
  assert(m_simulation);
  m_simulation->Change(dt);

  //Kill some random patch
  {
    const int w = parameters.get_spatial_width();
    const int h = parameters.get_spatial_height();
    m_simulation->KillSeagrass(
      std::rand() % w,
      std::rand() % h
    );
  }

  DisplayGrid();
}

void ribi::kp::korter_project_qt_simulation_dialog::SetParameters(const parameters& parameters)
{
  try
  {
    assert(m_parameters_widget);
    m_parameters_widget->set(parameters);
  }
  catch(std::logic_error& e)
  {
    std::clog << e.what() << std::endl;
  }
}

void ribi::kp::korter_project_qt_simulation_dialog::StartRun()
{
  m_timer->stop();
  m_seagrass_widget->setEnabled(false);
  try
  {
    to_parameters();
  }
  catch (std::logic_error& e)
  {
    std::clog << e.what() << std::endl;
    return;
  }

  const auto parameters = to_parameters();
  {
    const int w{parameters.get_spatial_width()};
    const int h{parameters.get_spatial_height()};
    this->m_seagrass_widget->SetResolution(w,h);
    //this->m_sulfide_widget->SetResolution(w,h);
  }
  this->m_seagrass_widget->setEnabled(true);
  //this->m_sulfide_widget->setEnabled(true);

  //m_simulation = std::make_unique<Simulation>(parameters);
  m_simulation.reset(new simulation(parameters));

  DisplayGrid();

  m_timer->setInterval(1);
  m_timer->start();

}
