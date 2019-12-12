#ifndef CPPURSES_DEMOS_PALETTE_COLOR_CONTROL_HPP
#define CPPURSES_DEMOS_PALETTE_COLOR_CONTROL_HPP
#include <signals/signal.hpp>

#include <cppurses/widget/layouts/horizontal.hpp>

#include "value_control.hpp"

namespace palette {

/// Holds Value_control objects for red, green, and blue color values.
class Color_control : public cppurses::layout::Horizontal<Value_control> {
    Value_control& slider_red_{this->make_child("R")};
    Value_control& slider_green_{this->make_child("G")};
    Value_control& slider_blue_{this->make_child("B")};

   public:
    Color_control();

    /// Set the red slider to a specific value.
    void set_red_slider(int value) { slider_red_.set_value(value); }

    /// Set the green slider to a specific value.
    void set_green_slider(int value) { slider_green_.set_value(value); }

    /// Set the blue slider to a specific value.
    void set_blue_slider(int value) { slider_blue_.set_value(value); }

    /// Set all sliders to the respective RGB color value.
    void set_sliders(cppurses::Color color);

    sig::Signal<void(int)>& red_changed{slider_red_.value_changed};
    sig::Signal<void(int)>& green_changed{slider_green_.value_changed};
    sig::Signal<void(int)>& blue_changed{slider_blue_.value_changed};
};

}  // namespace palette
#endif  // CPPURSES_DEMOS_PALETTE_COLOR_CONTROL_HPP
