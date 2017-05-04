#include <system_module/object.hpp>
#include <widget_module/layout.hpp>
#include "painter_module/painter.hpp"
#include "system_module/events/paint_event.hpp"

namespace twf {

Layout::Layout() {
    // Set dimensions to maximum initially
    this->set_x(0);
    this->set_y(0);
    this->geometry().set_width(System::max_width());
    this->geometry().set_height(System::max_height());

    this->initialize();
}

void Layout::initialize() {
    // Slots
    this->update_layout = std::bind(&Layout::update, this);
    this->update_layout.track(this->destroyed);
}

void Layout::paint_too_small_warning() {
    this->erase_widget_screen();
    Painter p{this};
    p.move(0, 0);
    p.put("Layout too small for widgets.");
    // Widget::paint_event(Paint_event());
}

bool Layout::paint_event(const Paint_event& event) {
    this->update_geometry();
    return Widget::paint_event(event);
}

/* bool Layout::child_event(const Child_event& event) {
 *     this->update();
 *     return true;
 * } */

}  // namespace twf
