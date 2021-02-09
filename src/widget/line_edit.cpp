#include <caterm/widget/widgets/line_edit.hpp>

#include <cctype>
#include <functional>
#include <utility>
#include <vector>

#include <caterm/painter/color.hpp>
#include <caterm/painter/glyph.hpp>
#include <caterm/painter/glyph_string.hpp>
#include <caterm/painter/trait.hpp>
#include <caterm/system/key.hpp>
#include <caterm/widget/point.hpp>
#include <caterm/widget/widgets/textbox.hpp>

namespace ox {

void Line_edit::underline(bool enabled)
{
    if (enabled) {
        this->set_wallpaper(U' ' | Trait::Underline);
        this->set_contents(this->contents() | Trait::Underline);
        this->insert_brush.traits.insert(Trait::Underline);
    }
    else {
        this->set_wallpaper(U' ');
        auto non_underlined = this->contents();
        non_underlined.remove_traits(Trait::Underline);
        this->set_contents(std::move(non_underlined));
        this->insert_brush.traits.remove(Trait::Underline);
    }
    this->update();
}

void Line_edit::set_ghost_color(Color c)
{
    if (not on_initial_)
        return;
    this->set_contents(this->contents() | fg(c));
    this->update();
}

auto Line_edit::key_press_event(Key k) -> bool
{
    switch (k) {
        case Key::Enter:
            edit_finished(this->contents().str());
            if (clear_on_enter_)
                this->clear();
            if (on_initial_)
                on_initial_ = false;
            return true;
        case Key::Arrow_up:
        case Key::Arrow_down: return true;
        default: break;
    }
    auto const is_printable = [](char c) {
        return std::isprint(c) or std::isspace(c);
    };
    auto const symbol = key_to_char32(k);
    if (!is_printable(symbol))
        return Textbox::key_press_event(k);
    if (!validator_(symbol))
        return true;
    if (symbol != U'\0' && on_initial_) {  // First alpha-num input
        this->clear();
        on_initial_ = false;
    }
    return Textbox::key_press_event(k);
}

}  // namespace ox
