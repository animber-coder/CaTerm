#ifndef CATERM_PAINTER_PAINTER_HPP
#define CATERM_PAINTER_PAINTER_HPP
#include <caterm/painter/detail/screen_descriptor.hpp>
#include <caterm/terminal/detail/canvas.hpp>
#include <caterm/widget/area.hpp>
#include <caterm/widget/point.hpp>

namespace ox {
class Glyph_string;
struct Glyph;
class Widget;
namespace detail {
class Canvas;
}

/// Contains functions to paint Glyphs to a Widget's screen area.
/** For use within Widget::paint_event(...), and virtual overrides. */
class Painter {
   public:
    /// Construct an object ready to paint Glyphs from \p w to \p canvas.
    Painter(Widget& w, detail::Canvas& canvas);

    Painter(Painter const&) = delete;
    Painter(Painter&&)      = delete;
    Painter& operator=(Painter const&) = delete;
    Painter& operator=(Painter&&) = delete;

   public:
    /// Put single Glyph to local coordinates.
    void put(Glyph tile, Point p);

    /// Put Glyph_string to local coordinates.
    void put(Glyph_string const& text, Point p);

    /// Paint the Border object around the outside of the associated Widget.
    /** Borders own the perimeter defined by Widget::x(), Widget::y() and
     *  Widget::outer_width(), Widget::outer_height(). Border is owned by
     *  widget_ */
    void border();

    /// Fill the Widget with \p tile Glyphs starting at the top left \p point.
    /** \p point is in Widget local coordinates. */
    void fill(Glyph tile, Point point, Area area);

    /// Draw a horizontal line from \p a to \p b, inclusive, in local coords.
    void hline(Glyph tile, Point a, Point b);

    /// Draw a vertical line from \p a to \p b, inclusive, in local coords.
    void vline(Glyph tile, Point a, Point b);

    /// Fill the entire widget screen with wallpaper.
    void wallpaper_fill();

   private:
    /// Put a single Glyph to the canvas_ container.
    /** No bounds checking, used internally for all painting. Main entry point
     *  for modifying the canvas_ object. */
    void put_global(Glyph tile, Point p)
    {
        tile.brush    = merge(tile.brush, brush_);
        canvas_.at(p) = tile;
    }

    /// Paint a line from \p a to \p b inclusive using global coordinates.
    /** No bounds checking, used internally for Border object painting. */
    void hline_global(Glyph tile, Point a, Point b);

    /// Paint a line from \p a to \p b inclusive using global coordinates.
    /** No bounds checking, used internally for Border object painting. */
    void vline_global(Glyph tile, Point a, Point b);

    /// Fill the Widget with \p tile Glyphs starting at the top left \p point.
    /** No bounds checking, used internally in Painter constructor. */
    void fill_global(Glyph tile, Point point, Area area);

   private:
    Widget const& widget_;
    Area const inner_area_;
    detail::Canvas& canvas_;
    Brush brush_;
};

}  // namespace ox
#endif  // CATERM_PAINTER_PAINTER_HPP
