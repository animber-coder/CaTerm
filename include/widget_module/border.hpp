#ifndef BORDER_HPP
#define BORDER_HPP

#include <painter_module/glyph.hpp>

#include <cstddef>
#include <string>

namespace twf {
class Widget;

class Border {
   public:
    // explicit Border(Widget* w) : widget_{w} {}

    void set_walls(const Glyph& horizontals, const Glyph& verticals);
    void set_north(const Glyph& g) { north_ = g; }
    void set_south(const Glyph& g) { south_ = g; }
    void set_east(const Glyph& g) { east_ = g; }
    void set_west(const Glyph& g) { west_ = g; }
    void set_north_west(const Glyph& g) { north_west_ = g; }
    void set_north_east(const Glyph& g) { north_east_ = g; }
    void set_south_west(const Glyph& g) { south_west_ = g; }
    void set_south_east(const Glyph& g) { south_east_ = g; }

    Glyph north() const { return north_; }
    Glyph south() const { return south_; }
    Glyph east() const { return east_; }
    Glyph west() const { return west_; }
    Glyph north_west() const { return north_west_; }
    Glyph north_east() const { return north_; }
    Glyph south_west() const { return south_west_; }
    Glyph south_east() const { return south_east_; }

    // void set_parent(Widget* w) { widget_ = w; }

    bool enabled() const { return enabled_; }
    void enable() { enabled_ = true; }
    void disable() { enabled_ = false; }
    // std::size_t thickness() const { return thickness_; }

   private:
    Glyph north_ = "─";
    Glyph south_ = "─";
    Glyph east_ = "│";
    Glyph west_ = "│";
    Glyph north_west_ = "┌";
    Glyph north_east_ = "┐";
    Glyph south_west_ = "└";
    Glyph south_east_ = "┘";

    // std::size_t thickness_ = 1;// remove this

    bool enabled_ = false;
    // Widget* widget_ = nullptr;
};

}  // namespace twf
#endif  // BORDER_HPP
