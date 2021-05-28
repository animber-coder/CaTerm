#include <caterm/painter/painter.hpp>

#include <caterm/painter/glyph_string.hpp>
#include <caterm/system/event_loop.hpp>
#include <caterm/system/system.hpp>
#include <caterm/terminal/detail/canvas.hpp>
#include <caterm/widget/point.hpp>
#include <caterm/widget/widget.hpp>

namespace ox {

Painter::Painter(Widget& widg, detail::Canvas& canvas)
    : widget_{widg},
      inner_area_{widget_.width(), widget_.height()},
      canvas_{canvas},
      brush_{widg.brush}
{}

auto Painter::put(Glyph tile, Point p) -> Painter&
{
    // User code can contain invalid points.
    if (p.x >= inner_area_.width || p.y >= inner_area_.height || p.x < 0 ||
        p.y < 0) {
        return *this;
    }
    auto const x_global = widget_.inner_x() + p.x;
    auto const y_global = widget_.inner_y() + p.y;
    this->put_global(tile, {x_global, y_global});
    return *this;
}

auto Painter::put(Glyph_string const& text, Point p) -> Painter&
{
    for (Glyph g : text)
        this->put(g, {p.x++, p.y});
    return *this;
}

auto Painter::at(Point p) const -> Glyph
{
    auto const global = p + widget_.top_left();
    return canvas_.at(global);
}

auto Painter::at(Point p) -> Glyph&
{
    auto const global = p + widget_.top_left();
    return canvas_.at(global);
}

auto Painter::fill(Glyph tile, Point point, Area area) -> Painter&
{
    if (area.width == 0)
        return *this;
    auto const y_limit = point.y + area.height;
    auto const x_limit = point.x + area.width - 1;  // Used in inclusive context
    for (; point.y < y_limit; ++point.y)
        this->hline(tile, point, {x_limit, point.y});
    return *this;
}

auto Painter::hline(Glyph tile, Point a, Point b) -> Painter&
{
    for (; a.x <= b.x; ++a.x)
        this->put(tile, a);
    return *this;
}

auto Painter::vline(Glyph tile, Point a, Point b) -> Painter&
{
    for (; a.y <= b.y; ++a.y)
        this->put(tile, a);
    return *this;
}

auto Painter::wallpaper_fill() -> Painter&
{
    this->fill_global_no_brush(widget_.generate_wallpaper(), widget_.top_left(),
                               widget_.outer_area());
    return *this;
}

// GLOBAL COORDINATES - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void Painter::put_global(Glyph tile, Point p)
{
    tile.brush    = merge(tile.brush, brush_);
    canvas_.at(p) = tile;
}

void Painter::hline_global(Glyph tile, Point a, Point b)
{
    for (; a.x <= b.x; ++a.x)
        this->put_global(tile, a);
}

void Painter::hline_global_no_brush(Glyph tile, Point a, Point b)
{
    for (; a.x <= b.x; ++a.x)
        canvas_.at(a) = tile;
}

void Painter::vline_global(Glyph tile, Point a, Point b)
{
    for (; a.y <= b.y; ++a.y)
        this->put_global(tile, a);
}

void Painter::fill_global(Glyph tile, Point point, Area area)
{
    if (area.width == 0)
        return;
    auto const y_limit = point.y + area.height;
    auto const x_limit = point.x + area.width - 1;  // Used in inclusive context
    for (; point.y < y_limit; ++point.y)
        this->hline_global(tile, point, {x_limit, point.y});
}

void Painter::fill_global_no_brush(Glyph tile, Point point, Area area)
{
    if (area.width == 0)
        return;
    auto const y_limit = point.y + area.height;
    auto const x_limit = point.x + area.width - 1;  // Used in inclusive context
    for (; point.y < y_limit; ++point.y)
        this->hline_global_no_brush(tile, point, {x_limit, point.y});
}

}  // namespace ox
