#ifndef CATERM_WIDGET_LAYOUTS_DETAIL_LINEAR_LAYOUT_HPP
#define CATERM_WIDGET_LAYOUTS_DETAIL_LINEAR_LAYOUT_HPP
#include <cassert>

#include <caterm/system/event.hpp>
#include <caterm/widget/layout.hpp>

#include "shared_space.hpp"
#include "unique_space.hpp"

namespace ox::layout::detail {

template <typename Get_policy_t, typename Get_length_t, typename Get_offset_t>
struct Dimension_parameters {
    using get_policy = Get_policy_t;  // Size_policy const&(Widget const&)
    using get_length = Get_length_t;  // std::size_t(Widget const&) [w/h]
    using get_offset = Get_offset_t;  // std::size_t(Widget const&) [global x/y]
};

template <typename Primary_t,
          typename Secondary_t,
          typename Get_area_t,
          typename Get_point_t>
struct Linear_layout_parameters {
    using Primary   = Primary_t;
    using Secondary = Secondary_t;
    using get_area  = Get_area_t;   // Area(size_t primary, size_t secondary)
    using get_point = Get_point_t;  // Point(size_t primary, size_t secondary)
};

/// Lays out Widgets in 2D, sharing space in a primary dimension.
/** The secondary dimension does not share space among Widgets. */
template <typename Child, typename Parameters>
class Linear_layout : public Layout<Child> {
   public:
    using Child_t = Child;

   private:
    using Base_t = Layout<Child_t>;

    template <typename UnaryPredicate>
    using enable_if_invocable = std::enable_if_t<
        std::is_invocable_v<UnaryPredicate,
                            std::add_lvalue_reference_t<Child_t>>,
        int>;

   public:
    using Layout<Child>::Layout;

   public:
    // Forwarding functions so that child_offset can be updated. Currently you
    // don't hold generic Layout pointers anywhere, so these do not have to be
    // virtual, but keep this in mind if you every hold Layouts and Widgets
    // separately.

    [[nodiscard]] auto remove_child(Child_t const* child)
        -> std::unique_ptr<Widget>
    {
        auto result = this->Base_t::remove_child(child);
        this->reset_offset_if_out_of_bounds();
        return result;
    }

    /// Removes and returns the first child where predicate(child) returns true.
    /** If no child is found, returns nullptr. */
    template <typename UnaryPredicate,
              typename = enable_if_invocable<UnaryPredicate>>
    [[nodiscard]] auto remove_child_if(UnaryPredicate&& predicate)
        -> std::unique_ptr<Widget>
    {
        auto result = this->Base_t::remove_child_if(
            std::forward<UnaryPredicate>(predicate));
        this->reset_offset_if_out_of_bounds();
        return result;
    }

    /// Removes and returns the child at \p index in the child container.
    /** Returns nullptr if \p index is out of range. */
    [[nodiscard]] auto remove_child_at(std::size_t index)
        -> std::unique_ptr<Widget>
    {
        auto result = this->Base_t::remove_child_at(index);
        this->reset_offset_if_out_of_bounds();
        return result;
    }

    /// Removes the child with given pointer and sends a Delete_event to it.
    /** Returns false if \p child is not found and deleted. */
    auto remove_and_delete_child(Child_t const* child) -> bool
    {
        auto const result = this->Base_t::remove_and_delete_child(child);
        this->reset_offset_if_out_of_bounds();
        return result;
    }

    /// Erase first element that satisfies \p pred.
    /** Returns true if a child is found and deleted. */
    template <typename UnaryPredicate,
              typename = enable_if_invocable<UnaryPredicate>>
    auto remove_and_delete_child_if(UnaryPredicate&& predicate) -> bool
    {
        auto const result = this->Base_t::remove_and_delete_child_if(
            std::forward<UnaryPredicate>(predicate));
        this->reset_offset_if_out_of_bounds();
        return result;
    }

    /// Removes the child at \p index and sends a Delete_event to it.
    /** Returns false if \p index is out of range. */
    auto remove_and_delete_child_at(std::size_t index) -> bool
    {
        auto const result = this->Base_t::remove_and_delete_child_at(index);
        this->reset_offset_if_out_of_bounds();
        return result;
    }

    /// Removes all children and sends Delete_events to each.
    void delete_all_children()
    {
        this->Base_t::delete_all_children();
        this->set_child_offset(0);
    }

   public:
    /// Sets the child Widget offset, does not do bounds checking.
    void set_child_offset(std::size_t index)
    {
        assert(index <= this->child_count());
        Widget::child_offset_ = index;
        shared_space_.set_offset(index);
        unique_space_.set_offset(index);
        System::post_event(Child_polished_event{*this, *this});
    }

    void decrement_offset()
    {
        auto const offset = this->get_child_offset();
        if (offset == 0)
            return;
        this->set_child_offset(offset - 1);
    }

    void increment_offset()
    {
        auto const offset = this->get_child_offset();
        if (offset + 1 >= this->child_count())
            return;
        this->set_child_offset(offset + 1);
    }

   protected:
    using Parameters_t = Parameters;

   protected:
    void update_geometry() override
    {
        auto const primary_lengths = shared_space_.calculate_lengths(*this);
        auto const primary_pos =
            shared_space_.calculate_positions(primary_lengths);

        auto const secondary_lengths = unique_space_.calculate_lengths(*this);
        auto const secondary_pos =
            unique_space_.calculate_positions(secondary_lengths);

        this->send_enable_disable_events(primary_lengths, secondary_lengths);
        this->send_resize_events(primary_lengths, secondary_lengths);
        this->send_move_events(primary_pos, secondary_pos);
    }

   private:
    using Length_list   = std::vector<int>;
    using Position_list = std::vector<int>;

    Shared_space<Parameters> shared_space_;
    Unique_space<Parameters> unique_space_;

   private:
    void send_enable_disable_events(Length_list const& primary,
                                    Length_list const& secondary)
    {
        auto const children = this->get_children();
        auto const offset   = this->get_child_offset();
        for (auto i = 0uL; i < offset; ++i) {
            if (children[i].is_enabled())
                children[i].disable(true, false);
        }
        for (auto i = 0uL; i < primary.size(); ++i) {
            auto& child = children[offset + i];
            if (is_valid(primary[i], secondary[i])) {
                if (!child.is_enabled())
                    child.enable(true, false);
            }
            else if (child.is_enabled())
                child.disable(true, false);
        }
    }

    void send_resize_events(Length_list const& primary,
                            Length_list const& secondary)
    {
        auto const children = this->get_children();
        auto const offset   = this->get_child_offset();
        for (auto i = 0uL; i < primary.size(); ++i) {
            auto& child = children[offset + i];
            if (child.is_enabled()) {
                auto const area =
                    typename Parameters::get_area{}(primary[i], secondary[i]);
                System::post_event(Resize_event{child, area});
            }
        }
    }

    void send_move_events(Position_list const& primary,
                          Position_list const& secondary)
    {
        auto const children = this->get_children();
        auto const offset   = this->get_child_offset();
        auto const primary_offset =
            typename Parameters::Primary::get_offset{}(*this);
        auto const secondary_offset =
            typename Parameters::Secondary::get_offset{}(*this);
        for (auto i = 0uL; i < primary.size(); ++i) {
            auto& child = children[offset + i];
            if (child.is_enabled()) {
                auto const point = typename Parameters::get_point{}(
                    primary[i] + primary_offset,
                    secondary[i] + secondary_offset);
                System::post_event(Move_event{child, point});
            }
        }
    }

    /// Determine whether a widget is valid to display from its lengths
    /** A length of zero in any dimension means the Widget will be disabled. */
    // TODO This is ambiguous, what if a zero width/height wants to be enabled?
    // Need another data member to tell if something should be enabled or not.
    // What's the use case? Feb 22, 2021
    [[nodiscard]] static auto is_valid(std::size_t primary,
                                       std::size_t secondary) -> bool
    {
        return primary != 0 && secondary != 0;
    }

    /// After a remove_child or remove_and_delete_child this is called.
    void reset_offset_if_out_of_bounds()
    {
        auto const count = this->child_count();
        if (count == 0)
            this->set_child_offset(0);
        else if (this->get_child_offset() >= count)
            this->set_child_offset(count - 1);
    }
};

}  // namespace ox::layout::detail
#endif  // CATERM_WIDGET_LAYOUTS_DETAIL_LINEAR_LAYOUT_HPP
