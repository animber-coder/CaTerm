#ifndef CATERM_SYSTEM_DETAIL_INTERVAL_EVENT_LOOP_HPP
#define CATERM_SYSTEM_DETAIL_INTERVAL_EVENT_LOOP_HPP
#include <algorithm>
#include <chrono>
#include <thread>

#include <caterm/system/event_loop.hpp>

namespace ox {

/// Frames Per Second
struct FPS {
    unsigned int value;
};

}  // namespace ox

namespace ox::detail {

/// loop_function() waits for a given time interval, then returns.
/** Not useful on its own, but can be inherited from, and its loop_function can
 *  be called on from the derived classes loop_function to perform the wait.
 *  Accounts for time since last wait so interval is not dependent on
 *  calculations in between the calls to wait. */
class Interval_event_loop : public Event_loop {
   public:
    using Period_t = std::chrono::milliseconds;

   public:
    explicit Interval_event_loop(Period_t interval) : interval_{interval} {}

    explicit Interval_event_loop(FPS fps) : interval_{fps_to_period(fps)} {}

    auto get_interval() const -> Period_t { return interval_; }

   public:
    /// Converts frames per second to an interval of time.
    static auto fps_to_period(FPS fps) -> Period_t
    {
        return Period_t{static_cast<Period_t::rep>((1. / fps.value) *
                                                   Period_t::period::den)};
    }

   protected:
    /// Tells the event engine to not processes the event queue.
    void loop_function() override { this->wait_on_interval(); }

   private:
    using Clock_t = std::chrono::high_resolution_clock;

    Period_t const interval_;
    std::chrono::time_point<Clock_t> last_time_;

   private:
    void wait_on_interval()
    {
        auto const time_to_sleep = [this] {
            auto const elapsed = Clock_t::now() - last_time_;
            return std::max(Clock_t::duration::zero(), interval_ - elapsed);
        }();
        std::this_thread::sleep_for(time_to_sleep);
        last_time_ = Clock_t::now();
    }
};

}  // namespace ox::detail
#endif  // CATERM_SYSTEM_DETAIL_INTERVAL_EVENT_LOOP_HPP
