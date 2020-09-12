#ifndef CPPURSES_WIDGET_POINT_HPP
#define CPPURSES_WIDGET_POINT_HPP
#include <cstddef>
#include <functional>

namespace cppurses {

/// Represents a 2D point in space.
/** Usually taken to be relative to the top-left corner of a Widget, or of the
 *  Terminal screen. */
struct Point {
    std::size_t x = 0;
    std::size_t y = 0;
};

inline auto operator==(Point const& lhs, Point const& rhs) -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline auto operator!=(Point const& lhs, Point const& rhs) -> bool
{
    return !(lhs == rhs);
}

/// Only useful for total ordering, is not accurate a true less than.
inline auto operator<(Point const& lhs, Point const& rhs) -> bool
{
    return (lhs.y < rhs.y) || (lhs.y == rhs.y && lhs.x < rhs.x);
}

inline auto operator+(Point const& lhs, Point const& rhs) -> Point
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

}  // namespace cppurses

/// Custom specialization of std::hash for cppurses::point.
namespace std {
template <>
struct hash<cppurses::Point> {
    using argument_type = cppurses::Point;
    using result_type   = std::size_t;
    auto operator()(argument_type const& point) const noexcept -> result_type
    {
        auto const h1 = std::hash<decltype(point.x)>{}(point.x);
        auto const h2 = std::hash<decltype(point.y)>{}(point.y);
        return h1 ^ (h2 << 1);
    }
};
}  // namespace std
#endif  // CPPURSES_WIDGET_POINT_HPP
