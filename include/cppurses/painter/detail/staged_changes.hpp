#ifndef CPPURSES_PAINTER_DETAIL_STAGED_CHANGES_HPP
#define CPPURSES_PAINTER_DETAIL_STAGED_CHANGES_HPP
#include <unordered_map>

#include <cppurses/painter/detail/screen_descriptor.hpp>

namespace cppurses {
class Widget;
namespace detail {

/// Global map holds the changes to be flushed to the screen.
class Staged_changes {
   public:
    using Map_t = std::unordered_map<Widget*, Screen_descriptor>;

   public:
    /// Return the global Staged_changes map object.
    static auto get() -> Map_t&
    {
        static auto changes = Map_t{};
        return changes;
    }
};

}  // namespace detail
}  // namespace cppurses
#endif  // CPPURSES_PAINTER_DETAIL_STAGED_CHANGES_HPP
