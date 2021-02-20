#ifndef CATERM_SYSTEM_ANIMATION_ENGINE_HPP
#define CATERM_SYSTEM_ANIMATION_ENGINE_HPP
#include <map>
#include <mutex>

#include <caterm/common/lockable.hpp>
#include <caterm/common/timer.hpp>
#include <caterm/system/event_loop.hpp>

namespace ox {
class Widget;

/// Registers Widgets with intervals to send timer events.
class Animation_engine : private Lockable<std::recursive_mutex> {
   public:
    using Clock_t    = Timer::Clock_t;
    using Interval_t = Timer::Interval_t;
    using Time_point = Timer::Time_point;

    struct Registered_data {
        Interval_t interval;
        Time_point last_event_time;
    };

    static auto constexpr default_interval = Interval_t{100};

   public:
    ~Animation_engine()
    {
        loop_.exit(0);
        loop_.wait();
    }

   public:
    /// Register to start sending Timer_events to \p w every \p interval.
    void register_widget(Widget& w, Interval_t interval);

    /// Register to start sending Timer_events to \p w at \p fps.
    void register_widget(Widget& w, FPS fps);

    /// Stop the given Widget from being sent Timer_events.
    void unregister_widget(Widget& w);

    /// Return true if there are no registered widgets
    [[nodiscard]] auto is_empty() const -> bool { return subjects_.empty(); }

    /// Start another thread that waits on intervals and sents timer events.
    void start()
    {
        loop_.run_async([this] { this->loop_function(); });
    }

    /// Sends exit signal and waits for animation thread to exit.
    void stop()
    {
        loop_.exit(0);
        loop_.wait();
    }

    /// Return true if start() has been called, and hasn't been exited.
    [[nodiscard]] auto is_running() const -> bool { return loop_.is_running(); }

   private:
    std::map<Widget*, Registered_data> subjects_;
    Event_loop loop_;
    Timer timer_ = Timer{default_interval};

   private:
    /// Post any Timer_events that are ready to be posted.
    void post_timer_events();

    /// Waits on intervals then sends Timer_events.
    void loop_function();
};

}  // namespace ox
#endif  // CATERM_SYSTEM_ANIMATION_ENGINE_HPP
