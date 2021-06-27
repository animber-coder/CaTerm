#ifndef CATERM_PAINTER_PALETTE_EN4_HPP
#define CATERM_PAINTER_PALETTE_EN4_HPP
#include <caterm/painter/color.hpp>

namespace ox::en4 {

constexpr auto Blue  = Color::Background;
constexpr auto Peach = Color{5};
constexpr auto Green = Color{2};
constexpr auto White = Color::Foreground;

/// EN 4 Color Palette
/** https://lospec.com/palette-list/en4 */
inline auto const palette = Palette{
    /* clang-format off */
    {Blue,  RGB{0x20283d}},
    {Peach, RGB{0xe5b083}},
    {Green, RGB{0x426e5d}},
    {White, RGB{0xfbf7f3}},
    /* clang-format on */
};

}  // namespace ox::en4
#endif  // CATERM_PAINTER_PALETTE_EN4_HPP
