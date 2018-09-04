#ifndef CPPURSES_SYSTEM_DETAIL_FIND_WIDGET_AT_HPP
#define CPPURSES_SYSTEM_DETAIL_FIND_WIDGET_AT_HPP
#include <cstddef>

namespace cppurses {
class Widget;
namespace detail {

/// Returns the Widget* that owns the global coordinates (x, y).
/** Returns nullptr on failing to find a Widget with the provided coordinates.
 *  Returns the deepest child Widget that owns the coordinates. If a parent owns
 *  the coordinates, it is check if any of the childen own it as well before
 *  returning. Used only by NCurses_paint_engine at the moment. */
Widget* find_widget_at(std::size_t x, std::size_t y);

}  // namespace detail
}  // namespace cppurses
#endif  // CPPURSES_SYSTEM_DETAIL_FIND_WIDGET_AT_HPP
