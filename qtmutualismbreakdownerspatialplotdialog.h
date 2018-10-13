#ifndef QTKORTER_PROJECT_SPATIALPLOTDIALOG_H
#define QTKORTER_PROJECT_SPATIALPLOTDIALOG_H

#include <vector>

#include "korter_project_grid_cell.h"
#include "mutualismbreakdownerparameters.h"
#include "qthideandshowdialog.h"
#include "mutualismbreakdownerspatialsimulation.h"
struct QwtPlotCurve;

namespace Ui {
  class QtMutualismBreakdownerSpatialPlotDialog;
}

namespace ribi {
namespace kp {

struct SpatialSimulation;
struct QtMutualismBreakdownerParametersWidget;
struct QtMutualismBreakdownerSpatialWidget;

class QtMutualismBreakdownerSpatialPlotDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:


  explicit QtMutualismBreakdownerSpatialPlotDialog(QWidget *parent = 0);
  ~QtMutualismBreakdownerSpatialPlotDialog();
  Parameters GetParameters() const;
  void SetParameters(const Parameters& parameters);

private slots:

  void StartRun();
  void NextTimestep();

private:
  using Simulation = SpatialSimulation;

  Ui::QtMutualismBreakdownerSpatialPlotDialog *ui;
  QwtPlotCurve * const m_curve_sulfide_concentration;
  QtMutualismBreakdownerParametersWidget * const m_parameters_widget;
  QtMutualismBreakdownerSpatialWidget * const m_seagrass_widget;
  QTimer * const m_timer;
  std::unique_ptr<Simulation> m_simulation;
  void DisplayGrid();
};

} //~namespace mb
} //~namespace ribi

#endif // QTKORTER_PROJECT_SPATIALPLOTDIALOG_H
