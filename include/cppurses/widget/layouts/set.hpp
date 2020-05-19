#ifndef CPPURSES_WIDGET_LAYOUTS_SET_HPP
#define CPPURSES_WIDGET_LAYOUTS_SET_HPP
#include <algorithm>
#include <functional>
#include <memory>
#include <type_traits>

#include <cppurses/common/identity.hpp>

namespace cppurses::layout {

/// Provides a set-like interface to Layout_t.
/** Projection transforms a Layout::Child_t into a comparable. */
/** Comparison is fed the output of Projection, used to find insertion pos. */
/** Comparison{}(Projection{}(element), Projection{}(child)); */
template <typename Layout_t,
          typename Projection = Identity,
          typename Comparison = std::less<
              std::invoke_result_t<Projection,
                                   std::add_const_t<std::add_lvalue_reference_t<
                                       typename Layout_t::Child_t>>>>>
class Set : public Layout_t {
   public:
    using Child_t = typename Layout_t::Child_t;

    using Key_t =
        std::invoke_result_t<Projection,
                             std::add_const_t<std::add_lvalue_reference_t<
                                 typename Layout_t::Child_t>>>;

   public:
    /// Insert \p child into correct position based on Projection and Comparison
    auto insert(std::unique_ptr<Child_t> child) -> Child_t&
    {
        auto const comp = [&](Child_t const& a, Child_t const& b) {
            return Comparison{}(Projection{}(a), Projection{}(b));
        };
        auto const children = this->get_children();
        auto iter =
            std::upper_bound(children.begin(), children.end(), *child, comp);
        return this->Widget::children_.insert(std::move(child),
                                              iter.underlying().underlying());
    }

    /// Create a Widget and insert it into the list of children.
    /** Return a reference to this newly created Widget. */
    template <typename Widget_t = Child_t, typename... Args>
    auto make_child(Args&&... args) -> Widget_t&
    {
        static_assert(
            std::is_base_of_v<Child_t, Widget_t>,
            "layout::Set::make_child: Widget_t must be a Child_t type");
        return this->insert(
            std::make_unique<Widget_t>(std::forward<Args>(args)...));
    }

    /// Find a child widget by its key type(the result of the Projection fn).
    /** Uses the Projection function on each child until a result equal to \p
     *  key is found. Retuns nullptr if no child found. */
    auto find(Key_t const& key) -> Child_t*
    {
        return this->get_children().find(
            [&key](auto const& c) { return Projection{}(c) == key; });
    }

   private:
    using Layout_t::append;
};

}  // namespace cppurses::layout
#endif  // CPPURSES_WIDGET_LAYOUTS_SET_HPP
