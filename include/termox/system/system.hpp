#ifndef CATERM_SYSTEM_SYSTEM_HPP
#define CATERM_SYSTEM_SYSTEM_HPP
#include <mutex>
#include <utility>
#include <vector>

#include <signals_light/signal.hpp>

#include <caterm/system/animation_engine.hpp>
#include <caterm/system/detail/user_input_event_loop.hpp>
#include <caterm/system/event_fwd.hpp>
#include <caterm/terminal/terminal.hpp>
#include <caterm/widget/cursor.hpp>

namespace ox {
class Widget;
}  // namespace ox

namespace ox::detail {
class Event_engine;
}  // namespace ox::detail

namespace ox {

/// Organizes the highest level of the TUI framework.
/** Constructing an instance of this class initializes the display system.
 *  Manages the head Widget and the main User_input_event_loop. */
class System {
   public:
    /// Emitted when System::exit is called. Should call Event_loop::exit.
    /** Passes along the exit_code System::exit() was called with. */
    static sl::Signal<void(int)> exit_signal;

    // Slots
    static sl::Slot<void()> quit;

    /// Provides access to and modification of global terminal properties.
    inline static Terminal terminal;

   public:
    System() { terminal.initialize(); }
    System(System const&) = delete;
    System& operator=(System const&) = delete;
    System(System&&)                 = default;
    System& operator=(System&&) = default;

    ~System()
    {
        System::exit(0);
        terminal.uninitialize();
    }

    /// Return a pointer to the currently focused Widget.
    [[nodiscard]] static auto focus_widget() -> Widget*;

    /// Give program focus to \p w.
    /** Sends Focus_out_event to Widget in focus, and Focus_in_event to \p w. */
    static void set_focus(Widget& w);

    /// Removes focus from the currently in focus Widget.
    static void clear_focus();

    /// Enable Tab/Back_tab keys to change the focus Widget.
    static void enable_tab_focus();

    /// Disable Tab/Back_tab keys from changing focus Widget.
    static void disable_tab_focus();

    /// Set a new head Widget for the entire system.
    /** Will disable the previous head widget if not nullptr. Only valid to call
     *  before System::run or after System::exit. */
    static void set_head(Widget* new_head);

    /// Return a pointer to the head Widget.
    /** This Widget is the ancestor of every other widget that will be displayed
     *  on the screen. */
    static auto head() -> Widget* { return head_; }

    /// Create a Widget_t object, set it as head widget and call System::run().
    /** \p args... are passed on to the Widget_t constructor. Blocks until
     *  System::exit() is called, returns the exit code. Will throw a
     *  std::runtime_error if screen cannot be initialized. */
    template <typename Widget_t, typename... Args>
    auto run(Args&&... args) -> int
    {
        auto head = Widget_t(std::forward<Args>(args)...);
        System::set_head(&head);
        return this->run();
    }

    /// Set \p head as head widget and call System::run().
    /** Will throw a std::runtime_error if screen cannot be initialized. */
    auto run(Widget& head) -> int
    {
        System::set_head(&head);
        return this->run();
    }

    /// Launch the main Event_loop and start processing Events.
    /** Blocks until System::exit() is called, returns the exit code. Will throw
     *  a std::runtime_error if screen cannot be initialized. Enables and sets
     *  focus to the head Widget.*/
    static auto run() -> int;

    /// Immediately send the event filters and then to the intended receiver.
    /** Return true if the event was actually sent. */
    static auto send_event(Event e) -> bool;

    // Minor optimization.
    /** Return true if the event was actually sent. */
    static auto send_event(Paint_event e) -> bool;

    // Minor optimization.
    /** Return true if the event was actually sent. */
    static auto send_event(Delete_event e) -> bool;

    /// Append the event to the Event_queue for the thread it was called on.
    /** The Event_queue is processed once per iteration of the Event_loop. When
     *  the Event is pulled from the Event_queue, it is processed by
     *  System::send_event() */
    static void post_event(Event e);

    /// Send an exit signal to each of the currently running Event_loops.
    /** Also call shutdown() on the Animation_engine and set
     *  System::exit_requested_ to true. Though it sends the exit signal to each
     *  of the Event_loops, they are not guaranteed to be stopped by the time
     *  this function returns. */
    static void exit(int exit_code = 0);

    /// Returns a reference to the single Event_engine that owns the queue.
    static auto event_engine() -> detail::Event_engine&
    {
        return event_engine_;
    }

    /// Enable animation for the given Widget \p w at \p interval.
    /** Starts the animation_engine if not started yet. */
    static void enable_animation(Widget& w,
                                 Animation_engine::Interval_t interval)
    {
        if (!animation_engine_.is_running())
            animation_engine_.run_async();
        animation_engine_.register_widget(w, interval);
    }

    /// Enable animation for the given Widget \p w at \p fps.
    /** Starts the animation_engine if not started yet. */
    static void enable_animation(Widget& w, FPS fps)
    {
        if (!animation_engine_.is_running())
            animation_engine_.run_async();
        animation_engine_.register_widget(w, fps);
    }

   public:
    /// Disable animation for the given Widget \p w.
    /** Does not stop the animation_engine, even if its empty. */
    static void disable_animation(Widget& w)
    {
        animation_engine_.unregister_widget(w);
    }

    /// Return whether System has gotten an exit request, set by System::exit()
    static auto is_exit_requested() -> bool { return exit_requested_; }

    /// Set the terminal cursor via \p cursor parameters and \p offset applied.
    static void set_cursor(Cursor cursor, Point offset)
    {
        auto& term = System::terminal;
        if (!cursor.is_enabled())
            term.show_cursor(false);
        else {
            term.move_cursor({offset.x + cursor.x(), offset.y + cursor.y()});
            term.show_cursor();
        }
    }

   private:
    inline static Widget* head_        = nullptr;
    inline static bool exit_requested_ = false;
    static detail::User_input_event_loop user_input_loop_;
    static detail::Event_engine event_engine_;
    static Animation_engine animation_engine_;
};

}  // namespace ox
#endif  // CATERM_SYSTEM_SYSTEM_HPP
