#ifndef CATERM_PAINTER_PALETTE_DAWN_BRINGER16_HPP
#define CATERM_PAINTER_PALETTE_DAWN_BRINGER16_HPP
#include <caterm/painter/color.hpp>

namespace ox::dawn_bringer16 {

constexpr auto Black       = Color::Background;
constexpr auto Dark_red    = Color{1};
constexpr auto Green       = Color{2};
constexpr auto Brown       = Color{3};
constexpr auto Dark_blue   = Color{4};
constexpr auto Violet      = Color{5};
constexpr auto Light_blue  = Color{6};
constexpr auto Light_gray  = Color{7};
constexpr auto Dark_gray   = Color{8};
constexpr auto Red         = Color{9};
constexpr auto Light_green = Color{10};
constexpr auto Yellow      = Color{11};
constexpr auto Blue        = Color{12};
constexpr auto Orange      = Color{13};
constexpr auto Gray        = Color{14};
constexpr auto White       = Color::Foreground;

/// Dawn Bringer 16 Color Palette
/** https://lospec.com/palette-list/dawnbringer-16 */
inline auto const palette = Palette{
    /* clang-format off */
    {Black,       RGB{0x140c1c}},
    {Dark_red,    RGB{0x442434}},
    {Green,       RGB{0x346524}},
    {Brown,       RGB{0x854c30}},
    {Dark_blue,   RGB{0x30346d}},
    {Violet,      RGB{0xd2aa99}},
    {Light_blue,  RGB{0x6dc2ca}},
    {Light_gray,  RGB{0x8595a1}},
    {Dark_gray,   RGB{0x4e4a4e}},
    {Red,         RGB{0xd04648}},
    {Light_green, RGB{0x6daa2c}},
    {Yellow,      RGB{0xdad45e}},
    {Blue,        RGB{0x597dce}},
    {Orange,      RGB{0xd27d2c}},
    {Gray,        RGB{0x757161}},
    {White,       RGB{0xdeeed6}},
    /* clang-format on */
};

}  // namespace ox::dawn_bringer16
#endif  // CATERM_PAINTER_PALETTE_DAWN_BRINGER16_HPP
