#ifndef CATERM_TERMINAL_DYNAMIC_COLOR_ENGINE_HPP
#define CATERM_TERMINAL_DYNAMIC_COLOR_ENGINE_HPP
#include <mutex>
#include <vector>

#include <caterm/common/lockable.hpp>
#include <caterm/common/timer.hpp>
#include <caterm/painter/color.hpp>
#include <caterm/system/event_loop.hpp>
#include <caterm/system/event_queue.hpp>

namespace ox {

/// Event loop that manages posting of Dynamic_color_events.
class Dynamic_color_engine : private Lockable<std::mutex> {
   public:
    using Clock_t    = Timer::Clock_t;
    using Interval_t = Timer::Interval_t;
    using Time_point = Timer::Time_point;

    struct Registered_data {
        Color color;
        Dynamic_color dynamic;
        Time_point last_event_time;
    };

    static auto constexpr default_interval = Interval_t{100};

   public:
    /// Add a dynamic color linked to \p color.
    /** Does not check for duplicates. */
    void register_color(Color color, Dynamic_color const& dynamic);

    /// Removes the Dynamic_color linked to \p color.
    /** Function does nothing if Color is not found. */
    void unregister_color(Color color);

    /// Remove all registered colors.
    void clear();

    /// Return true if there are no registered widgets
    [[nodiscard]] auto is_empty() const -> bool;

    /// Start another thread that waits on intervals and sents Events.
    void start();

    /// Sends exit signal and waits for animation thread to exit.
    void stop();

   private:
    std::vector<Registered_data> data_;
    Event_loop loop_;
    Timer timer_ = Timer{default_interval};

   private:
    /// Post any Dynamic_color_events that are ready to be posted.
    auto get_dynamic_color_event() -> Dynamic_color_event;

    /// Waits on intervals then sends Dynamic_color_events.
    void loop_function(Event_queue& queue);
};

}  // namespace ox
#endif  // CATERM_TERMINAL_DYNAMIC_COLOR_ENGINE_HPP
