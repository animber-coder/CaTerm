#include "system/system.hpp"
#include "painter/paint_buffer.hpp"
#include "painter/palette.hpp"
#include "system/event.hpp"
#include "system/event_loop.hpp"
#include "system/events/paint_event.hpp"
#include "system/detail/ncurses_event_listener.hpp"
#include "system/detail/event_queue.hpp"
#include "widget/widget.hpp"
#include <signals/slot.hpp>
#include <memory>
#include <utility>

namespace cppurses {
namespace detail {
class Abstract_event_listener;
}  // namespace detail

sig::Slot<void()> System::quit = []() { System::exit(); };  // NOLINT

Widget* System::head_ = nullptr;  // NOLINT
Event_loop System::event_loop_;
std::unique_ptr<Paint_buffer> System::paint_buffer_ = nullptr;  // NOLINT
std::unique_ptr<detail::Abstract_event_listener> System::event_listener_ =
    std::make_unique<detail::NCurses_event_listener>();  // NOLINT

std::unique_ptr<Palette> System::system_palette_ = nullptr;  // NOLINT

void System::post_event(std::unique_ptr<Event> event) {
    System::event_loop_.event_queue.append(std::move(event));
}

bool System::send_event(const Event& event) {
    bool handled = event.send_to_all_filters();
    if (!handled) {
        event.send();
    }
    return handled;
}

void System::exit(int return_code) {
    event_loop_.exit(return_code);
}

detail::Abstract_event_listener* System::event_listener() {
    return event_listener_.get();
}

Paint_buffer* System::paint_buffer() {
    return paint_buffer_.get();
}

void System::set_paint_buffer(std::unique_ptr<Paint_buffer> buffer) {
    paint_buffer_ = std::move(buffer);
    if (paint_buffer_ != nullptr) {
        System::post_event<Paint_event>(System::head());
    }
}

unsigned System::max_width() {
    return System::paint_buffer()->update_width();
}

unsigned System::max_height() {
    return System::paint_buffer()->update_height();
}

Widget* System::head() {
    return head_;
}

void System::set_palette(std::unique_ptr<Palette> palette) {
    system_palette_ = std::move(palette);
    system_palette_->initialize();
}

Palette* System::palette() {
    return system_palette_.get();
}

System::System() {
    System::set_paint_buffer(std::make_unique<Paint_buffer>());
    System::set_palette(std::make_unique<DawnBringer_palette>());
    this->disable_ctrl_characters();
}

System::~System() {
    System::set_paint_buffer(nullptr);
}

void System::set_head(Widget* head_widget) {
    head_ = head_widget;
}

void System::enable_ctrl_characters() {
    event_listener_->enable_ctrl_characters();
}

void System::disable_ctrl_characters() {
    event_listener_->disable_ctrl_characters();
}

int System::run() {
    int return_code = event_loop_.run();
    return return_code;
}

}  // namespace cppurses
