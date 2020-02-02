#ifndef KORTER_PROJECT_GRID_CELL_H
#define KORTER_PROJECT_GRID_CELL_H

#include "korter_project_parameters.h"

namespace ribi {
namespace kp {

struct grid_cell
{
  ///A grid cell is empty by default
  grid_cell(
    const double trait = sm_empty,
    const double neutral = 0.0
  );

  bool is_empty() const noexcept;
  bool is_nurse() const noexcept;
  bool is_seed() const noexcept;
  void make_empty();
  void make_nurse();

  /// Make the grid cell contain a seed,
  /// with a trait of 0.5 and a neutral marker of 0.0
  void make_seed(
    const double trait = 0.5,
    const double neutral = 0.0
  );

  ///Get the trait that has a fitness effect.
  ///If the value is lower than zero, this grid cell is
  ///either empty or a nurse plant.
  double get_trait() const noexcept { return m_trait; }

  ///Get the neutral marker; the trait that has no fitness effect.
  double get_neutral() const noexcept { return m_neutral; }

  ///Set the trait that has a fitness effect.
  ///This value must be zero or higher.
  ///To make a grid cell empty or become a nurse plant,
  ///use 'make_empty' or 'make_nurse'
  void set_trait(const double trait);

  private:

  static constexpr double sm_empty{-12.34};
  static constexpr double sm_nurse{-23.45};

  /// A trait that is under selection:
  /// * 0.0 or bigger if occupied
  /// * Equal to 'sm_empty' if empty
  /// * Equal to 'sm_nurse' if nurse
  double m_trait;

  /// A neutral marker, a trait that is not under selection
  double m_neutral;

  friend std::ostream& operator<<(std::ostream& os, const grid_cell& g) noexcept;
  friend std::istream& operator>>(std::istream& is, grid_cell& g) noexcept;
};

///Is the grid cell empty?
bool is_empty(const grid_cell& c) noexcept;

///Is the grid cell a nurse plant?
bool is_nurse(const grid_cell& c) noexcept;

///Is the grid cell a seed/non-nurse plant?
bool is_seed(const grid_cell& c) noexcept;

bool operator==(const grid_cell& lhs, const grid_cell& rhs) noexcept;
bool operator!=(const grid_cell& lhs, const grid_cell& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const grid_cell& g) noexcept;
std::istream& operator>>(std::istream& is, grid_cell& g) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // KORTER_PROJECT_GRID_CELL_H
