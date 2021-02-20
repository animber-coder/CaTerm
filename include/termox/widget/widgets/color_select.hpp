#ifndef CATERM_WIDGET_WIDGETS_COLOR_SELECT_HPP
#define CATERM_WIDGET_WIDGETS_COLOR_SELECT_HPP
#include <memory>
#include <string>
#include <utility>

#include <signals_light/signal.hpp>

#include <caterm/painter/color.hpp>
#include <caterm/painter/glyph_string.hpp>
#include <caterm/painter/painter.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/widgets/button.hpp>

namespace ox {

class Color_tile : public Button {
   public:
    Color_tile(Color c, bool display_number)
        : color_{std::to_string(c.value) | fg(Color::Foreground)},
          number_{display_number}
    {
        using namespace ox::pipe;
        *this | bg(c) | fg(Color::Foreground);
    }

   protected:
    auto paint_event(Painter& p) -> bool override
    {
        if (number_)
            p.put(color_, {0, 0});
        return Button::paint_event(p);
    }

   private:
    Glyph_string color_;
    bool number_;
};

using Color_line = layout::Horizontal<Color_tile>;

/// Displays each color of the current palette.
/** Updates when Terminal::set_pallete() succeeds. */
class Color_select : public layout::Vertical<Color_line> {
   public:
    sl::Signal<void(Color)> color_selected;

   public:
    explicit Color_select(bool display_numbers = false)
        : numbers_{display_numbers}
    {
        this->set_palette(Terminal::current_palette());
        Terminal::palette_changed.connect(
            [this](auto const& pal) { this->set_palette(pal); });
    }

   private:
    void set_palette(Palette const& pal)
    {
        this->delete_all_children();
        auto const size           = pal.size();
        auto constexpr row_length = 8uL;
        auto count                = 0uL;

        while (count != size) {
            auto& color_line = this->make_child();
            for (auto i = 0uL; i < row_length && count != size; ++i, ++count) {
                using namespace ox::pipe;
                auto const color = pal[count].color;
                color_line.make_child(color, numbers_) |
                    on_press([this, color]() { color_selected(color); });
            }
        }
    }

   private:
    bool numbers_;
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto color_select(Args&&... args) -> std::unique_ptr<Color_select>
{
    return std::make_unique<Color_select>(std::forward<Args>(args)...);
}

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_COLOR_SELECT_HPP
