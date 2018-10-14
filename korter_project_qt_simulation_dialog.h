#ifndef QTKORTER_PROJECT_SPATIALPLOTDIALOG_H
#define QTKORTER_PROJECT_SPATIALPLOTDIALOG_H

#include <vector>

#include "korter_project_grid_cell.h"
#include "korter_project_parameters.h"
#include "qthideandshowdialog.h"
#include "korter_project_simulation.h"
struct QwtPlotCurve;

namespace Ui {
  class korter_project_qt_simulation_dialog;
}

namespace ribi {
namespace kp {

struct simulation;
struct korter_project_qt_parameters_widget;
struct korter_project_qt_grid;

class korter_project_qt_simulation_dialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:


  explicit korter_project_qt_simulation_dialog(QWidget *parent = 0);
  ~korter_project_qt_simulation_dialog();
  parameters to_parameters() const;
  void SetParameters(const parameters& parameters);

private slots:

  void StartRun();
  void NextTimestep();

private:
  Ui::korter_project_qt_simulation_dialog *ui;
  QwtPlotCurve * const m_curve_sulfide_concentration;
  korter_project_qt_parameters_widget * const m_parameters_widget;
  korter_project_qt_grid * const m_seagrass_widget;
  QTimer * const m_timer;
  std::unique_ptr<simulation> m_simulation;
  void DisplayGrid();
};

} //~namespace mb
} //~namespace ribi

#endif // QTKORTER_PROJECT_SPATIALPLOTDIALOG_H
