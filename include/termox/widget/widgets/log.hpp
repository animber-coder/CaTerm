#ifndef CATERM_WIDGET_WIDGETS_LOG_HPP
#define CATERM_WIDGET_WIDGETS_LOG_HPP
#include <signals_light/signal.hpp>

#include <caterm/painter/glyph_string.hpp>
#include <caterm/system/key.hpp>
#include <caterm/widget/widgets/text_view.hpp>
#include <caterm/widget/widgets/textbox.hpp>

namespace ox {

/// A scrollable list of logged messages.
/** Received messages are posted at the bottom of the Log. */
class Log : public Textbox {
   public:
    struct Parameters {};

   public:
    explicit Log(Parameters = {}) {}

   public:
    void post_message(Glyph_string message)
    {
        if (!this->contents().empty())
            this->append(U"\n");
        this->append(std::move(message));
        this->update_display();
        auto const tl = this->top_line();
        auto const h  = this->height();
        auto const lc = this->line_count();
        if (tl + h < lc)
            this->scroll_down(lc - tl - h);
        this->set_cursor(this->contents().size());
    }

   protected:
    auto key_press_event(Key k) -> bool override
    {
        switch (k) {
            case Key::Arrow_right:
            case Key::Arrow_left:
            case Key::Arrow_up:
            case Key::Arrow_down: return Textbox::key_press_event(k);
            default: return true;
        }
    }

   private:
    using Text_view::append;
    using Text_view::erase;
    using Text_view::insert;
    using Text_view::pop_back;
    using Text_view::set_contents;
};

/// Helper function to create a Log instance.
[[nodiscard]] inline auto log(Log::Parameters parameters = {})
    -> std::unique_ptr<Log>
{
    return std::make_unique<Log>(std::move(parameters));
}

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_LOG_HPP
