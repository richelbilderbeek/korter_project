#include "korter_project_qt_parameters_widget.h"

#include <cassert>
#include <fstream>
#include <QFileDialog>

#include "korter_project_qt_fitness_widget.h"
#include "ui_korter_project_qt_parameters_widget.h"


ribi::kp::korter_project_qt_parameters_widget::korter_project_qt_parameters_widget(QWidget *parent) :
  QWidget(parent),
  m_fitness_widget(new qt_fitness_widget),
  ui(new Ui::korter_project_qt_parameters_widget)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  {
    using Layout = QGridLayout;
    Layout * const my_layout{
      dynamic_cast<Layout*>(ui->page_fitness->layout())
    };
    assert(my_layout);
    my_layout->addWidget(m_fitness_widget);
  }

  ui->button_save_results->setText("results.csv");



  QObject::connect(m_fitness_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_spatial_height,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_spatial_width,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_n_nurse_plants,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_n_seeds,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_n_trait_histogram_bins,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_rng_seed,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_init_trait_mean, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_init_trait_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_mut_stddev, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_trait_histogram_bin_width, SIGNAL(valueChanged(double)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->box_max_n_generations, SIGNAL(valueChanged(int)), this, SLOT(OnAnyChange()));
  QObject::connect(ui->button_save_results, SIGNAL(clicked(bool)), this, SLOT(OnAnyChange()));
  OnAnyChange();
}

ribi::kp::korter_project_qt_parameters_widget::~korter_project_qt_parameters_widget()
{
  delete ui;
}

void ribi::kp::korter_project_qt_parameters_widget::show_frac_fac(const double f_fac)
{
  ui->label_percentage_facilitated_value->setText(
    QString::number(f_fac * 100.0)
  );
}

ribi::kp::parameters ribi::kp::korter_project_qt_parameters_widget::to_parameters() const
{
  const parameters p(
    m_fitness_widget->to_parameters(),
    ui->box_init_trait_mean->value(),
    ui->box_init_trait_stddev->value(),
    ui->box_mut_stddev->value(),
    ui->box_spatial_height->value(),
    ui->box_spatial_width->value(),
    ui->box_n_nurse_plants->value(),
    ui->box_n_seeds->value(),
    ui->box_n_trait_histogram_bins->value(),
    ui->box_rng_seed->value(),
    ui->box_trait_histogram_bin_width->value(),
    ui->box_max_n_generations->value(),
    ui->button_save_results->text().toStdString()
  );

  return p;
}

void ribi::kp::korter_project_qt_parameters_widget::set(const parameters& p)
{
  m_fitness_widget->set(p.get_fitness_parameters());
  ui->box_init_trait_mean->setValue(p.get_init_trait_mean());
  ui->box_init_trait_stddev->setValue(p.get_init_trait_stddev());
  ui->box_mut_stddev->setValue(p.get_mut_stddev());
  ui->box_n_nurse_plants->setValue(p.get_n_nurse_plants());
  ui->box_n_seeds->setValue(p.get_n_seeds());
  ui->box_n_trait_histogram_bins->setValue(p.get_n_trait_histogram_bins()),
  ui->box_rng_seed->setValue(p.get_rng_seed());
  ui->box_spatial_height->setValue(p.get_spatial_height());
  ui->box_spatial_width->setValue(p.get_spatial_width());
  ui->box_trait_histogram_bin_width->setValue(p.get_trait_histogram_bin_width());
  ui->box_max_n_generations->setValue(p.get_max_n_generations());
  ui->button_save_results->setText(QString::fromStdString(p.get_results_filename()));
}

void ribi::kp::korter_project_qt_parameters_widget::OnAnyChange()
{
  ui->box_n_nurse_plants->setMaximum(
    ui->box_spatial_width->value() * ui->box_spatial_height->value()
  );
  {
    QString r_code =
      QString("<code>")
      + "filename &lt;- \""
      + ui->button_save_results->text()
      + "\"<br>"
      + "</code>"
      + "<code>"
      + "df_result &lt;- read.csv(filename, comment.char = \"#\")</br>"
      + "</code>"
    ;
    ui->button_save_results->setToolTip(r_code);
    ui->label_save_results->setToolTip(r_code);
  }

  emit signal_parameters_changed();
}

void ribi::kp::korter_project_qt_parameters_widget::on_button_save_clicked()
{
  const std::string filename{
    QFileDialog::getSaveFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ofstream f(filename);
  f << to_parameters();
}

void ribi::kp::korter_project_qt_parameters_widget::on_button_load_clicked()
{
  const std::string filename{
    QFileDialog::getOpenFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ifstream f(filename);
  parameters parameters;
  f >> parameters;
  set(parameters);
}

void ribi::kp::korter_project_qt_parameters_widget::on_button_save_results_clicked()
{
  const std::string filename = QFileDialog::getSaveFileName().toStdString();
  if (filename.empty()) return;
  ui->button_save_results->setText(QString::fromStdString(filename));
}
