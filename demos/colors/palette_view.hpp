#ifndef CATERM_DEMOS_COLORS_COLORS_DISPLAY_HPP
#define CATERM_DEMOS_COLORS_COLORS_DISPLAY_HPP
#include <utility>

#include <signals_light/signal.hpp>

#include <caterm/painter/color.hpp>
#include <caterm/painter/glyph_string.hpp>
#include <caterm/painter/palette/amstrad_cpc.hpp>
#include <caterm/painter/palette/apple_ii.hpp>
#include <caterm/painter/palette/ashes.hpp>
#include <caterm/painter/palette/basic.hpp>
#include <caterm/painter/palette/basic8.hpp>
#include <caterm/painter/palette/cga.hpp>
#include <caterm/painter/palette/commodore_64.hpp>
#include <caterm/painter/palette/commodore_vic20.hpp>
#include <caterm/painter/palette/dawn_bringer16.hpp>
#include <caterm/painter/palette/dawn_bringer32.hpp>
#include <caterm/painter/palette/en4.hpp>
#include <caterm/painter/palette/gameboy.hpp>
#include <caterm/painter/palette/gameboy_pocket.hpp>
#include <caterm/painter/palette/macintosh_ii.hpp>
#include <caterm/painter/palette/msx.hpp>
#include <caterm/painter/palette/nes.hpp>
#include <caterm/painter/palette/savanna.hpp>
#include <caterm/painter/palette/secam.hpp>
#include <caterm/painter/palette/stormy6.hpp>
#include <caterm/painter/palette/teletext.hpp>
#include <caterm/painter/palette/thomson_m05.hpp>
#include <caterm/painter/palette/windows.hpp>
#include <caterm/painter/palette/windows_console.hpp>
#include <caterm/painter/palette/zx_spectrum.hpp>
#include <caterm/system/system.hpp>
#include <caterm/terminal/terminal.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/widgets/color_select.hpp>
#include <caterm/widget/widgets/cycle_box.hpp>

namespace colors {

class Palette_picker : public ox::Labeled_cycle_box {
   public:
    sl::Signal<void(ox::Palette)> palette_picked;

   public:
    Palette_picker() : Labeled_cycle_box{"Palette"}
    {
        using namespace ox;
        this->append_option(L"Dawn Bringer 16", dawn_bringer16::palette);
        this->append_option(L"Dawn Bringer 32", dawn_bringer32::palette);
        this->append_option(L"Basic 16", basic::palette);
        this->append_option(L"Basic 8", basic8::palette);
        this->append_option(L"EN 4", en4::palette);
        this->append_option(L"Stormy 6", stormy6::palette);
        this->append_option(L"Teletext", teletext::palette);
        this->append_option(L"Gameboy", gameboy::palette);
        this->append_option(L"Gameboy Pocket", gameboy_pocket::palette);
        this->append_option(L"NES", nes::palette);
        this->append_option(L"CGA", cga::palette);
        this->append_option(L"Amstrad CPC", amstrad_cpc::palette);
        this->append_option(L"Early MSFT Windows", windows::palette);
        this->append_option(L"Apple II", apple_ii::palette);
        this->append_option(L"Macintosh II", macintosh_ii::palette);
        this->append_option(L"MSX", msx::palette);
        this->append_option(L"ZX Spectrum", zx_spectrum::palette);
        this->append_option(L"Thomson M05", thomson_m05::palette);
        this->append_option(L"SECAM", secam::palette);
        this->append_option(L"Commodore VIC-20", commodore_vic20::palette);
        this->append_option(L"Commodore 64", commodore_64::palette);
        this->append_option(L"Windows Console", windows_console::palette);
        this->append_option(L"Atelier Savanna", savanna::palette);
        this->append_option(L"Ashes", ashes::palette);
    }

   private:
    /// Adds an entry to the cycle box for the given palette with \p title.
    void append_option(ox::Glyph_string title, ox::Palette const& pal)
    {
        this->cycle_box.add_option(std::move(title)).connect([this, pal]() {
            palette_picked(pal);
        });
    }
};

class Palette_demo : public ox::layout::Vertical<> {
   public:
    ox::Color_select& palette_view = this->make_child<ox::Color_select>(true);
    Palette_picker& palette_picker = this->make_child<Palette_picker>();

   public:
    Palette_demo()
    {
        using namespace ox::pipe;
        *this | strong_focus();
        palette_picker.palette_picked.connect(
            [](auto const& pal) { ox::System::terminal.set_palette(pal); });
    }
};

}  // namespace colors
#endif  // CATERM_DEMOS_COLORS_COLORS_DISPLAY_HPP
