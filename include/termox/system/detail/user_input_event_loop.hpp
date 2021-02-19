#ifndef CATERM_SYSTEM_DETAIL_USER_INPUT_EVENT_LOOP_HPP
#define CATERM_SYSTEM_DETAIL_USER_INPUT_EVENT_LOOP_HPP
#include <caterm/system/event_loop.hpp>

namespace ox::detail {

/// Event loop that blocks for user input on each iteration.
class User_input_event_loop : public Event_loop {
   protected:
    /// Wait on esc::read(), and post the result.
    void loop_function() override;
};

}  // namespace ox::detail
#endif  // CATERM_SYSTEM_DETAIL_USER_INPUT_EVENT_LOOP_HPP
