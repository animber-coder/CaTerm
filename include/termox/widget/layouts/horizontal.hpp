#ifndef CATERM_WIDGET_LAYOUTS_HORIZONTAL_HPP
#define CATERM_WIDGET_LAYOUTS_HORIZONTAL_HPP
#include <cstddef>

#include "detail/linear_layout.hpp"

namespace ox::layout::h_detail {

struct Get_area {
    auto operator()(std::size_t primary, std::size_t secondary) const -> Area
    {
        return {primary, secondary};
    }
};

struct Get_point {
    auto operator()(std::size_t primary, std::size_t secondary) const -> Point
    {
        return {primary, secondary};
    }
};

struct Primary_policy {
    auto operator()(Widget const& w) const -> Size_policy const&
    {
        return w.width_policy;
    }
};

struct Primary_length {
    auto operator()(Widget const& w) const -> std::size_t { return w.width(); }
};

struct Primary_offset {
    auto operator()(Widget const& w) const -> std::size_t
    {
        return w.inner_x();
    }
};

struct Secondary_policy {
    auto operator()(Widget const& w) const -> Size_policy const&
    {
        return w.height_policy;
    }
};

struct Secondary_length {
    auto operator()(Widget const& w) const -> std::size_t { return w.height(); }
};

struct Secondary_offset {
    auto operator()(Widget const& w) const -> std::size_t
    {
        return w.inner_y();
    }
};

using Primary = detail::Dimension_parameters<Primary_policy,
                                             Primary_length,
                                             Primary_offset,
                                             Policy_direction::Horizontal>;

using Secondary = detail::Dimension_parameters<Secondary_policy,
                                               Secondary_length,
                                               Secondary_offset,
                                               Policy_direction::Vertical>;

using Horizontal_parameters =
    detail::Linear_layout_parameters<Primary, Secondary, Get_area, Get_point>;

}  // namespace ox::layout::h_detail

namespace ox::layout {

template <typename Child_t = Widget>
using Horizontal =
    detail::Linear_layout<Child_t, h_detail::Horizontal_parameters>;

/// Helper function to create an instance.
template <typename Widget_t = Widget, typename... Args>
auto horizontal(Args&&... args) -> std::unique_ptr<Horizontal<Widget_t>>
{
    return std::make_unique<Horizontal<Widget_t>>(std::forward<Args>(args)...);
}

template <typename T>
struct Is_horizontal : std::false_type {};

template <typename Child_t>
struct Is_horizontal<layout::Horizontal<Child_t>> : std::true_type {};

template <typename Layout_t>
constexpr bool is_horizontal_v = Is_horizontal<Layout_t>::value;

}  // namespace ox::layout
#endif  // CATERM_WIDGET_LAYOUTS_HORIZONTAL_HPP
