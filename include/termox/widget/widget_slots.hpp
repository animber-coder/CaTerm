#ifndef CATERM_WIDGET_WIDGET_SLOTS_HPP
#define CATERM_WIDGET_WIDGET_SLOTS_HPP
#include <signals_light/signal.hpp>

#include <caterm/painter/color.hpp>
#include <caterm/system/key.hpp>
#include <caterm/system/mouse.hpp>
#include <caterm/widget/point.hpp>

namespace ox {
class Widget;
}  // namespace ox

namespace ox::slot {

[[nodiscard]] auto enable(Widget& w) -> sl::Slot<void()>;

[[nodiscard]] auto disable(Widget& w) -> sl::Slot<void()>;

[[nodiscard]] auto update(Widget& w) -> sl::Slot<void()>;

[[nodiscard]] auto click(Widget& w) -> sl::Slot<void(Point, Mouse::Button)>;

[[nodiscard]] auto click(Widget& w, Point p) -> sl::Slot<void(Mouse::Button)>;

[[nodiscard]] auto click(Widget& w, Mouse::Button b) -> sl::Slot<void(Point)>;

[[nodiscard]] auto click(Widget& w, Point p, Mouse::Button b)
    -> sl::Slot<void()>;

[[nodiscard]] auto keypress(Widget& w) -> sl::Slot<void(Key)>;

[[nodiscard]] auto keypress(Widget& w, Key k) -> sl::Slot<void()>;

[[nodiscard]] auto set_background(Widget& w) -> sl::Slot<void(Color)>;

[[nodiscard]] auto set_background(Widget& w, Color c) -> sl::Slot<void()>;

[[nodiscard]] auto set_foreground(Widget& w) -> sl::Slot<void(Color)>;

[[nodiscard]] auto set_foreground(Widget& w, Color c) -> sl::Slot<void()>;

[[nodiscard]] auto toggle_cursor(Widget& w) -> sl::Slot<void()>;

}  // namespace ox::slot
#endif  // CATERM_WIDGET_WIDGET_SLOTS_HPP
