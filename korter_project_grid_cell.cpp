#include "korter_project_grid_cell.h"

#include <cassert>
#include <iostream>
#include <sstream>

ribi::kp::grid_cell::grid_cell(
  const double trait,
  const double neutral)
  : m_trait{trait}, m_neutral{neutral}
{

}

bool ribi::kp::grid_cell::is_empty() const noexcept
{
  // Allow exact float point comparison,
  // because 'sm_empty' is a constant
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wfloat-equal"
  return m_trait == sm_empty;
  #pragma GCC diagnostic pop
}

bool ribi::kp::is_empty(const grid_cell& c) noexcept
{
  return c.is_empty();
}

bool ribi::kp::grid_cell::is_nurse() const noexcept
{
  // Allow exact float point comparison,
  // because 'sm_nurse' is a constant
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wfloat-equal"
  return m_trait == sm_nurse;
  #pragma GCC diagnostic pop
}

bool ribi::kp::is_nurse(const grid_cell& c) noexcept
{
  return c.is_nurse();
}

bool ribi::kp::grid_cell::is_seed() const noexcept
{
  return m_trait >= 0.0;
}

bool ribi::kp::is_seed(const grid_cell& c) noexcept
{
  return c.is_seed();
}

void ribi::kp::grid_cell::make_empty()
{
  m_trait = sm_empty;
  assert(is_empty());
}

void ribi::kp::grid_cell::make_nurse()
{
  m_trait = sm_nurse;
  assert(is_nurse());
}

void ribi::kp::grid_cell::make_seed(
  const double trait,
  const double neutral
)
{
  m_trait = trait;
  m_neutral = neutral;
  assert(is_seed());
  assert(!is_empty());
  assert(!is_nurse());
}

void ribi::kp::grid_cell::set_trait(const double trait)
{
  assert(trait >= 0.0);
  m_trait = trait;
  assert(!is_empty());
  assert(!is_nurse());
}

bool ribi::kp::operator==(const grid_cell& lhs, const grid_cell& rhs) noexcept
{
  // We really want an exact floating point comparison.
  // Traits are sometimes a constant, such as
  // 'sm_empty' and 'sm_nurse'
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wfloat-equal"
  return lhs.get_trait() == rhs.get_trait()
    && lhs.get_neutral() == rhs.get_neutral()
  ;
  #pragma GCC diagnostic pop
}

bool ribi::kp::operator!=(const grid_cell& lhs, const grid_cell& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::kp::operator<<(std::ostream& os, const grid_cell& parameter) noexcept
{
  os
    << parameter.get_trait() << " "
  ;
  return os;
}

std::istream& ribi::kp::operator>>(std::istream& is, grid_cell& parameter) noexcept
{
  is
    >> parameter.m_trait
  ;
  return is;
}
