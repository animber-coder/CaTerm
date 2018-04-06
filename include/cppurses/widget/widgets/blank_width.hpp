#ifndef WIDGET_WIDGETS_BLANK_WIDTH_HPP
#define WIDGET_WIDGETS_BLANK_WIDTH_HPP
#include <cstddef>

#include <cppurses/widget/widget.hpp>

namespace cppurses {

class Blank_width : public Widget {
   public:
    explicit Blank_width(std::size_t width = 1);
};

}  // namespace cppurses

#endif  // WIDGET_WIDGETS_BLANK_WIDTH_HPP
