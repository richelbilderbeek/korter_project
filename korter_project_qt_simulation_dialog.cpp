#include "korter_project_qt_simulation_dialog.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QTimer>

#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "korter_project_qt_scale.h"
#include "korter_project_qt_parameters_widget.h"
#include "korter_project_qt_grid.h"
#include "korter_project_fitness_parameters.h"
#include "ui_korter_project_qt_simulation_dialog.h"
#include "korter_project_simulation.h"

ribi::kp::korter_project_qt_simulation_dialog::korter_project_qt_simulation_dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::korter_project_qt_simulation_dialog),
  m_parameters_widget{new korter_project_qt_parameters_widget},
  m_qt_grid{new korter_project_qt_grid(10,10)},
  m_qt_scale{new qt_scale},
  m_timer{new QTimer(this)},
  m_simulation{nullptr},
  m_surface_plot{new QtSurfacePlotWidget}
{
  ui->setupUi(this);

  {
    const auto my_layout = ui->widget_left->layout();
    assert(my_layout);
    my_layout->addWidget(m_parameters_widget);
  }
  {
    const auto my_layout = ui->widget_mid->layout();
    assert(my_layout);
    my_layout->addWidget(m_qt_grid);
  }
  {
    const auto my_layout = ui->widget_right->layout();
    assert(my_layout);
    my_layout->addWidget(m_surface_plot);
    my_layout->addWidget(m_qt_scale);
  }
  m_qt_grid->setToolTip(
    "<b>Shows the spatial situation:</b>"
    "<ul>"
    "  <li>Green: a nurse/facilitator plant</li>"
    "  <li>"
    "    Blue: a facilitated plant. "
    "    The brighter the color, the higher its fitness"
    "  </li>"
    "  <li>"
    "    Red: an unfacilitated plant. "
    "    The brighter the color, the higher its fitness"
    "  </li>"
    "</ul>"
  );

  //Setup surface plot
  {
    m_surface_plot->setMinimumWidth(100);
    std::vector<std::vector<double>> v(100, std::vector<double>(100, 0.0));
    for (int i = 0; i != 100; ++i)
    {
      for (int j = 0; j != 100; ++j)
      {
        v[i][j] = std::cos(6.28 * static_cast<double>(i) / 100.0)
          + std::sin(6.28 * static_cast<double>(j) / 100.0)
        ;
      }
    }
    m_surface_plot->SetSurfaceGrey(v);
    m_surface_plot->setToolTip(
      "<b>The trait value distribution through time</b>"
      "<ul>"
      "  <li>"
      "    <b>The vertical axis</b> shows "
      "    the trait value distribution through time, "
      "    starting at at the top and adding new trait value distributions "
      "    below"
      "  </li>"
      "  <li>"
      "    <b>The horizontal axis</b> "
      "    shows the trait value distribution, "
      "    where abundant trait values are displayed brighter. "
      "    Trait values range from zero at the left to their maximum range at "
      "    the right. The maximum range is determined by the parameters set by "
      "    the user in the 'Output' tab. The maximum range of traits "
      "    displayed equals the number of bins times the bin width. "
      "    Traits values higher than the maximum range are put in the "
      "    rightmost bin"
      "  </li>"
      "</ul>"
    );
  }
  //Setup scale
  {
    m_qt_scale->set_min(0.0);
    m_qt_scale->set_text("trait value");
  }

  QObject::connect(m_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(start_run()));
  QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(NextTimestep()));

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10,screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }
  start_run();
}

ribi::kp::korter_project_qt_simulation_dialog::~korter_project_qt_simulation_dialog()
{
  delete ui;
}

void ribi::kp::korter_project_qt_simulation_dialog::display_grid()
{
  const auto upper_trait = calc_upper_trait(
    m_simulation->get_parameters().get_fitness_parameters()
  );

  assert(m_simulation);
  const auto& grid = m_simulation->get_grid();
  const auto& cells = grid.get_cells();
  const int height{static_cast<int>(cells.size())};
  const int width{static_cast<int>(cells[0].size())};
  for (int y=0; y!=height; ++y)
  {
    const auto& line = cells[y];
    for (int x=0; x!=width; ++x)
    {
      const grid_cell& c = line[x];
      if (c.is_empty()) m_qt_grid->set_pixel(x, y, qRgb(0, 0, 0));
      else if (c.is_nurse()) m_qt_grid->set_pixel(x, y, qRgb(0, 255, 0));
      else
      {
        assert(c.is_seed());
        const auto trait = c.get_trait();
        int z = static_cast<int>(255.0 * trait / upper_trait);
        if (z < 0) z = 0;
        else if (z > 255) z = 255;
        if (is_facilitated(grid, x, y))
        {
          //Facilitated are blue
          m_qt_grid->set_pixel(x, y, qRgb(0, 0, z));
        }
        else
        {
          //Unfacilitated are red
          m_qt_grid->set_pixel(x, y, qRgb(z, 0, 0));
        }
      }
    }
  }
  m_qt_grid->update();
}

void ribi::kp::korter_project_qt_simulation_dialog::display_traits()
{
  const auto& histograms = m_simulation->get_trait_histograms();
  m_surface_plot->SetSurfaceGrey(histograms);
}

ribi::kp::parameters ribi::kp::korter_project_qt_simulation_dialog::to_parameters() const
{
  assert(m_parameters_widget);
  return m_parameters_widget->to_parameters();
}

void ribi::kp::korter_project_qt_simulation_dialog::NextTimestep()
{
  const int current_generation
    = this->m_simulation->get_trait_histograms().size();
  const int max_n_generations = to_parameters().get_max_n_generations();
  if (current_generation == max_n_generations)
  {
    std::ofstream f(to_parameters().get_results_filename());
    // Display parameters properly
    {
      const parameters params = to_parameters();
      const fitness_parameters& fitness_params = params.get_fitness_parameters();
      f
        << "# fitness_params.get_fac_max: " << fitness_params.get_fac_max() << '\n'
        << "# fitness_params.get_fac_opt: " << fitness_params.get_fac_opt() << '\n'
        << "# fitness_params.get_fac_stddev: " << fitness_params.get_fac_stddev() << '\n'
        << "# fitness_params.get_unfac_max: " << fitness_params.get_unfac_max() << '\n'
        << "# fitness_params.get_unfac_opt: " << fitness_params.get_unfac_opt() << '\n'
        << "# fitness_params.get_unfac_stddev: " << fitness_params.get_unfac_stddev() << '\n'
        << "# init_trait_mean: " << params.get_init_trait_mean() << '\n'
        << "# init_trait_stddev: " << params.get_init_trait_stddev() << '\n'
        << "# max_n_generations: " << params.get_max_n_generations() << '\n'
        << "# mut_stddev: " << params.get_mut_stddev() << '\n'
        << "# n_nurse_plants: " << params.get_n_nurse_plants() << '\n'
        << "# n_seeds: " << params.get_n_seeds() << '\n'
        << "# n_trait_histogram_bins: " << params.get_n_trait_histogram_bins() << '\n'
        << "# results_filename: " << params.get_results_filename() << '\n'
        << "# rng_seed: " << params.get_rng_seed() << '\n'
        << "# spatial_height: " << params.get_spatial_height() << '\n'
        << "# spatial_height: " << params.get_spatial_height() << '\n'
        << "# trait_histogram_bin_width: " << params.get_trait_histogram_bin_width() << '\n'
      ;
    }
    const auto& histograms =  m_simulation->get_trait_histograms();
    for (const auto& histogram: histograms)
    {
      std::stringstream s;
      std::copy(std::begin(histogram), std::end(histogram),
      std::ostream_iterator<double>(s, ","));
      std::string t = s.str();
      t.back() = '\n'; //Replace comma by newline
      f << t;
    }
  }
  if (current_generation > max_n_generations) return;


  assert(m_simulation);
  m_simulation->go_to_next_generation();
  display_grid();
  display_traits();
}

void ribi::kp::korter_project_qt_simulation_dialog::resizeEvent(QResizeEvent *)
{
  const int w{this->width()};
  ui->widget_left->setMaximumWidth(w / 3);
  ui->widget_mid->setMaximumWidth(w / 3);
}

void ribi::kp::korter_project_qt_simulation_dialog::set_parameters(const parameters& parameters)
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

void ribi::kp::korter_project_qt_simulation_dialog::start_run()
{
  m_timer->stop();
  m_qt_grid->setEnabled(false);
  try
  {
    to_parameters();
  }
  catch (std::exception& e)
  {
    QString title = "Korter Project (" + QString(e.what()) + ")";
    this->setWindowTitle(title);
    return;
  }
  this->setWindowTitle("Korter Project");

  const auto parameters = to_parameters();

  m_qt_scale->set_max(
    static_cast<double>(parameters.get_n_trait_histogram_bins()) *
    parameters.get_trait_histogram_bin_width()
  );
  {
    const int w{parameters.get_spatial_width()};
    const int h{parameters.get_spatial_height()};
    this->m_qt_grid->set_size(w, h);
  }
  this->m_qt_grid->setEnabled(true);

  m_simulation.reset(new simulation(parameters));
  this->m_parameters_widget->show_frac_fac(
    calc_frac_fac_seeds(m_simulation->get_grid())
  );
  display_grid();
  display_traits();

  m_timer->setInterval(1);
  m_timer->start();

}
