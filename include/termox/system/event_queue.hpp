#ifndef CATERM_SYSTEM_EVENT_QUEUE_HPP
#define CATERM_SYSTEM_EVENT_QUEUE_HPP
#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include <caterm/common/unique_queue.hpp>
#include <caterm/system/event.hpp>

namespace ox {

[[nodiscard]] inline auto operator<(Paint_event const& x, Paint_event const& y)
    -> bool
{
    return std::addressof(x.receiver.get()) < std::addressof(y.receiver.get());
}

[[nodiscard]] inline auto operator==(Paint_event const& a, Paint_event const& b)
    -> bool
{
    return std::addressof(a.receiver.get()) == std::addressof(b.receiver.get());
}

}  // namespace ox

namespace ox::detail {

class Paint_queue {
   public:
    void append(Paint_event e) { events_.append(e); }

    /// Return true if any events are actually sent.
    auto send_all() -> bool;

    [[nodiscard]] auto size() const -> std::size_t { return events_.size(); }

   private:
    Unique_queue<Paint_event> events_;
};

class Delete_queue {
   public:
    void append(Delete_event e) { deletes_.push_back(std::move(e)); }

    void send_all();

    [[nodiscard]] auto size() const -> std::size_t { return deletes_.size(); }

   private:
    std::vector<Delete_event> deletes_;
};

class Basic_queue {
   public:
    void append(Event e) { basics_.push_back(std::move(e)); }

    auto send_all() -> bool;

    [[nodiscard]] auto size() const -> std::size_t { return basics_.size(); }

   private:
    std::vector<Event> basics_;
};

}  // namespace ox::detail

namespace ox {

class Event_queue {
   public:
    /// Adds the given event with priority for the underlying event type.
    void append(Event e)
    {
        std::visit(
            [this](auto&& e) {
                this->add_to_a_queue(std::forward<decltype(e)>(e));
            },
            std::move(e));
    }

    /// Send all events, then flush the screen if any events were actually sent.
    void send_all();

   private:
    detail::Basic_queue basics_;
    detail::Paint_queue paints_;
    detail::Delete_queue deletes_;

   private:
    template <typename T>
    void add_to_a_queue(T e)
    {
        basics_.append(std::move(e));
    }

    void add_to_a_queue(Paint_event e) { paints_.append(std::move(e)); }

    void add_to_a_queue(Delete_event e) { deletes_.append(std::move(e)); }
};

}  // namespace ox
#endif  // CATERM_SYSTEM_EVENT_QUEUE_HPP
