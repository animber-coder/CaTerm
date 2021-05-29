#include <caterm/system/detail/send.hpp>

#include <cassert>

#include <esc/event.hpp>

#include <caterm/painter/color.hpp>
#include <caterm/painter/detail/is_paintable.hpp>
#include <caterm/painter/painter.hpp>
#include <caterm/system/detail/focus.hpp>
#include <caterm/system/event.hpp>
#include <caterm/system/key.hpp>
#include <caterm/system/mouse.hpp>
#include <caterm/system/system.hpp>
#include <caterm/terminal/detail/screen_buffers.hpp>
#include <caterm/terminal/terminal.hpp>
#include <caterm/widget/area.hpp>
#include <caterm/widget/widget.hpp>

namespace ox::detail {

void send(ox::Paint_event e)
{
    if (!is_paintable(e.receiver))
        return;
    auto p = Painter{e.receiver, ox::Terminal::screen_buffers.next};
    e.receiver.get().paint_event(p);
}

void send(ox::Key_press_event e)
{
    if (e.receiver)
        e.receiver->get().key_press_event(e.key);
}

void send(ox::Mouse_press_event e)
{
    detail::Focus::mouse_press(e.receiver);
    e.receiver.get().mouse_press_event(e.data);
}

void send(ox::Mouse_release_event e)
{
    e.receiver.get().mouse_release_event(e.data);
}

void send(ox::Mouse_wheel_event e)
{
    e.receiver.get().mouse_wheel_event(e.data);
}

void send(ox::Mouse_move_event e) { e.receiver.get().mouse_move_event(e.data); }

void send(ox::Child_added_event e)
{
    e.receiver.get().child_added_event(e.child);
}

void send(ox::Child_removed_event e)
{
    e.receiver.get().child_removed_event(e.child);
}

void send(ox::Child_polished_event e)
{
    e.receiver.get().child_polished_event(e.child);
}

void send(ox::Delete_event e)
{
    if (e.removed == nullptr)
        return;
    e.removed->delete_event();
    for (Widget* w : e.removed->get_descendants())
        w->delete_event();
    e.removed.reset();
}

void send(ox::Disable_event e) { e.receiver.get().disable_event(); }

void send(ox::Enable_event e) { e.receiver.get().enable_event(); }

void send(ox::Focus_in_event e)
{
    Focus::direct_set_focus(e.receiver.get());
    e.receiver.get().focus_in_event();
}

void send(ox::Focus_out_event e) { e.receiver.get().focus_out_event(); }

void send(ox::Move_event e)
{
    auto const previous = e.receiver.get().top_left();
    if (previous == e.new_position)
        return;
    e.receiver.get().set_top_left(e.new_position);
    e.receiver.get().move_event(e.new_position, previous);
}

void send(ox::Resize_event e)
{
    auto const previous = e.receiver.get().area();
    if (previous == e.new_area)
        return;
    e.receiver.get().set_area(e.new_area);
    e.receiver.get().resize_event(e.new_area, previous);
}

void send(ox::Timer_event e)
{
    if (e.receiver.get().is_enabled())
        e.receiver.get().timer_event();
}

void send(ox::Dynamic_color_event const& e)
{
    for (auto [color, true_color] : e.color_data) {
        ox::Terminal::update_color_stores(color, true_color);
        ox::Terminal::repaint_color(color);
    }
}

void send(::esc::Window_resize x)
{
    ox::Widget& head = []() -> ox::Widget& {
        ox::Widget* head = ox::System::head();
        assert(head != nullptr);
        return *head;
    }();
    ox::Terminal::flag_full_repaint();
    ox::Terminal::screen_buffers.resize(x.new_dimensions);
    ox::System::post_event(ox::Resize_event{head, x.new_dimensions});
}

void send(ox::Custom_event e) { e.send(); }

}  // namespace ox::detail
