#ifndef CATERM_WIDGET_WIDGETS_CONFIRM_BUTTON_HPP
#define CATERM_WIDGET_WIDGETS_CONFIRM_BUTTON_HPP
#include <utility>

#include <signals_light/signal.hpp>

#include <caterm/painter/color.hpp>
#include <caterm/painter/glyph_string.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/stack.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/widgets/button.hpp>

namespace ox {

/// A Button with a confirm screen after the initial press.
/** Clicked signal is only emitted after confirmation. */
class Confirm_button : public layout::Stack<> {
   private:
    class Confirm_page : public layout::Horizontal<Button> {
       public:
        Child_t& confirm_btn;
        Child_t& exit_btn = this->make_child(U"X");

       public:
        explicit Confirm_page(Glyph_string confirm_text)
            : confirm_btn{this->make_child(std::move(confirm_text))}
        {
            using namespace pipe;
            confirm_btn | bg(Color::Blue) | fg(Color::Black);
            exit_btn | bg(Color::Gray) | fg(Color::Black) | fixed_width(3);
        }
    };

   public:
    /// Emitted once confirmation has been made.
    sl::Signal<void()> pressed;

   public:
    Button& main_btn;
    Confirm_page& confirm_page;

   public:
    /// Construct a Button with \p label and corresponding \p confirm_text.
    explicit Confirm_button(Glyph_string label,
                            Glyph_string confirm_text = "Confirm")
        : main_btn{this->make_page<Button>(std::move(label))},
          confirm_page{this->make_page<Confirm_page>(std::move(confirm_text))}
    {
        using namespace pipe;
        *this | fixed_height(1) | active_page(front_page_);
        this->give_focus_on_change(false);

        main_btn |
            on_left_click([this] { *this | active_page(confirm_page_); });

        confirm_page.confirm_btn | on_left_click([this] {
            pressed();
            *this | active_page(front_page_);
        });

        confirm_page.exit_btn |
            on_left_click([this] { *this | active_page(front_page_); });
    }

   private:
    static auto constexpr front_page_   = 0uL;
    static auto constexpr confirm_page_ = 1uL;
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto confirm_button(Args&&... args)
    -> std::unique_ptr<Confirm_button>
{
    return std::make_unique<Confirm_button>(std::forward<Args>(args)...);
}

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_CONFIRM_BUTTON_HPP
