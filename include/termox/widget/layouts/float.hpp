#ifndef CATERM_WIDGET_LAYOUT_FLOAT_HPP
#define CATERM_WIDGET_LAYOUT_FLOAT_HPP
#include <utility>

#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/widget.hpp>

namespace ox {

// TODO Think about adding stretch for either side, limit child add/remove
// functions, invariant should be only every having the widgets you have at
// construction.
template <typename Widget_t, template <typename> typename Layout_t>
class Float : public Layout_t<Widget> {
   private:
    using Base_t = Layout_t<Widget>;

   public:
    ox::Widget& buffer_1;
    Widget_t& widget;
    ox::Widget& buffer_2;

   public:
    template <typename... Args>
    Float(Args&&... args)
        : buffer_1{this->template make_child()},
          widget{
              this->template make_child<Widget_t>(std::forward<Args>(args)...)},
          buffer_2{this->template make_child()}
    {
        this->update_policy();
    }

   protected:
    auto child_polished_event(Widget& child) -> bool override
    {
        if (&child == &widget)
            this->update_policy();
        return Base_t::child_polished_event(child);
    }

   private:
    void update_policy()
    {
        if constexpr (ox::layout::is_horizontal_v<Base_t>)
            this->height_policy = widget.height_policy;
        else
            this->width_policy = widget.width_policy;
    }
};

template <typename Widget_t>
using Float_2d = ox::Float<ox::Float<Widget_t, ox::layout::Horizontal>,
                           ox::layout::Vertical>;

}  // namespace ox
#endif  //
