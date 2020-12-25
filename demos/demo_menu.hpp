#ifndef DEMOS_DEMO_MENU_HPP
#define DEMOS_DEMO_MENU_HPP
#include <caterm/painter/detail/screen_descriptor.hpp>
#include <caterm/painter/palette/dawn_bringer16.hpp>
#include <caterm/system/key.hpp>
#include <caterm/system/shortcuts.hpp>
#include <caterm/system/system.hpp>
#include <caterm/widget/focus_policy.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/widgets/menu_stack.hpp>
#include <caterm/widget/widgets/titlebar.hpp>

#include "animation/animation_demo.hpp"
#include "colors/palette_view.hpp"
#include "composites/composites.hpp"
#include "focus/focus_demo.hpp"
#include "game_of_life/gol_demo.hpp"
#include "glyph_paint/glyph_paint.hpp"
#include "graph/graph_demo.hpp"
#include "layout/layout_demo.hpp"
#include "notepad/notepad.hpp"
#include "palette/palette_demo.hpp"
#include "snake/snake.hpp"

namespace demos {

class Demo_menu : public ox::Menu_stack {
   public:
    Demo_menu() : Menu_stack{L"Demos"}
    {
        using namespace ox;
        using namespace ox::pipe;

        Shortcuts::add_shortcut(Key::Escape).connect([this] {
            System::terminal.set_palette(ox::dawn_bringer16::palette);
            this->Menu_stack::goto_menu();
        });

        this->make_page<comp::Idea>(L"Idea");
        this->make_page<snake::Snake_game>(L"Snake Game");

        // clang-format off
        this->append_page(L"Composites",
            layout::vertical
            (
                checkbox(),
                checkbox(),
                textbox(L"WOW!") | bg(Color::Green) | Trait::Bold,
                layout::horizontal
                (
                    textbox(L"Left") | bg(Color::Light_blue),
                    textbox(L"Right") | bg(Color::Violet)
                ),
                checkbox(),
                hcheckbox_label({L"A Box"})
            )
        );
        // clang-format on

        this->make_page<Notepad>(L"Notepad");
        this->append_page(L"Focus", focus::build_demo());
        this->append_page(L"Animated Widget", animation::build_demo());

        this->make_page<graph::Graph_demo>(L"Graph");
        this->make_page<gol::GoL_demo>(L"Game of Life");
        this->make_page<paint::Glyph_paint>(L"Glyph Paint");

        this->make_page<colors::Palette_demo>(L"Color Palettes");
        this->make_page<palette::Palette_demo>(L"Color Palette");

        this->make_page<layout_demo::Layout_demo>(L"Layouts");
        this->make_page<comp::Two_lists>(L"Check Lists");
    }
};

class Demos : public ox::layout::Vertical<> {
   public:
    // TODO add a back button to left side of titlebar that appears in demos
    using Titlebar = ox::Titlebar;

    Titlebar& title_ = this->make_child<Titlebar>("~ CaTerm ~");
    Demo_menu& menu  = this->make_child<Demo_menu>();

   public:
    Demos() { this->focus_policy = ox::Focus_policy::Direct; }

   protected:
    auto focus_in_event() -> bool override
    {
        ox::System::set_focus(menu);
        return true;
    }
};

}  // namespace demos
#endif  // DEMOS_DEMO_MENU_HPP
