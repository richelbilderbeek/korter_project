#ifndef KORTER_PROJECT_PARAMETERS_H
#define KORTER_PROJECT_PARAMETERS_H

#include <iosfwd>
#include <memory>

#include "korter_project_fitness_parameters.h"

namespace ribi {
namespace kp {

struct parameters
{
  explicit parameters(
    const fitness_parameters& fp = fitness_parameters(),
    const double init_trait_mean = 0.5,
    const double init_trait_stddev = 0.1,
    const double mut_stddev = 0.01,
    const int spatial_height = 1,
    const int spatial_width = 1,
    const int n_nurse_plants = 0,
    const int n_seeds = 0,
    const int n_trait_histogram_bins = 10,
    const int rng_seed = 0,
    const double trait_histogram_bin_width = 0.1,
    const int max_n_generations = 1000,
    const std::string& results_filename = "results.csv",
    const double init_neutral_mean = 0.5,
    const double init_neutral_stddev = 0.1
  );

  const auto& get_fitness_parameters() const noexcept { return m_fitness_parameters; }
  double get_init_neutral_mean() const noexcept { return m_init_neutral_mean; }
  double get_init_neutral_stddev() const noexcept { return m_init_neutral_stddev; }
  double get_init_trait_mean() const noexcept { return m_init_trait_mean; }
  double get_init_trait_stddev() const noexcept { return m_init_trait_stddev; }

  ///The standard deviation of the mutation
  double get_mut_stddev() const noexcept { return m_mut_stddev; }

  int get_spatial_height() const noexcept { return m_spatial_height; }
  int get_spatial_width() const noexcept { return m_spatial_width; }
  int get_n_nurse_plants() const noexcept { return m_n_nurse_plants; }
  int get_n_seeds() const noexcept { return m_n_seeds; }
  int get_rng_seed() const noexcept { return m_rng_seed; }
  int get_n_trait_histogram_bins() const noexcept { return m_n_trait_histogram_bins; }
  double get_trait_histogram_bin_width() const noexcept { return m_trait_histogram_bin_width; }

  int get_max_n_generations() const noexcept { return m_max_n_generations; }

  const std::string& get_results_filename() const noexcept { return m_results_filename; }

  void set_init_neutral_mean(const double mean);
  void set_init_neutral_stddev(const double stddev);
  void set_init_trait_mean(const double mean);
  void set_init_trait_stddev(const double stddev);

  void set_n_nurse_plants(const int n_nurse_plants);
  void set_n_seeds(const int n_seeds);

  void set_spatial_height(const int height);
  void set_spatial_width(const int width);

  /// Does the user want to use the testing grid,
  /// as created by 'create_test_grid'?
  /// Assumes the width is already set to 4
  /// Assumes the height is already set to 3
  void set_use_test_grid(const bool use_test_grid = true);

  /// Does the user want to use the testing grid,
  /// as created by 'create_test_grid'?
  bool use_test_grid() const noexcept { return m_use_test_grid; }

  private:
  const fitness_parameters m_fitness_parameters;

  double m_init_trait_mean;
  double m_init_trait_stddev;
  double m_mut_stddev;

  int m_spatial_height;
  int m_spatial_width;

  int m_n_nurse_plants;
  int m_n_seeds;
  int m_n_trait_histogram_bins;
  int m_rng_seed;
  double m_trait_histogram_bin_width;
  int m_max_n_generations;
  std::string m_results_filename;

  ///If true, the testing grid is used,
  ///as can be created by 'create_test_grid'
  bool m_use_test_grid = false;

  double m_init_neutral_mean;
  double m_init_neutral_stddev;

  friend std::ostream& operator<<(std::ostream& os, const parameters& parameter) noexcept;
  friend std::istream& operator>>(std::istream& is, parameters& parameter) noexcept;
  friend bool operator==(const parameters& lhs, const parameters& rhs) noexcept;
};

/// Create the parameters to use a testing grid
parameters create_test_parameters() noexcept;

bool operator==(const parameters& lhs, const parameters& rhs) noexcept;
bool operator!=(const parameters& lhs, const parameters& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const parameters& parameter) noexcept;
std::istream& operator>>(std::istream& is, parameters& parameter) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // KORTER_PROJECT_PARAMETERS_H
