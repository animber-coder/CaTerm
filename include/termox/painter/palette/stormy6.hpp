#ifndef CATERM_PAINTER_PALETTE_STORMY6_HPP
#define CATERM_PAINTER_PALETTE_STORMY6_HPP
#include <caterm/painter/color.hpp>

namespace ox::stormy6 {

constexpr auto Black  = Color::Background;
constexpr auto Green  = Color{2};
constexpr auto Teal   = Color{7};
constexpr auto Red    = Color{9};
constexpr auto Orange = Color{13};
constexpr auto White  = Color::Foreground;

/// Stormy 6 Color Palette
/** https://lospec.com/palette-list/stormy-6 */
inline auto const palette = Palette{
    /* clang-format off */
    {Black,  RGB{0x242828}},
    {Green,  RGB{0x7f9860}},
    {Teal,   RGB{0x3a5043}},
    {Red,    RGB{0xa95a3f}},
    {Orange, RGB{0xedbb70}},
    {White,  RGB{0xf8eebf}},
    /* clang-format on */
};

}  // namespace ox::stormy6
#endif  // CATERM_PAINTER_PALETTE_STORMY6_HPP
