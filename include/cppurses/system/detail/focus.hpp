#ifndef CPPURSES_SYSTEM_DETAIL_FOCUS_HPP
#define CPPURSES_SYSTEM_DETAIL_FOCUS_HPP

namespace cppurses {
class Widget;
struct Focus_in_event;
namespace detail {

class Focus {
   public:
    /// Return a pointer to the currently focused Widget.
    static auto focus_widget() -> cppurses::Widget* { return focus_widget_; }

    /// Sets the focus to \p clicked if it has a Focus_policy::Mouse/Strong.
    static void mouse_press(cppurses::Widget& clicked);

    /// Find the next Focus_policy::Tab/Strong Widget and set focus to it.
    static auto tab_press() -> bool;

    /// Find the previous Focus_policy::Tab/Strong Widget and set focus to it.
    static auto shift_tab_press() -> bool;

    /// Set focus to \p new_focus.
    /** If \p new_focus has Focus_policy::None, calls Focus::clear(). */
    static void set(cppurses::Widget& new_focus);

    /// Set the focus widget to nullptr.
    static void clear();

    /// Enable Tab/Back_tab keys to change the focus Widget.
    static void enable_tab_focus() { tab_enabled_ = true; }

    /// Disable Tab/Back_tab keys from changing focus Widget.
    static void disable_tab_focus() { tab_enabled_ = false; }

    /// Stops a Tab or Back_tab from changing focus to the next Widget.
    static void suppress_tab() { tab_suppressed_ = true; }

    /// Re-enable a Tab or Back_tab to change focus to the next Widget.
    static void unsuppress_tab() { tab_suppressed_ = false; }

    friend Focus_in_event;

   private:
    static cppurses::Widget* focus_widget_;
    static bool tab_enabled_;
    static bool tab_suppressed_;
};

}  // namespace detail
}  // namespace cppurses
#endif  // CPPURSES_SYSTEM_DETAIL_FOCUS_HPP
