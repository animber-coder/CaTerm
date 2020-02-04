#ifndef CPPURSES_WIDGET_DETAIL_BORDER_OFFSETS_HPP
#define CPPURSES_WIDGET_DETAIL_BORDER_OFFSETS_HPP
#include <cstddef>

namespace cppurses {
class Widget;
class Painter;
namespace detail {

/// Provides functions to calculate distance offsets of Borders.
/** Offsets are enabled depending on the Border object itself and from the
 *  current dimensions of the passed in Widget, which may be too small to
 *  display a Border. Offsets are interpreted as the space that a border will be
 *  taking from the Widget. */
class Border_offset {
    /// Calculate west border offset, either 1 or 0.
    static auto west(Widget const& w) -> std::size_t;

    /// Calculate east border offset, either 1 or 0.
    static auto east(Widget const& w) -> std::size_t;

    /// Calculate north border offset, either 1 or 0.
    static auto north(Widget const& w) -> std::size_t;

    /// Calculate south border offset, either 1 or 0.
    static auto south(Widget const& w) -> std::size_t;

    /// Calculate whether or not \p w is too small to display the west border.
    static auto west_disqualified(Widget const& w) -> bool;

    /// Calculate whether or not \p w is too small to display the east border.
    static auto east_disqualified(Widget const& w) -> bool;

    /// Calculate whether or not \p w is too small to display the north border.
    static auto north_disqualified(Widget const& w) -> bool;

    /// Calculate whether or not \p w is too small to display the south border.
    static auto south_disqualified(Widget const& w) -> bool;

    friend class cppurses::Widget;
    friend class cppurses::Painter;
};

}  // namespace detail
}  // namespace cppurses
#endif  // CPPURSES_WIDGET_DETAIL_BORDER_OFFSETS_HPP
