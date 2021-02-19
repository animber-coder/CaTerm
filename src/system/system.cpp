#include <caterm/system/system.hpp>

#include <algorithm>
#include <iterator>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

#include <signals_light/signal.hpp>

#include <caterm/system/animation_engine.hpp>
#include <caterm/system/detail/event_engine.hpp>
#include <caterm/system/detail/event_queue.hpp>
#include <caterm/system/detail/filter_send.hpp>
#include <caterm/system/detail/focus.hpp>
#include <caterm/system/detail/is_sendable.hpp>
#include <caterm/system/detail/send.hpp>
#include <caterm/system/detail/send_shortcut.hpp>
#include <caterm/system/detail/user_input_event_loop.hpp>
#include <caterm/system/event.hpp>
#include <caterm/system/event_loop.hpp>
#include <caterm/system/system.hpp>
#include <caterm/terminal/terminal.hpp>
#include <caterm/widget/area.hpp>
#include <caterm/widget/widget.hpp>

namespace ox {

auto System::focus_widget() -> Widget* { return detail::Focus::focus_widget(); }

void System::set_focus(Widget& w) { detail::Focus::set(w); }

void System::clear_focus() { detail::Focus::clear(); }

void System::enable_tab_focus() { detail::Focus::enable_tab_focus(); }

void System::disable_tab_focus() { detail::Focus::disable_tab_focus(); }

void System::post_event(Event e)
{
    System::event_engine().append(std::move(e));
}

void System::exit(int exit_code)
{
    System::exit_requested_ = true;
    System::exit_signal(exit_code);
    animation_engine_.exit(0);
    animation_engine_.wait();
}

void System::set_head(Widget* new_head)
{
    if (head_ != nullptr)
        head_->disable();
    head_ = new_head;
}

auto System::run() -> int
{
    if (head_ == nullptr)
        return -1;
    head_->enable();
    System::post_event(Resize_event{*System::head(), terminal.area()});
    detail::Focus::set(*head_);
    return user_input_loop_.run();
}

auto System::send_event(Event e) -> bool
{
    auto handled =
        std::visit([](auto const& e) { return detail::send_shortcut(e); }, e);
    if (!std::visit([](auto const& e) { return detail::is_sendable(e); }, e))
        return false;
    if (!handled) {
        handled =
            std::visit([](auto const& e) { return detail::filter_send(e); }, e);
    }
    if (!handled)
        std::visit([](auto e) { detail::send(std::move(e)); }, std::move(e));
    return true;
}

auto System::send_event(Paint_event e) -> bool
{
    if (!detail::is_sendable(e))
        return false;
    auto const handled = detail::filter_send(e);
    if (!handled)
        detail::send(std::move(e));
    return true;
}

auto System::send_event(Delete_event e) -> bool
{
    auto const handled = detail::filter_send(e);
    if (!handled)
        detail::send(std::move(e));
    return true;
}

sl::Slot<void()> System::quit = [] { System::exit(); };
detail::Event_engine System::event_engine_;
Animation_engine System::animation_engine_;

// GCC requires this here, it can't find the default constructor when it's in
// system.hpp for whatever reason...
sl::Signal<void(int)> System::exit_signal;
detail::User_input_event_loop System::user_input_loop_;

}  // namespace ox
