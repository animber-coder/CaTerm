#ifndef DEMOS_GLYPH_PAINT_SIDE_PANE_HPP
#define DEMOS_GLYPH_PAINT_SIDE_PANE_HPP
#include <caterm/painter/color.hpp>
#include <caterm/painter/glyph.hpp>
#include <caterm/painter/trait.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/widgets/color_select.hpp>
#include <caterm/widget/widgets/cycle_stack.hpp>
#include <caterm/widget/widgets/label.hpp>
#include <caterm/widget/widgets/text_display.hpp>

#include "glyph_selector.hpp"
#include "options_box.hpp"
#include "trait_box.hpp"

namespace paint {

class Side_pane : public ox::layout::Vertical<> {
   private:
    class Color_pages : public ox::Cycle_stack<ox::Color_select> {
       public:
        ox::Color_select& foreground =
            make_page(U"Foreground" | ox::Trait::Bold);
        ox::Color_select& background =
            make_page(U"Background" | ox::Trait::Bold);

       public:
        Color_pages()
        {
            ox::Terminal::palette_changed.connect([this](auto const& pal) {
                *this | ox::pipe::fixed_height(std::ceil(pal.size() / 8.) + 1);
            });
        }
    };

   public:
    Side_pane()
    {
        using namespace ox::pipe;

        *this | fixed_width(16);
        space1 | wallpaper(U'─');
        space2 | wallpaper(U'─');
        glyph_selector | preferred_height(6);
        show_glyph | fixed_height(1) | align_center();
    }

   public:
    Glyph_selector& glyph_selector = append_child(populated_glyph_selector());
    Widget& space1                 = make_child() | ox::pipe::fixed_height(1);
    Color_pages& color_pages       = make_child<Color_pages>();
    Trait_box& trait_box           = make_child<Trait_box>();
    ox::HLabel& show_glyph         = make_child<ox::HLabel>(U"x");
    Widget& space2                 = make_child() | ox::pipe::fixed_height(1);
    Options_stack& options_box     = make_child<Options_stack>();
};

}  // namespace paint
#endif  // DEMOS_GLYPH_PAINT_SIDE_PANE_HPP
