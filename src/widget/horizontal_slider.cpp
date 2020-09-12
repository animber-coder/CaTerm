#include <cppurses/widget/widgets/horizontal_slider.hpp>

#include <cmath>
#include <cstddef>

#include <signals/signals.hpp>

#include <cppurses/system/key.hpp>
#include <cppurses/system/mouse.hpp>
#include <cppurses/widget/detail/tracks_lifetime.hpp>

namespace cppurses {

void Horizontal_slider::set_percent(float percent)
{
    if (percent < 0.0)
        percent_progress_ = 0.0;
    else if (percent > 1.0)
        percent_progress_ = 1.0;
    else
        percent_progress_ = percent;
    percent_changed(percent_progress_);
    this->update();
}

auto Horizontal_slider::mouse_press_event(Mouse const& m) -> bool
{
    if (m.button == Mouse::Button::Left)
        this->set_percent(position_to_percent(m.local.x));
    return Widget::mouse_press_event(m);
}

auto Horizontal_slider::mouse_wheel_event(Mouse const& m) -> bool
{
    switch (m.button) {
        case Mouse::Button::ScrollUp: scrolled_up(); break;
        case Mouse::Button::ScrollDown: scrolled_down(); break;
        default: break;
    }
    return Widget::mouse_wheel_event(m);
}

auto Horizontal_slider::key_press_event(Key k) -> bool
{
    auto const current_position = percent_to_position(percent_progress_);
    switch (k) {
        case Key::Arrow_right:
            this->set_percent(position_to_percent(current_position + 1));
            break;
        case Key::Arrow_left:
            if (current_position != 0)
                this->set_percent(position_to_percent(current_position - 1));
            break;
        default: break;
    }
    return Widget::key_press_event(k);
}

auto Horizontal_slider::position_to_percent(std::size_t position) -> float
{
    auto const width = this->width();
    if (width < 2)
        return 0.f;
    if (position >= (width - 1))
        return 1.f;
    return static_cast<float>(position) / static_cast<float>(width - 1);
}

auto Horizontal_slider::percent_to_position(float percent) -> std::size_t
{
    auto const width = this->width();
    return width == 0 ? 0 : std::round(percent * static_cast<float>(width - 1));
}

namespace slot {
using namespace detail;

auto set_percent(Horizontal_slider& s) -> sig::Slot<void(float)>
{
    return tracks_lifetime(s, [&s](float percent) { s.set_percent(percent); });
}

auto set_percent(Horizontal_slider& s, float percent) -> sig::Slot<void()>
{
    return tracks_lifetime(s, [&s, percent] { s.set_percent(percent); });
}

}  // namespace slot
}  // namespace cppurses
