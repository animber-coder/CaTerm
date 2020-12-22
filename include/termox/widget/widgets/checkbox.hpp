#ifndef CATERM_WIDGET_WIDGETS_CHECKBOX_HPP
#define CATERM_WIDGET_WIDGETS_CHECKBOX_HPP
#include <utility>

#include <signals_light/signal.hpp>

#include <caterm/painter/glyph.hpp>
#include <caterm/painter/glyph_string.hpp>
#include <caterm/painter/painter.hpp>
#include <caterm/system/mouse.hpp>
#include <caterm/widget/detail/link_lifetimes.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/widget.hpp>
#include <caterm/widget/widgets/label.hpp>

namespace ox {

/// Checkbox Widget that is either checked or not checked.
/** Uses mouse left button click to toggle between states. */
class Checkbox : public Widget {
   public:
    /// Emitted when box becomes checked.
    sl::Signal<void()> checked;

    /// Emitted when box becomes unchecked.
    sl::Signal<void()> unchecked;

    /// Emitted every time the box changes state.
    sl::Signal<void()> toggled;

   public:
    explicit Checkbox(bool is_checked = false,
                      Glyph checked   = L'☒',
                      Glyph unchecked = L'☐')
        : is_checked_{is_checked}, checked_{checked}, unchecked_{unchecked}
    {
        using namespace pipe;
        *this | fixed_height(1) | fixed_width(1);
    }

    /// Change state to be unchecked if currently checked, checked otherwise.
    void toggle()
    {
        is_checked_ = !is_checked_;
        toggled();
        is_checked_ ? checked() : unchecked();
        this->update();
    }

    /// Set the state to be checked.
    void check()
    {
        if (not is_checked_)
            this->toggle();
    }

    /// Set the state to be unchecked.
    void uncheck()
    {
        if (is_checked_)
            this->toggle();
    }

    /// Return whether Checkbox is currently checked.
    auto is_checked() const -> bool { return is_checked_; }

    /// Set the Glyph used for a checked box.
    void set_checked_glyph(Glyph const& symbol)
    {
        checked_ = symbol;
        this->update();
    }

    /// Set the Glyph used for an unchecked box.
    void set_unchecked_glyph(Glyph const& symbol)
    {
        unchecked_ = symbol;
        this->update();
    }

    /// Return the Glyph representing the checked state.
    auto get_checked_glyph() const -> Glyph const& { return checked_; }

    /// Return the Glyph representing the unchecked state.
    auto get_unchecked_glyph() const -> Glyph const& { return unchecked_; }

   protected:
    auto paint_event() -> bool override
    {
        Painter{*this}.put(this->is_checked() ? checked_ : unchecked_, 0, 0);
        return Widget::paint_event();
    }

    auto mouse_press_event(Mouse const& m) -> bool override
    {
        if (m.button == Mouse::Button::Left)
            this->toggle();
        return Widget::mouse_press_event(m);
    }

   private:
    bool is_checked_ = false;
    Glyph checked_;
    Glyph unchecked_;
};

/// Helper function to create an instance.
template <typename... Args>
auto checkbox(Args&&... args) -> std::unique_ptr<Checkbox>
{
    return std::make_unique<Checkbox>(std::forward<Args>(args)...);
}

class Labeled_checkbox : public Label_right<layout::Horizontal<>, Checkbox> {
   public:
    Checkbox& checkbox = Label_right::wrapped;

    sl::Signal<void()>& checked   = checkbox.checked;
    sl::Signal<void()>& unchecked = checkbox.unchecked;
    sl::Signal<void()>& toggled   = checkbox.toggled;

   public:
    Labeled_checkbox(Glyph_string label_ = "")
        : Label_right{{std::move(label_)}}
    {
        using namespace pipe;
        Label_right::label | on_mouse_press([&](auto) { checkbox.toggle(); });
        Label_right::padding | on_mouse_press([&](auto) { checkbox.toggle(); });
    }
};

/// Helper function to create an instance.
template <typename... Args>
auto labeled_checkbox(Args&&... args) -> std::unique_ptr<Labeled_checkbox>
{
    return std::make_unique<Labeled_checkbox>(std::forward<Args>(args)...);
}

}  // namespace ox

namespace ox::slot {

inline auto toggle(Checkbox& cb) -> sl::Slot<void()>
{
    return link_lifetimes([&cb] { cb.toggle(); }, cb);
}

inline auto check(Checkbox& cb) -> sl::Slot<void()>
{
    return link_lifetimes([&cb] { cb.check(); }, cb);
}

inline auto uncheck(Checkbox& cb) -> sl::Slot<void()>
{
    return link_lifetimes([&cb] { cb.uncheck(); }, cb);
}

}  // namespace ox::slot
#endif  // CATERM_WIDGET_WIDGETS_CHECKBOX_HPP
