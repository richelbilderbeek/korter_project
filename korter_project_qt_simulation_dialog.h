#ifndef QTKORTER_PROJECT_SPATIALPLOTDIALOG_H
#define QTKORTER_PROJECT_SPATIALPLOTDIALOG_H

#include <vector>

#include "korter_project_grid_cell.h"
#include "korter_project_parameters.h"
#include "qthideandshowdialog.h"
#include "korter_project_simulation.h"
#include "qtsurfaceplotwidget.h"

struct QwtPlotCurve;

namespace Ui {
  class korter_project_qt_simulation_dialog;
}

namespace ribi {

class QtSurfacePlotWidget;

namespace kp {

struct simulation;
struct qt_scale;
struct korter_project_qt_parameters_widget;
struct korter_project_qt_grid;

///The main dialog showing the parameters, simulation and
///results
class korter_project_qt_simulation_dialog : public QDialog
{
  Q_OBJECT
  
public:


  explicit korter_project_qt_simulation_dialog(QWidget *parent = 0);
  ~korter_project_qt_simulation_dialog();
  parameters to_parameters() const;
  void set_parameters(const parameters& parameters);

private slots:

  void start_run();
  void NextTimestep();
  void resizeEvent(QResizeEvent *);

private:
  Ui::korter_project_qt_simulation_dialog *ui;
  korter_project_qt_parameters_widget * const m_parameters_widget;
  korter_project_qt_grid * const m_qt_grid;
  qt_scale * const m_qt_scale;
  QTimer * const m_timer;
  std::unique_ptr<simulation> m_simulation;

  ///Shows the histogram of the neutral markers in time
  QtSurfacePlotWidget * const m_neutrals_in_time_plot;

  ///Shows the histogram of the traits in time
  QtSurfacePlotWidget * const m_traits_in_time_plot;


  ///Display the grid of plants
  void display_grid();

  ///Display the neutral markers' values in time
  void display_neutrals();

  ///Display the plant traits in time
  void display_traits();
};

} //~namespace mb
} //~namespace ribi

#endif // QTKORTER_PROJECT_SPATIALPLOTDIALOG_H
