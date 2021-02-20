#ifndef CATERM_WIDGET_WIDGET_SPINNER_HPP
#define CATERM_WIDGET_WIDGET_SPINNER_HPP
#include <cstddef>
#include <utility>

#include <caterm/painter/glyph_string.hpp>
#include <caterm/painter/painter.hpp>
#include <caterm/system/animation_engine.hpp>
#include <caterm/widget/widget.hpp>

namespace ox {

/// Single cell animated spinner.
class Spinner : public Widget {
   public:
    using Interval_t = Animation_engine::Interval_t;

   public:
    /// Each glyph in frames is a frame, offset is starting index into frames.
    explicit Spinner(Glyph_string frames,
                     Interval_t period = Interval_t{100},
                     int width         = 1,
                     int offset        = 0)
        : frames_{std::move(frames)},
          period_{period},
          width_{width},
          index_{offset}
    {
        height_policy.fixed(1);
        width_policy.fixed(width_);
    }

   public:
    void set_frames(Glyph_string frames) { frames_ = std::move(frames); }

    void set_period(Interval_t period)
    {
        if (started_) {
            this->stop();
            period_ = period;
            this->start();
        }
        else
            period_ = period;
    }

    void start()
    {
        if (started_)
            return;
        this->enable_animation(period_);
        started_ = true;
    }

    void stop()
    {
        this->disable_animation();
        started_ = false;
        this->update();
    }

   protected:
    auto paint_event(Painter& p) -> bool override
    {
        if (started_) {
            for (auto x = 0; x < width_; ++x)
                p.put(frames_[index_], {x, 0});
        }
        return Widget::paint_event(p);
    }

    auto timer_event() -> bool override
    {
        ++index_;
        if (index_ >= frames_.size())
            index_ = 0;
        this->update();
        return Widget::timer_event();
    }

   private:
    bool started_ = false;
    Glyph_string frames_;
    Interval_t period_;
    int width_;
    int index_;
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner(Args&&... args) -> std::unique_ptr<Spinner>
{
    return std::make_unique<Spinner>(std::forward<Args>(args)...);
}

/// Specific Spinners
struct Spinner_cycle : Spinner {
    Spinner_cycle(Interval_t period = Interval_t{100},
                  int width         = 1,
                  int offset        = 0)
        : Spinner{U"⠁⠈⠐⠠⢀⡀⠄⠂", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_cycle(Args&&... args)
    -> std::unique_ptr<Spinner_cycle>
{
    return std::make_unique<Spinner_cycle>(std::forward<Args>(args)...);
}

struct Spinner_cycle_ccw : Spinner {
    Spinner_cycle_ccw(Interval_t period = Interval_t{100},
                      int width         = 1,
                      int offset        = 0)
        : Spinner{U"⠁⠂⠄⡀⢀⠠⠐⠈", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_cycle_ccw(Args&&... args)
    -> std::unique_ptr<Spinner_cycle_ccw>
{
    return std::make_unique<Spinner_cycle_ccw>(std::forward<Args>(args)...);
}

struct Spinner_fall : Spinner {
    Spinner_fall(Interval_t period = Interval_t{100},
                 int width         = 1,
                 int offset        = 0)
        : Spinner{U"⠁⠂⠄⡀⡈⡐⡠⣀⣁⣂⣄⣌⣔⣤⣥⣦⣮⣶⣷⣿", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_fall(Args&&... args) -> std::unique_ptr<Spinner_fall>
{
    return std::make_unique<Spinner_fall>(std::forward<Args>(args)...);
}

struct Spinner_fall_two : Spinner {
    Spinner_fall_two(Interval_t period = Interval_t{100},
                     int width         = 1,
                     int offset        = 0)
        : Spinner{U" ⠁⠉⠋⠛⠟⠿⡿⣿⣿⣿⣿⣷⣶⣦⣤⣄⣀⡀ ", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_fall_two(Args&&... args)
    -> std::unique_ptr<Spinner_fall_two>
{
    return std::make_unique<Spinner_fall_two>(std::forward<Args>(args)...);
}

struct Spinner_fall_three : Spinner {
    Spinner_fall_three(Interval_t period = Interval_t{100},
                       int width         = 1,
                       int offset        = 0)
        : Spinner{U"   ⠁⠂⠄⡀⡈⡐⡠⣀⣁⣂⣄⣌⣔⣤⣥⣦⣮⣶⣷⣿⣿⣿⣿⣿⣿⡿⠿⢟⠟⡛⠛⠫⢋⠋⠍⡉⠉⠑⠡⢁⠁⠂⠄⡀   ", period,
                  width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_fall_three(Args&&... args)
    -> std::unique_ptr<Spinner_fall_three>
{
    return std::make_unique<Spinner_fall_three>(std::forward<Args>(args)...);
}

struct Spinner_rise : Spinner {
    Spinner_rise(Interval_t period = Interval_t{100},
                 int width         = 1,
                 int offset        = 0)
        : Spinner{U"⡀⠄⠂⠁⢁⠡⠑⠉⡉⠍⠋⢋⠫⠛⡛⠟⢟⠿⡿⣿", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_rise(Args&&... args) -> std::unique_ptr<Spinner_rise>
{
    return std::make_unique<Spinner_rise>(std::forward<Args>(args)...);
}

struct Spinner_rise_two : Spinner {
    Spinner_rise_two(Interval_t period = Interval_t{100},
                     int width         = 1,
                     int offset        = 0)
        : Spinner{U"    ⡀⣀⣄⣤⣦⣶⣷⣿⣿⣿⣿⡿⠿⠟⠛⠋⠉⠁    ", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_rise_two(Args&&... args)
    -> std::unique_ptr<Spinner_rise_two>
{
    return std::make_unique<Spinner_rise_two>(std::forward<Args>(args)...);
}

struct Spinner_rise_three : Spinner {
    Spinner_rise_three(Interval_t period = Interval_t{100},
                       int width         = 1,
                       int offset        = 0)
        : Spinner{U"   ⡀⠄⠂⠁⢁⠡⠑⠉⡉⠍⠋⢋⠫⠛⡛⠟⢟⠿⡿⣿⣿⣿⣿⣿⣿⣷⣶⣮⣦⣥⣤⣔⣌⣄⣂⣁⣀⡠⡐⡈⡀⠄⠂⠁   ", period,
                  width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_rise_three(Args&&... args)
    -> std::unique_ptr<Spinner_rise_three>
{
    return std::make_unique<Spinner_rise_three>(std::forward<Args>(args)...);
}

struct Spinner_fill : Spinner {
    Spinner_fill(Interval_t period = Interval_t{100},
                 int width         = 1,
                 int offset        = 0)
        : Spinner{U"⡀⣀⣄⣤⣦⣶⣷⣿", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_fill(Args&&... args) -> std::unique_ptr<Spinner_fill>
{
    return std::make_unique<Spinner_fill>(std::forward<Args>(args)...);
}

struct Spinner_top_fill : Spinner {
    Spinner_top_fill(Interval_t period = Interval_t{100},
                     int width         = 1,
                     int offset        = 0)
        : Spinner{U"⠁⠉⠋⠛⠟⠿⡿⣿", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_top_fill(Args&&... args)
    -> std::unique_ptr<Spinner_top_fill>
{
    return std::make_unique<Spinner_top_fill>(std::forward<Args>(args)...);
}

struct Spinner_tail : Spinner {
    Spinner_tail(Interval_t period = Interval_t{100},
                 int width         = 1,
                 int offset        = 0)
        : Spinner{U"⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_tail(Args&&... args) -> std::unique_ptr<Spinner_tail>
{
    return std::make_unique<Spinner_tail>(std::forward<Args>(args)...);
}

struct Spinner_switch : Spinner {
    Spinner_switch(Interval_t period = Interval_t{100},
                   int width         = 1,
                   int offset        = 0)
        : Spinner{U"⢹⢺⢼⣸⣇⡧⡗⡏", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
auto spinner_switch(Args&&... args) -> std::unique_ptr<Spinner_switch>
{
    return std::make_unique<Spinner_switch>(std::forward<Args>(args)...);
}

struct Spinner_chase : Spinner {
    Spinner_chase(Interval_t period = Interval_t{100},
                  int width         = 1,
                  int offset        = 0)
        : Spinner{U"⢄⢂⢁⡁⡈⡐⡠", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_chase(Args&&... args)
    -> std::unique_ptr<Spinner_chase>
{
    return std::make_unique<Spinner_chase>(std::forward<Args>(args)...);
}

struct Spinner_line : Spinner {
    Spinner_line(Interval_t period = Interval_t{100},
                 int width         = 1,
                 int offset        = 0)
        : Spinner{U"-\\|/", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_line(Args&&... args) -> std::unique_ptr<Spinner_line>
{
    return std::make_unique<Spinner_line>(std::forward<Args>(args)...);
}

struct Spinner_block_cycle : Spinner {
    Spinner_block_cycle(Interval_t period = Interval_t{100},
                        int width         = 1,
                        int offset        = 0)
        : Spinner{U"▖▘▝▗", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_block_cycle(Args&&... args)
    -> std::unique_ptr<Spinner_block_cycle>
{
    return std::make_unique<Spinner_block_cycle>(std::forward<Args>(args)...);
}

struct Spinner_fade : Spinner {
    Spinner_fade(Interval_t period = Interval_t{100},
                 int width         = 1,
                 int offset        = 0)
        : Spinner{U"         ░░▒▓▓██████████████████▓▓▒░░         ", period,
                  width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_fade(Args&&... args) -> std::unique_ptr<Spinner_fade>
{
    return std::make_unique<Spinner_fade>(std::forward<Args>(args)...);
}

/// Best used with multiple spinners horizontally, each offset one from neighbor
struct Spinner_fade_trail : Spinner {
    Spinner_fade_trail(Interval_t period = Interval_t{100},
                       int width         = 1,
                       int offset        = 0)
        : Spinner{U"⢀⢀⠠⠠⢀⢀⠠⠠⢀░░▒▓▓██████████████████▓▓▒░░⢀⢀⠠⠠⢀⢀⠠⠠⢀", period,
                  width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_fade_trail(Args&&... args)
    -> std::unique_ptr<Spinner_fade_trail>
{
    return std::make_unique<Spinner_fade_trail>(std::forward<Args>(args)...);
}

struct Spinner_quarter_circles : Spinner {
    Spinner_quarter_circles(Interval_t period = Interval_t{100},
                            int width         = 1,
                            int offset        = 0)
        : Spinner{U"◜◝◞◟", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_quarter_circles(Args&&... args)
    -> std::unique_ptr<Spinner_quarter_circles>
{
    return std::make_unique<Spinner_quarter_circles>(
        std::forward<Args>(args)...);
}

struct Spinner_triangles : Spinner {
    Spinner_triangles(Interval_t period = Interval_t{100},
                      int width         = 1,
                      int offset        = 0)
        : Spinner{U"◤◥◢◣", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_triangles(Args&&... args)
    -> std::unique_ptr<Spinner_triangles>
{
    return std::make_unique<Spinner_triangles>(std::forward<Args>(args)...);
}

struct Spinner_empty_triangles : Spinner {
    Spinner_empty_triangles(Interval_t period = Interval_t{100},
                            int width         = 1,
                            int offset        = 0)
        : Spinner{U"◸◹◿◺", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_empty_triangles(Args&&... args)
    -> std::unique_ptr<Spinner_empty_triangles>
{
    return std::make_unique<Spinner_empty_triangles>(
        std::forward<Args>(args)...);
}

struct Spinner_clock : Spinner {
    Spinner_clock(Interval_t period = Interval_t{100},
                  int width         = 1,
                  int offset        = 0)
        : Spinner{U"◴◷◶◵", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_clock(Args&&... args)
    -> std::unique_ptr<Spinner_clock>
{
    return std::make_unique<Spinner_clock>(std::forward<Args>(args)...);
}

struct Spinner_box : Spinner {
    Spinner_box(Interval_t period = Interval_t{100},
                int width         = 1,
                int offset        = 0)
        : Spinner{U"▤▧▥▨", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_box(Args&&... args) -> std::unique_ptr<Spinner_box>
{
    return std::make_unique<Spinner_box>(std::forward<Args>(args)...);
}

struct Spinner_cross : Spinner {
    Spinner_cross(Interval_t period = Interval_t{100},
                  int width         = 1,
                  int offset        = 0)
        : Spinner{U"┽╀┾╁", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_cross(Args&&... args)
    -> std::unique_ptr<Spinner_cross>
{
    return std::make_unique<Spinner_cross>(std::forward<Args>(args)...);
}

struct Spinner_vertical_pass : Spinner {
   public:
    Spinner_vertical_pass(Interval_t period = Interval_t{100},
                          int width         = 1,
                          int offset        = 0)
        : Spinner{first().append(second()).append(U" "), period, width, offset}
    {}

   private:
    [[nodiscard]] auto first() -> Glyph_string { return U"▁▂▃▄▅▆▇█"; }

    [[nodiscard]] auto second() -> Glyph_string
    {
        auto result = first();
        result.add_traits(Trait::Inverse);
        return result;
    }
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_vertical_pass(Args&&... args)
    -> std::unique_ptr<Spinner_vertical_pass>
{
    return std::make_unique<Spinner_vertical_pass>(std::forward<Args>(args)...);
}

struct Spinner_horizontal_pass : Spinner {
   public:
    Spinner_horizontal_pass(Interval_t period = Interval_t{100},
                            int width         = 1,
                            int offset        = 0)
        : Spinner{first().append(second()).append(U" "), period, width, offset}
    {}

   private:
    [[nodiscard]] auto first() -> Glyph_string { return U"▏▎▍▌▋▊▉█"; }

    [[nodiscard]] auto second() -> Glyph_string
    {
        auto result = first();
        result.add_traits(Trait::Inverse);
        return result;
    }
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_horizontal_pass(Args&&... args)
    -> std::unique_ptr<Spinner_horizontal_pass>
{
    return std::make_unique<Spinner_horizontal_pass>(
        std::forward<Args>(args)...);
}

struct Spinner_bump : Spinner {
    Spinner_bump(Interval_t period = Interval_t{100},
                 int width         = 1,
                 int offset        = 0)
        : Spinner{U" ▁▂▃▄▅▆▇█▇▆▅▄▃▂▁", period, width, offset}
    {}
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto spinner_bump(Args&&... args) -> std::unique_ptr<Spinner_bump>
{
    return std::make_unique<Spinner_bump>(std::forward<Args>(args)...);
}

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGET_SPINNER_HPP
