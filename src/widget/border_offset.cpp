#include <cppurses/widget/detail/border_offset.hpp>

#include <cstddef>

#include <cppurses/widget/border.hpp>
#include <cppurses/widget/widget.hpp>

namespace cppurses {
namespace detail {

bool Border_offset::west_disqualified(const Widget& w) {
    return w.outer_width() <= 1;
}

bool Border_offset::east_disqualified(const Widget& w) {
    if (w.outer_width() <= 1) {
        return true;
    }
    if (w.outer_width() == 2 && w.border.west_enabled) {
        return true;
    }
    return false;
}

bool Border_offset::north_disqualified(const Widget& w) {
    return w.outer_height() <= 1;
}

bool Border_offset::south_disqualified(const Widget& w) {
    if (w.outer_height() <= 1) {
        return true;
    }
    if (w.outer_height() == 2 && w.border.north_enabled) {
        return true;
    }
    return false;
}

std::size_t Border_offset::west(const Widget& w) {
    const Border& b{w.border};
    if (b.enabled && !west_disqualified(w) &&
        (b.west_enabled || b.north_west_enabled || b.south_west_enabled)) {
        return 1;
    }
    return 0;
}

std::size_t Border_offset::east(const Widget& w) {
    const Border& b{w.border};
    if (b.enabled && !east_disqualified(w) &&
        (b.east_enabled || b.north_east_enabled || b.south_east_enabled)) {
        return 1;
    }
    return 0;
}

std::size_t Border_offset::north(const Widget& w) {
    const Border& b{w.border};
    if (b.enabled && !north_disqualified(w) &&
        (b.north_enabled || b.north_east_enabled || b.north_west_enabled)) {
        return 1;
    }
    return 0;
}

std::size_t Border_offset::south(const Widget& w) {
    const Border& b{w.border};
    if (b.enabled && !south_disqualified(w) &&
        (b.south_enabled || b.south_east_enabled || b.south_west_enabled)) {
        return 1;
    }
    return 0;
}

}  // namespace detail
}  // namespace cppurses
