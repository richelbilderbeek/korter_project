#include "korter_project_grid.h"

#include <algorithm>
#include <cassert>
#include <iostream>

ribi::kp::grid::grid(
  const int width,
  const int height
) : m_cells(height, std::vector<grid_cell>(width))
{
  assert(height == get_height());
  assert(width == get_width());
  assert(static_cast<int>(m_cells.size()) == get_height());
  assert(static_cast<int>(m_cells[0].size()) == get_width());
}

ribi::kp::grid ribi::kp::add_seeds(
  grid g,
  const std::vector<double>& traits,
  std::mt19937& rng_engine
)
{
  const int n_seeds = static_cast<int>(traits.size());
  assert(n_seeds <= count_n_empty(g));
  const int width{g.get_width()};
  const int height{g.get_height()};
  //Put nurse plants into position
  std::uniform_int_distribution<int> width_distr(0, width - 1);
  std::uniform_int_distribution<int> height_distr(0, height - 1);
  for (int i = 0; i != n_seeds; ++i)
  {
    const double trait{traits[i]};
    const int x{width_distr(rng_engine)};
    const int y{height_distr(rng_engine)};
    assert(x >= 0);
    assert(x < g.get_width());
    assert(y >= 0);
    assert(y < g.get_height());
    if (g.get(x, y).is_empty())
    {
      g.get(x, y).set_trait(trait);
    }
    else
    {
      --i;
    }
  }
  return g;
}

double ribi::kp::calc_frac_fac_seeds(const grid& g)
{
  const int n_fac{count_n_facilitated_seeds(g)};
  const int n_unfac{count_n_unfacilitated_seeds(g)};
  assert(n_fac + n_unfac > 0);
  return static_cast<double>(n_fac) / static_cast<double>(n_fac + n_unfac);
}

std::vector<bool> ribi::kp::collect_is_facilitated(const grid& g)
{
  std::vector<bool> v;
  const int height{g.get_height()};
  const int width{g.get_width()};
  std::vector<double> t;
  for (int y = 0; y != height; ++y)
  {
    for (int x = 0; x != width; ++x)
    {
      if (is_seed(g, x, y))
      {
        v.push_back(is_facilitated(g, x, y));
      }
    }
  }
  return v;
}

std::vector<double> ribi::kp::collect_traits(const grid& g)
{
  std::vector<double> t;
  for (const auto& row: g.get_cells())
  {
    for (const grid_cell& cell: row)
    {
      if (cell.is_seed()) {
        t.push_back(cell.get_trait());
      }
    }
  }
  return t;
}

int ribi::kp::count_n_empty(const grid& g) noexcept
{
  int n{0};
  for (const auto& row: g.get_cells())
  {
    n += std::count_if(
      std::begin(row),
      std::end(row),
      [](const grid_cell& c) { return is_empty(c); }
    );
  }
  return n;
}

int ribi::kp::count_n_facilitated_seeds(const grid& g) noexcept
{
  using namespace std;

  const int height{g.get_height()};
  const int width{g.get_width()};
  int n_fac{0};
  for (int y = 0; y != height; ++y)
  {
    for (int x = 0; x != width; ++x)
    {
      if (!is_empty(g, x, y)
        && !is_nurse(g, x, y)
        && is_facilitated(g, x, y)
      )
      {
        ++n_fac;
      }
    }
  }
  return n_fac;
}

int ribi::kp::count_n_nurse(const grid& g) noexcept
{
  int n{0};
  for (const auto& row: g.get_cells())
  {
    n += std::count_if(
      std::begin(row),
      std::end(row),
      [](const grid_cell& c) { return is_nurse(c); }
    );
  }
  return n;
}

int ribi::kp::count_n_seeds(const grid& g) noexcept
{
  int n{0};
  for (const auto& row: g.get_cells())
  {
    n += std::count_if(
      std::begin(row),
      std::end(row),
      [](const grid_cell& c) { return is_seed(c); }
    );
  }
  return n;
}

int ribi::kp::count_n_unfacilitated_seeds(const grid& g) noexcept
{
  using namespace std;
  const int height{g.get_height()};
  const int width{g.get_width()};
  int n_unfac{0};

  for (int y = 0; y != height; ++y)
  {
    for (int x = 0; x != width; ++x)
    {
      if (!is_empty(g, x, y)
        && !is_nurse(g, x, y)
        && is_unfacilitated(g, x, y)
      )
      {
        ++n_unfac;
      }
    }
  }
  return n_unfac;
}

ribi::kp::grid ribi::kp::create_next_grid(
  grid g,
  const std::vector<double>& traits,
  std::mt19937& rng_engine
)
{
  remove_seeds(g);
  return add_seeds(g, traits, rng_engine);
}

ribi::kp::grid ribi::kp::create_test_grid() noexcept
{
  // |0123|
  //-|----+---
  //0|....|0
  //1|.N.U|1
  //2|.F..|2
  //-|----+---
  // |0123|
  //
  // N: Nurse plant
  // F: Facilitated plant/seed, because adjacent to nurse
  //    trait value 0.75
  //    neutral marker value 0.9
  // U: Unfacilitated plant/seed, because not adjacent to nurse
  //    trait value 0.25
  //    neutral marker value 0.1
  const int width{4};
  const int height{3};
  grid g(width, height);
  g.get(1, 1).make_nurse(); // N
  g.get(3, 1).make_seed(0.25, 0.1); // U
  g.get(1, 2).make_seed(0.75, 0.9); // F
  return g;
}

std::vector<int> ribi::kp::create_trait_histogram(
  const grid& g,
  const int n_bins,
  const double bin_width
)
{
  assert(g.get_height() > 0);
  assert(g.get_width() > 0);
  assert(n_bins > 0);
  assert(bin_width > 0.0);
  const std::vector<double> traits = collect_traits(g);
  std::vector<int> histogram(n_bins, 0);
  for (const double trait: traits)
  {
    const int index = trait / bin_width;
    assert(index >= 0);
    if (index < n_bins) { ++histogram[index]; }
    else { ++histogram.back(); }
  }
  return histogram;
}

const ribi::kp::grid_cell& ribi::kp::grid::get(const int x, const int y) const
{
  assert(x >= 0);
  assert(y >= 0);
  assert(y < get_height());
  assert(x < get_width());
  return m_cells[y][x];
}

ribi::kp::grid_cell& ribi::kp::grid::get(const int x, const int y)
{
  assert(x >= 0);
  assert(y >= 0);
  assert(y < get_height());
  assert(x < get_width());
  return m_cells[y][x];
}

int ribi::kp::grid::get_width() const
{
  assert(!m_cells.empty());
  return m_cells[0].size();
}

bool ribi::kp::is_empty(const ribi::kp::grid& g) noexcept
{
  const auto& h = g.get_cells();
  for (const auto& row: h)
  {
    for (const auto& c: row)
    {
      if (!c.is_empty()) return false;
    }
  }
  return true;
}

bool ribi::kp::is_empty(const grid& g, const int x, const int y)
{
  return g.get(x, y).is_empty();
}

bool ribi::kp::is_facilitated(const grid& g, const int x, const int y)
{
  assert(!g.get(x, y).is_nurse());
  const int h{g.get_height()};
  const int w{g.get_width()};
  return
       g.get((x - 1 + w) %  w, y).is_nurse()
    || g.get((x + 1 + w) %  w, y).is_nurse()
    || g.get(x, (y - 1 + h) % h).is_nurse()
    || g.get(x, (y + 1 + h) % h).is_nurse()
  ;
}

bool ribi::kp::is_nurse(const grid& g, const int x, const int y)
{
  return g.get(x, y).is_nurse();
}

bool ribi::kp::is_seed(const grid& g, const int x, const int y)
{
  return g.get(x, y).is_seed();
}

bool ribi::kp::is_unfacilitated(const grid& g, const int x, const int y)
{
  assert(!g.get(x, y).is_nurse());
  return !is_facilitated(g, x, y);
}

void ribi::kp::remove_seeds(grid& g)
{
  for (auto& row: g.get_cells())
  {
    for (auto& cell: row)
    {
      if (cell.is_seed()) {
        cell.make_empty();
      }
    }
  }
}

std::ostream& ribi::kp::operator<<(std::ostream& os, const grid& g) noexcept
{
  //Number of rows
  os << g.m_cells.size() << " ";

  //Per row ...
  for (const auto& row: g.m_cells)
  {
    //Number of elements
    os << row.size() << " ";
    //Per element
    for (const auto& element: row)
    {
      os << element << " ";
    }
  }
  return os;
}

std::istream& ribi::kp::operator>>(std::istream& is, grid& g) noexcept
{
  //Number of rows
  int n_rows{-1};
  is >> n_rows;
  std::vector<std::vector<grid_cell>> cells;
  cells.reserve(n_rows);

  //Per row
  for (int row_index = 0; row_index != n_rows; ++row_index)
  {
    //Number of elements
    int n_elements{-1};
    is >> n_elements;
    std::vector<grid_cell> row;
    row.reserve(n_elements);

    for (int i = 0; i != n_elements; ++i)
    {
      grid_cell element;
      is >> element;
      row.push_back(element);
    }
    cells.push_back(row);
  }
  g.m_cells = cells;
  return is;
}

bool ribi::kp::operator==(const grid& lhs, const grid& rhs) noexcept
{
  return
    lhs.get_cells() == rhs.get_cells()
  ;

}

bool ribi::kp::operator!=(const grid& lhs, const grid& rhs) noexcept
{
  return !(lhs == rhs);
}
