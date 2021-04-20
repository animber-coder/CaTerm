#ifndef CATERM_WIDGET_WIDGETS_LABEL_HPP
#define CATERM_WIDGET_WIDGETS_LABEL_HPP
#include <memory>
#include <utility>

#include <caterm/painter/glyph_string.hpp>
#include <caterm/widget/align.hpp>
#include <caterm/widget/growth.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/opposite.hpp>
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/tuple.hpp>

namespace ox {

/// A single line of text with alignment, non-editable.
/** Can be either Vertical or Horizontal by passing in a Layout type. */
template <template <typename> typename Layout_t>
class Label : public Widget {
    static_assert(layout::is_vertical_v<Layout_t<Widget>> ||
                  layout::is_horizontal_v<Layout_t<Widget>>);

   public:
    struct Parameters {
        Glyph_string text      = Glyph_string{U""};
        Align alignment        = Align::Left;
        int extra_left         = 0;
        int extra_right        = 0;
        Growth growth_strategy = Growth::Static;
    };

   public:
    /// Create a new Label Widget.
    /** \param text            The initial text used for the display.
     *  \param alignment       The placement of the text on the Label.
     *  \param extra_left      Align::Center takes this into account.
     *  \param extra_right     Align::Center takes this into account
     *  \param growth_strategy If the Label is resized to fit the text or not.
     */
    explicit Label(Glyph_string text      = U"",
                   Align alignment        = Align::Left,
                   int extra_left         = 0,
                   int extra_right        = 0,
                   Growth growth_strategy = Growth::Static)
        : text_{std::move(text)},
          alignment_{alignment},
          extra_left_{extra_left},
          extra_right_{extra_right},
          growth_strategy_{growth_strategy}
    {
        if constexpr (is_vertical)
            *this | pipe::fixed_width(1);
        else
            *this | pipe::fixed_height(1);

        if (growth_strategy_ == Growth::Dynamic) {
            if constexpr (is_vertical)
                *this | pipe::fixed_height(text_.size());
            else
                *this | pipe::fixed_width(text_.size());
        }
    }

    /// Construct directly with Parameters object.
    explicit Label(Parameters p)
        : Label(std::move(p.text),
                p.alignment,
                p.extra_left,
                p.extra_right,
                p.growth_strategy)
    {}

   public:
    /// Set text contents of Label and update display.
    void set_text(Glyph_string text)
    {
        if (growth_strategy_ == Growth::Dynamic) {
            if constexpr (is_vertical) {
                if (text.size() != this->outer_height())
                    *this | pipe::fixed_height(text.size());
            }
            else {
                if (text.size() != this->outer_width())
                    *this | pipe::fixed_width(text.size());
            }
        }
        text_ = std::move(text);
        this->update_offset();
    }

    /// Return the text given to set_text().
    [[nodiscard]] auto text() const noexcept -> Glyph_string const&
    {
        return text_;
    }

    /// Set text alignment of Label and update display.
    void set_alignment(Align x)
    {
        alignment_ = x;
        this->update_offset();
    }

    /// Return the Align given to set_alignment().
    [[nodiscard]] auto alignment() const noexcept -> Align
    {
        return alignment_;
    }

    /// Inform Label about space to left of Label for centered text offset.
    void set_extra_left(int x)
    {
        extra_left_ = x;
        this->update_offset();
    }

    /// Return the amount given to set_extra_left().
    [[nodiscard]] auto extra_left() const noexcept -> int
    {
        return extra_left_;
    }

    /// Inform Label about space to right of Label for centered text offset.
    void set_extra_right(int x)
    {
        extra_right_ = x;
        this->update_offset();
    }

    /// Return the amount given to set_extra_right().
    [[nodiscard]] auto extra_right() const noexcept -> int
    {
        return extra_right_;
    }

    /// Enable/Disable Dynamic size, where the Label's size is the text length.
    void set_growth_strategy(Growth type)
    {
        growth_strategy_ = type;
        if (growth_strategy_ == Growth::Dynamic) {
            if constexpr (is_vertical)
                *this | pipe::fixed_height(text_.size());
            else
                *this | pipe::fixed_width(text_.size());
        }
    }

    /// Return the value given to set_growth_strategy().
    [[nodiscard]] auto growth_strategy() const noexcept -> Growth
    {
        return growth_strategy_;
    }

   protected:
    auto paint_event(Painter& p) -> bool override
    {
        if constexpr (is_vertical)
            this->paint_vertical(p);
        else
            this->paint_horizontal(p);
        return Widget::paint_event(p);
    }

    auto resize_event(Area new_size, Area old_size) -> bool override
    {
        this->update_offset();
        return Widget::resize_event(new_size, old_size);
    }

   private:
    inline static auto constexpr is_vertical =
        layout::is_vertical_v<Layout_t<Widget>>;

    Glyph_string text_;
    Align alignment_;
    int extra_left_;
    int extra_right_;
    Growth growth_strategy_;

    int offset_ = 0;

   private:
    /// Update the internal offset_ value to account for new settings/state
    void update_offset()
    {
        auto const box_length = [this] {
            if constexpr (is_vertical)
                return this->height();
            else
                return this->width();
        }();

        offset_ = this->find_offset(text_.size(), box_length, extra_left_,
                                    extra_right_);
        this->update();
    }

    void paint_vertical(Painter& p)
    {
        for (auto i = 0; i < text_.size() && i < this->height(); ++i)
            p.put(text_[i], {0, offset_ + i});
    }

    void paint_horizontal(Painter& p) { p.put(text_, {offset_, 0}); }

    /// Find the text's first Glyph placement along the length of the Widget.
    [[nodiscard]] auto find_offset(int text_length,
                                   int box_length,
                                   int extra_left,
                                   int extra_right) -> int
    {
        switch (alignment_) {
            case Align::Left:
            case Align::Top: return left_top_offset();

            case Align::Center:
                return apply_origin_offset(
                    center_offset(text_length,
                                  box_length + extra_left + extra_right),
                    extra_left);

            case Align::Right:
            case Align::Bottom:
                return right_bottom_offset(text_length, box_length);
        }
        return 0;
    }

    [[nodiscard]] static auto left_top_offset() -> int { return 0; }

    [[nodiscard]] static auto center_offset(int text_length, int box_length)
        -> int
    {
        return text_length > box_length ? 0 : (box_length - text_length) / 2;
    }

    [[nodiscard]] static auto right_bottom_offset(int text_length,
                                                  int box_length) -> int
    {
        return text_length > box_length ? 0 : box_length - text_length;
    }

    /// Offsets a given \p position by the extra length parameters
    [[nodiscard]] static auto apply_origin_offset(int position, int left) -> int
    {
        position -= position < left ? position : left;
        return position;
    }
};

/// Helper function to create a Label instance.
template <template <typename> typename Layout_t>
[[nodiscard]] auto label(Glyph_string text      = U"",
                         Align alignment        = Align::Left,
                         int extra_left         = 0,
                         int extra_right        = 0,
                         Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<Label<Layout_t>>
{
    return std::make_unique<Label<Layout_t>>(
        std::move(text), alignment, extra_left, extra_right, growth_strategy);
}

/// Helper function to create a Label instance.
template <template <typename> typename Layout_t>
[[nodiscard]] auto label(typename Label<Layout_t>::Parameters parameters)
    -> std::unique_ptr<Label<Layout_t>>
{
    return std::make_unique<Label<Layout_t>>(std::move(parameters));
}

/// Horizontal Label Widget
using HLabel = Label<layout::Horizontal>;

/// Helper function to create an HLabel instance.
[[nodiscard]] inline auto hlabel(Glyph_string text      = U"",
                                 Align alignment        = Align::Left,
                                 int extra_left         = 0,
                                 int extra_right        = 0,
                                 Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<HLabel>
{
    return std::make_unique<HLabel>(std::move(text), alignment, extra_left,
                                    extra_right, growth_strategy);
}

/// Helper function to create an HLabel instance.
[[nodiscard]] inline auto hlabel(HLabel::Parameters parameters)
    -> std::unique_ptr<HLabel>
{
    return std::make_unique<HLabel>(std::move(parameters));
}

/// Vertical Label Widget
using VLabel = Label<layout::Vertical>;

/// Helper function to create a VLabel instance.
[[nodiscard]] inline auto vlabel(Glyph_string text      = U"",
                                 Align alignment        = Align::Left,
                                 int extra_left         = 0,
                                 int extra_right        = 0,
                                 Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<VLabel>
{
    return std::make_unique<VLabel>(std::move(text), alignment, extra_left,
                                    extra_right, growth_strategy);
}

/// Helper function to create a VLabel instance.
[[nodiscard]] inline auto vlabel(VLabel::Parameters parameters)
    -> std::unique_ptr<VLabel>
{
    return std::make_unique<VLabel>(std::move(parameters));
}

}  // namespace ox

// -----------------------------------------------------------------------------

namespace ox::detail {

/// Wraps a Widget_t object with a label.
/** Wrapper_layout is the layout of *this, if label_last is true, the Label is
 *  after the wrapped Widget_t. */
template <template <typename> typename Label_layout,
          typename Widget_t,
          template <typename>
          typename Wrapper_layout,
          bool label_last>
class Label_wrapper : public Wrapper_layout<Widget> {
   private:
    using Label_t      = Label<Label_layout>;
    using Padded_label = Tuple<layout::Opposite_t<Label_layout<Widget>>,
                               Widget,
                               Label_t,
                               Widget>;

   public:
    // Instead of inheriting Label_t::Parmeters, because default alignment.
    struct Parameters {
        Glyph_string text      = Glyph_string{U""};
        Align alignment        = label_last ? Align::Left : Align::Right;
        int extra_left         = 0;
        int extra_right        = 0;
        Growth growth_strategy = Growth::Static;
    };

   public:
    Label_t& label;
    Widget& padding = this->template make_child() | padding_policy();
    Widget_t& wrapped;

   public:
    /// Construct a new Label and wrapped Widget_t.
    /** Only takes Label constructor args, if you need to pass in args to the
     *  wrapped Widget_t, then use the Label::Parameters overload. */
    explicit Label_wrapper(Glyph_string text      = U"",
                           Align alignment        = Align::Left,
                           int extra_left         = 0,
                           int extra_right        = 0,
                           Growth growth_strategy = Growth::Static)
        : Label_wrapper{{std::move(text), alignment, extra_left, extra_right,
                         growth_strategy}}
    {}

    /// Constructs Label with given parameters, and Widget_t with args...
    template <typename... Args>
    explicit Label_wrapper(Parameters p, Args&&... args)
        : label{this->template make_child<Padded_label>(
                        {{},
                         {std::move(p.text), p.alignment, p.extra_left,
                          p.extra_right, p.growth_strategy},
                         {}})
                    .template get<1>()},
          wrapped{
              this->template make_child<Widget_t>(std::forward<Args>(args)...)}
    {
        if constexpr (layout::is_vertical_v<Wrapper_layout<Widget>>)
            this->width_policy = wrapped.width_policy;
        else
            this->height_policy = wrapped.height_policy;

        *this | pipe::on_focus_in([this] { System::set_focus(wrapped); });

        if constexpr (label_last)
            this->swap_children(0, 2);
    }

   private:
    [[nodiscard]] auto padding_policy()
    {
        if constexpr (layout::is_vertical_v<Wrapper_layout<Widget>>)
            return pipe::fixed_height(0);
        else
            return pipe::fixed_width(1);
    }
};

}  // namespace ox::detail

namespace ox {

// -----------------------------------------------------------------------------

/// Wraps a Widget_t object with a Label on the left.
template <template <typename> typename Label_layout_t, typename Widget_t>
using Label_left =
    detail::Label_wrapper<Label_layout_t, Widget_t, layout::Horizontal, false>;

// Helper function to create a Label_left instance.
template <template <typename> typename Layout_t,
          typename Widget_t,
          typename... Args>
[[nodiscard]] auto label_left(typename Label<Layout_t>::Parameters p,
                              Args&&... args)
    -> std::unique_ptr<Label_left<Layout_t, Widget_t>>
{
    return std::make_unique<Label_left<Layout_t, Widget_t>>(
        std::move(p), std::forward<Args>(args)...);
}

/// Helper function to create a Label_left instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <template <typename> typename Layout_t, typename Widget_t>
[[nodiscard]] auto label_left(Glyph_string text      = U"",
                              Align alignment        = Align::Left,
                              int extra_left         = 0,
                              int extra_right        = 0,
                              Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<Label_left<Layout_t, Widget_t>>
{
    return label_left<Layout_t, Widget_t>(typename Label<Layout_t>::Parameters{
        std::move(text), alignment, extra_left, extra_right, growth_strategy});
}

/// Wraps a Widget_t object with an HLabel on the left.
template <typename Widget_t>
using HLabel_left = Label_left<layout::Horizontal, Widget_t>;

// Helper function to create an HLabel_left instance.
template <typename Widget_t, typename... Args>
[[nodiscard]] auto hlabel_left(HLabel::Parameters p, Args&&... args)
    -> std::unique_ptr<HLabel_left<Widget_t>>
{
    return std::make_unique<HLabel_left<Widget_t>>(std::move(p),
                                                   std::forward<Args>(args)...);
}

/// Helper function to create an HLabel_left instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <typename Widget_t>
[[nodiscard]] auto hlabel_left(Glyph_string text      = U"",
                               Align alignment        = Align::Left,
                               int extra_left         = 0,
                               int extra_right        = 0,
                               Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<HLabel_left<Widget_t>>
{
    return hlabel_left<Widget_t>(HLabel::Parameters{
        std::move(text), alignment, extra_left, extra_right, growth_strategy});
}

/// Wraps a Widget_t object with a VLabel on the left.
template <typename Widget_t>
using VLabel_left = Label_left<layout::Vertical, Widget_t>;

// Helper function to create a VLabel_left instance.
template <typename Widget_t, typename... Args>
[[nodiscard]] auto vlabel_left(VLabel::Parameters p, Args&&... args)
    -> std::unique_ptr<VLabel_left<Widget_t>>
{
    return std::make_unique<VLabel_left<Widget_t>>(std::move(p),
                                                   std::forward<Args>(args)...);
}

/// Helper function to create a VLabel_left instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <typename Widget_t>
[[nodiscard]] auto vlabel_left(Glyph_string text      = U"",
                               Align alignment        = Align::Left,
                               int extra_left         = 0,
                               int extra_right        = 0,
                               Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<VLabel_left<Widget_t>>
{
    return vlabel_left<Widget_t>(VLabel::Parameters{
        std::move(text), alignment, extra_left, extra_right, growth_strategy});
}

/// Wraps a Widget_t object with a Label on the right.
template <template <typename> typename Label_layout_t, typename Widget_t>
using Label_right =
    detail::Label_wrapper<Label_layout_t, Widget_t, layout::Horizontal, true>;

/// Helper function to create a Label_right instance.
template <template <typename> typename Layout_t,
          typename Widget_t,
          typename... Args>
[[nodiscard]] auto label_right(typename Label<Layout_t>::Parameters p,
                               Args&&... args)
    -> std::unique_ptr<Label_right<Layout_t, Widget_t>>
{
    return std::make_unique<Label_right<Layout_t, Widget_t>>(
        std::move(p), std::forward<Args>(args)...);
}

/// Helper function to create a Label_right instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <template <typename> typename Layout_t, typename Widget_t>
[[nodiscard]] auto label_right(Glyph_string text      = U"",
                               Align alignment        = Align::Left,
                               int extra_left         = 0,
                               int extra_right        = 0,
                               Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<Label_left<Layout_t, Widget_t>>
{
    return label_right(typename Label<Layout_t>::Parameters{
        std::move(text), alignment, extra_left, extra_right, growth_strategy});
}

/// Wraps a Widget_t object with an HLabel on the right.
template <typename Widget_t>
using HLabel_right = Label_right<layout::Horizontal, Widget_t>;

// Helper function to create a HLabel_right instance.
template <typename Widget_t, typename... Args>
[[nodiscard]] auto hlabel_right(HLabel::Parameters p, Args&&... args)
    -> std::unique_ptr<HLabel_right<Widget_t>>
{
    return std::make_unique<HLabel_right<Widget_t>>(
        std::move(p), std::forward<Args>(args)...);
}

/// Helper function to create a HLabel_right instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <typename Widget_t>
[[nodiscard]] auto hlabel_right(Glyph_string text      = U"",
                                Align alignment        = Align::Left,
                                int extra_left         = 0,
                                int extra_right        = 0,
                                Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<HLabel_right<Widget_t>>
{
    return hlabel_right<Widget_t>(HLabel::Parameters{
        std::move(text), alignment, extra_left, extra_right, growth_strategy});
}

/// Wraps a Widget_t object with a VLabel on the right.
template <typename Widget_t>
using VLabel_right = Label_right<layout::Vertical, Widget_t>;

// Helper function to create a VLabel_right instance.
template <typename Widget_t, typename... Args>
[[nodiscard]] auto vlabel_right(VLabel::Parameters p, Args&&... args)
    -> std::unique_ptr<VLabel_right<Widget_t>>
{
    return std::make_unique<VLabel_right<Widget_t>>(
        std::move(p), std::forward<Args>(args)...);
}

/// Helper function to create a VLabel_right instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <typename Widget_t>
[[nodiscard]] auto vlabel_right(Glyph_string text      = U"",
                                Align alignment        = Align::Left,
                                int extra_left         = 0,
                                int extra_right        = 0,
                                Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<VLabel_right<Widget_t>>
{
    return vlabel_right<Widget_t>(VLabel::Parameters{
        std::move(text), alignment, extra_left, extra_right, growth_strategy});
}

/// Wraps a Widget_t object with a Label on the top.
template <template <typename> typename Label_layout_t, typename Widget_t>
using Label_top =
    detail::Label_wrapper<Label_layout_t, Widget_t, layout::Vertical, false>;

/// Helper function to create a Label_top instance.
template <template <typename> typename Layout_t,
          typename Widget_t,
          typename... Args>
[[nodiscard]] auto label_top(typename Label<Layout_t>::Parameters p,
                             Args&&... args)
    -> std::unique_ptr<Label_top<Layout_t, Widget_t>>
{
    return std::make_unique<Label_top<Layout_t, Widget_t>>(
        std::move(p), std::forward<Args>(args)...);
}

/// Helper function to create a Label_top instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <template <typename> typename Layout_t, typename Widget_t>
[[nodiscard]] auto label_top(Glyph_string text      = U"",
                             Align alignment        = Align::Left,
                             int extra_top          = 0,
                             int extra_bottom       = 0,
                             Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<Label_left<Layout_t, Widget_t>>
{
    return label_top(typename Label<Layout_t>::Parameters{
        std::move(text), alignment, extra_top, extra_bottom, growth_strategy});
}

/// Wraps a Widget_t object with a VLabel on the top.
template <typename Widget_t>
using VLabel_top = Label_top<layout::Vertical, Widget_t>;

// Helper function to create a VLabel_top instance.
template <typename Widget_t, typename... Args>
[[nodiscard]] auto vlabel_top(VLabel::Parameters p, Args&&... args)
    -> std::unique_ptr<VLabel_top<Widget_t>>
{
    return std::make_unique<VLabel_top<Widget_t>>(std::move(p),
                                                  std::forward<Args>(args)...);
}

/// Helper function to create a VLabel_top instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <typename Widget_t>
[[nodiscard]] auto vlabel_top(Glyph_string text      = U"",
                              Align alignment        = Align::Left,
                              int extra_left         = 0,
                              int extra_right        = 0,
                              Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<VLabel_top<Widget_t>>
{
    return vlabel_top<Widget_t>(VLabel::Parameters{
        std::move(text), alignment, extra_left, extra_right, growth_strategy});
}

/// Wraps a Widget_t object with an HLabel on the top.
template <typename Widget_t>
using HLabel_top = Label_top<layout::Horizontal, Widget_t>;

// Helper function to create an HLabel_top instance.
template <typename Widget_t, typename... Args>
[[nodiscard]] auto hlabel_top(HLabel::Parameters p, Args&&... args)
    -> std::unique_ptr<HLabel_top<Widget_t>>
{
    return std::make_unique<HLabel_top<Widget_t>>(std::move(p),
                                                  std::forward<Args>(args)...);
}

/// Helper function to create an HLabel_top instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <typename Widget_t>
[[nodiscard]] auto hlabel_top(Glyph_string text      = U"",
                              Align alignment        = Align::Left,
                              int extra_left         = 0,
                              int extra_right        = 0,
                              Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<HLabel_top<Widget_t>>
{
    return hlabel_top<Widget_t>(HLabel::Parameters{
        std::move(text), alignment, extra_left, extra_right, growth_strategy});
}

/// Wraps a Widget_t object with a Label on the bottom.
template <template <typename> typename Label_layout_t, typename Widget_t>
using Label_bottom =
    detail::Label_wrapper<Label_layout_t, Widget_t, layout::Vertical, true>;

/// Helper function to create a Label_bottom instance.
template <template <typename> typename Layout_t,
          typename Widget_t,
          typename... Args>
[[nodiscard]] auto label_bottom(typename Label<Layout_t>::Parameters p,
                                Args&&... args)
    -> std::unique_ptr<Label_bottom<Layout_t, Widget_t>>
{
    return std::make_unique<Label_bottom<Layout_t, Widget_t>>(
        std::move(p), std::forward<Args>(args)...);
}

/// Helper function to create a Label_bottom instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <template <typename> typename Layout_t, typename Widget_t>
[[nodiscard]] auto label_bottom(Glyph_string text      = U"",
                                Align alignment        = Align::Left,
                                int extra_top          = 0,
                                int extra_bottom       = 0,
                                Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<Label_left<Layout_t, Widget_t>>
{
    return label_bottom(typename Label<Layout_t>::Parameters{
        std::move(text), alignment, extra_top, extra_bottom, growth_strategy});
}

/// Wraps a Widget_t object with a VLabel on the bottom.
template <typename Widget_t>
using VLabel_bottom = Label_bottom<layout::Vertical, Widget_t>;

// Helper function to create a VLabel_bottom instance.
template <typename Widget_t, typename... Args>
[[nodiscard]] auto vlabel_bottom(VLabel::Parameters p, Args&&... args)
    -> std::unique_ptr<VLabel_bottom<Widget_t>>
{
    return std::make_unique<VLabel_bottom<Widget_t>>(
        std::move(p), std::forward<Args>(args)...);
}

/// Helper function to create a VLabel_bottom instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <typename Widget_t>
[[nodiscard]] auto vlabel_bottom(Glyph_string text      = U"",
                                 Align alignment        = Align::Left,
                                 int extra_left         = 0,
                                 int extra_right        = 0,
                                 Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<VLabel_bottom<Widget_t>>
{
    return vlabel_bottom<Widget_t>(VLabel::Parameters{
        std::move(text), alignment, extra_left, extra_right, growth_strategy});
}

/// Wraps a Widget_t object with an HLabel on the bottom.
template <typename Widget_t>
using HLabel_bottom = Label_bottom<layout::Horizontal, Widget_t>;

// Helper function to create an HLabel_bottom instance.
template <typename Widget_t, typename... Args>
[[nodiscard]] auto hlabel_bottom(HLabel::Parameters p, Args&&... args)
    -> std::unique_ptr<HLabel_bottom<Widget_t>>
{
    return std::make_unique<HLabel_bottom<Widget_t>>(
        std::move(p), std::forward<Args>(args)...);
}

/// Helper function to create an HLabel_bottom instance.
/** Only takes Label constructor args, if you need to pass in args to the
 *  wrapped Widget_t, then use the Label::Parameters overload. */
template <typename Widget_t>
[[nodiscard]] auto hlabel_bottom(Glyph_string text      = U"",
                                 Align alignment        = Align::Left,
                                 int extra_left         = 0,
                                 int extra_right        = 0,
                                 Growth growth_strategy = Growth::Static)
    -> std::unique_ptr<HLabel_bottom<Widget_t>>
{
    return hlabel_bottom<Widget_t>(HLabel::Parameters{
        std::move(text), alignment, extra_left, extra_right, growth_strategy});
}

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_LABEL_HPP
