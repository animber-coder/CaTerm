#ifndef CATERM_PAINTER_PALETTE_BASIC_HPP
#define CATERM_PAINTER_PALETTE_BASIC_HPP
#include <caterm/painter/color.hpp>

namespace ox::basic {

constexpr auto Black   = Color::Background;
constexpr auto Maroon  = Color{1};
constexpr auto Green   = Color{2};
constexpr auto Olive   = Color{3};
constexpr auto Navy    = Color{4};
constexpr auto Purple  = Color{5};
constexpr auto Teal    = Color{6};
constexpr auto Silver  = Color{7};
constexpr auto Grey    = Color{8};
constexpr auto Red     = Color{9};
constexpr auto Lime    = Color{10};
constexpr auto Yellow  = Color{11};
constexpr auto Blue    = Color{12};
constexpr auto Fuchsia = Color{13};
constexpr auto Aqua    = Color{14};
constexpr auto White   = Color::Foreground;

/// The Built-in Default Terminal 16 Color Palette
inline auto const palette = Palette{
    /* clang-format off */
    {Black,   Color_index{0}},
    {Maroon,  Color_index{1}},
    {Green,   Color_index{2}},
    {Olive,   Color_index{3}},
    {Navy,    Color_index{4}},
    {Purple,  Color_index{5}},
    {Teal,    Color_index{6}},
    {Silver,  Color_index{7}},
    {Grey,    Color_index{8}},
    {Red,     Color_index{9}},
    {Lime,    Color_index{10}},
    {Yellow,  Color_index{11}},
    {Blue,    Color_index{12}},
    {Fuchsia, Color_index{13}},
    {Aqua,    Color_index{14}},
    {White,   Color_index{15}},
    /* clang-format on */
};

}  // namespace ox::basic
#endif  // CATERM_PAINTER_PALETTE_BASIC_HPP
