#include <caterm/widget/widgets/cycle_box.hpp>

#include <cstddef>

#include <caterm/painter/glyph_string.hpp>
#include <caterm/system/mouse.hpp>
#include <caterm/widget/widgets/text_view.hpp>

namespace {

/// \p edge is one-past-the-last element, will go to zero instead of \p edge
/** Input Constraints: \p edge > 0  and \p i < \p edge */
auto wrapped_increment(std::size_t i, std::size_t edge) -> std::size_t
{
    return ++i == edge ? 0 : i;
}

/// \p edge is one-past-the-last element, will go to edge - 1 instead of -1.
/** Input Constraints: \p edge > 0  and \p i < \p edge */
auto wrapped_decrement(std::size_t i, std::size_t edge) -> std::size_t
{
    return i == 0 ? --edge : --i;
}

}  // namespace

namespace ox {

void Cycle_box::next()
{
    if (this->size() < 2)
        return;
    this->set_current_option(wrapped_increment(index_, this->size()));
    this->emit_signals();
}

void Cycle_box::previous()
{
    if (this->size() < 2)
        return;
    this->set_current_option(wrapped_decrement(index_, this->size()));
    this->emit_signals();
}

}  // namespace ox
