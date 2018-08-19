#ifndef WIDGET_LAYOUTS_HORIZONTAL_LAYOUT_HPP
#define WIDGET_LAYOUTS_HORIZONTAL_LAYOUT_HPP
#include <cstddef>
#include <functional>
#include <vector>

#include <cppurses/widget/layout.hpp>

namespace cppurses {
class Widget;

class Horizontal_layout : public Layout {
   protected:
    void update_geometry() override;

   private:
    std::vector<Dimensions> calculate_widget_sizes();
    void move_and_resize_children(const std::vector<Dimensions>& dimensions);

    void distribute_space(std::vector<Dimensions_reference> widgets,
                          int width_left);

    void collect_space(std::vector<Dimensions_reference> widgets,
                       int width_left);
};

}  // namespace cppurses
#endif  // WIDGET_LAYOUTS_HORIZONTAL_LAYOUT_HPP
