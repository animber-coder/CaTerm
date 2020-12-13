#ifndef CPPURSES_PAINTER_PALETTE_EN4_HPP
#define CPPURSES_PAINTER_PALETTE_EN4_HPP
#include <cppurses/painter/color.hpp>

namespace cppurses::en4 {

constexpr auto Blue  = Color::Background;
constexpr auto Peach = Color{5};
constexpr auto Green = Color{2};
constexpr auto White = Color::Foreground;

/// EN 4 Color Palette
/** https://lospec.com/palette-list/en4 */
inline auto const palette = Palette{
    /* clang-format off */
    {Blue,  ANSI{16}, 0x20283d},
    {Peach, ANSI{17}, 0xe5b083},
    {Green, ANSI{18}, 0x426e5d},
    {White, ANSI{19}, 0xfbf7f3},
    /* clang-format on */
};

}  // namespace cppurses::en4
#endif  // CPPURSES_PAINTER_PALETTE_EN4_HPP
