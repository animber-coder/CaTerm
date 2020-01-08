#include <cppurses/system/focus.hpp>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

#include <cppurses/system/event.hpp>
#include <cppurses/system/events/focus_event.hpp>
#include <cppurses/system/system.hpp>
#include <cppurses/widget/focus_policy.hpp>
#include <cppurses/widget/widget.hpp>

namespace {
using namespace cppurses;

bool is_tab_focus_policy(Focus_policy policy)
{
    return policy == Focus_policy::Strong || policy == Focus_policy::Tab;
}

bool is_click_focus_policy(Focus_policy policy)
{
    return policy == Focus_policy::Strong || policy == Focus_policy::Click;
}

const auto is_tab_focusable = [](const auto* widg) {
    return widg->enabled() && is_tab_focus_policy(widg->focus_policy);
};

// Return a widg tree from System::head() if focus_widget is nullptr.
auto gen_focus_front_widg_tree()
{
    auto widg_tree = System::head()->get_descendants();
    widg_tree.insert(std::begin(widg_tree), System::head());
    auto* const focus_widg = Focus::focus_widget();
    if (focus_widg != nullptr) {
        const auto begin = std::begin(widg_tree);
        const auto end   = std::end(widg_tree);
        const auto iter  = std::find(begin, end, focus_widg);
        if (iter != end)
            std::rotate(begin, iter, end);
    }
    return widg_tree;
}

Widget* next_tab_focus()
{
    if (System::head() == nullptr)
        return nullptr;
    const auto widg_tree  = gen_focus_front_widg_tree();
    const auto begin      = std::next(std::begin(widg_tree));
    const auto end        = std::end(widg_tree);
    const auto next_focus = std::find_if(begin, end, is_tab_focusable);
    return next_focus != end ? *next_focus : Focus::focus_widget();
}

Widget* previous_tab_focus()
{
    if (System::head() == nullptr)
        return nullptr;
    const auto widg_tree      = gen_focus_front_widg_tree();
    const auto begin          = std::rbegin(widg_tree);
    const auto end            = std::rend(widg_tree);
    const auto previous_focus = std::find_if(begin, end, is_tab_focusable);
    return previous_focus != end ? *previous_focus : Focus::focus_widget();
}

}  // namespace

namespace cppurses {

Widget* Focus::focus_widget_{nullptr};
bool Focus::tab_enabled_{true};
bool Focus::tab_suppressed_{false};

void Focus::mouse_press(Widget& clicked)
{
    if (&clicked == focus_widget_)
        return;
    if (is_click_focus_policy(clicked.focus_policy))
        Focus::set_focus_to(clicked);
}

bool Focus::tab_press()
{
    if (tab_enabled_ && !tab_suppressed_) {
        Widget* next = next_tab_focus();
        if (next == nullptr)
            Focus::clear();
        else
            Focus::set_focus_to(*next);
        return true;
    }
    tab_suppressed_ = false;
    return false;
}

bool Focus::shift_tab_press()
{
    if (tab_enabled_ && !tab_suppressed_) {
        Widget* previous = previous_tab_focus();
        if (previous == nullptr)
            Focus::clear();
        else
            Focus::set_focus_to(*previous);
        return true;
    }
    tab_suppressed_ = false;
    return false;
}

void Focus::set_focus_to(Widget& new_focus)
{
    if (&new_focus == focus_widget_)
        return;
    if (new_focus.focus_policy == Focus_policy::None) {
        Focus::clear();
        return;
    }
    if (focus_widget_ != nullptr) {
        // Focus_out_event has private constructor, can't use make_unique.
        std::unique_ptr<Focus_out_event> event{
            new Focus_out_event{*focus_widget_}};
        System::post_event(std::move(event));
    }
    focus_widget_ = &new_focus;
    std::unique_ptr<Focus_in_event> event{new Focus_in_event{*focus_widget_}};
    System::post_event(std::move(event));
}

void Focus::clear()
{
    if (focus_widget_ == nullptr)
        return;
    std::unique_ptr<Focus_out_event> event{new Focus_out_event(*focus_widget_)};
    System::post_event(std::move(event));
    focus_widget_ = nullptr;
}

}  // namespace cppurses
