#ifndef CATERM_PAINTER_DETAIL_IS_PAINTABLE_HPP
#define CATERM_PAINTER_DETAIL_IS_PAINTABLE_HPP
#include <caterm/widget/widget.hpp>

namespace ox::detail {

/// A check for whether a widget is in a state that can be painted.
inline auto is_paintable(Widget const& w) -> bool
{
    return w.is_enabled() && (w.outer_width() != 0) && (w.outer_height() != 0);
}

}  // namespace ox::detail
#endif  // CATERM_PAINTER_DETAIL_IS_PAINTABLE_HPP
