#include <cppurses/system/events/key.hpp>

#include <cstdint>

#include <cppurses/system/focus.hpp>
#include <cppurses/widget/widget.hpp>

namespace {
/// Translate a keycode \p key into its char representation.
/** Return '\0' if \p key does not have a printable representation. */
auto key_to_char(cppurses::Key::Code key) -> char
{
    constexpr auto alpha_low  = std::int16_t{32};
    constexpr auto alpha_high = std::int16_t{126};
    const auto value          = static_cast<std::int16_t>(key);
    if (value < alpha_low || value > alpha_high)
        return '\0';
    return static_cast<char>(value);
}

}  // namespace

// This file is needed, including widget.hpp in the header will create a cycle.
namespace cppurses {

auto Key::Press::send() const -> bool
{
    bool r = receiver_.key_press_event(Key::State{key_, key_to_char(key_)});
    if (key_ == Code::Tab && Focus::tab_press())
        return true;
    if (key_ == Code::Back_tab && Focus::shift_tab_press())
        return true;
    return r;
}

auto Key::Press::filter_send(Widget& filter) const -> bool
{
    return filter.key_press_event_filter(receiver_,
                                         Key::State{key_, key_to_char(key_)});
}

auto Key::Release::send() const -> bool
{
    return receiver_.key_release_event(Key::State{key_, key_to_char(key_)});
}

auto Key::Release::filter_send(Widget& filter) const -> bool
{
    return filter.key_release_event_filter(receiver_,
                                           Key::State{key_, key_to_char(key_)});
}

}  // namespace cppurses
