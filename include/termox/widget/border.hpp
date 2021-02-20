#ifndef CATERM_WIDGET_BORDER_HPP
#define CATERM_WIDGET_BORDER_HPP
#include <caterm/painter/glyph.hpp>

namespace ox {

/// Provides representation of a Widget's visible, surrounding border.
class Border {
   private:
    /// Holds enabled state and appearance for a Border Segment.
    class Segment : public Glyph {
       public:
        /// Construct a Border Segment with \g for appearance.
        Segment(Glyph g) : Glyph{g} {}

        /// Enable the Segment to be displayable.
        void enable() { enabled_ = true; }

        /// Disable the Segment, making it non-displayable.
        void disable() { enabled_ = false; }

        /// Return whether or not the border is enabled.
        [[nodiscard]] auto is_enabled() const -> bool { return enabled_; }

        /// Can assign to this as if it is a Glyph.
        using Glyph::operator=;

       private:
        bool enabled_ = true;
    };

    /// Holds all 8 Segments that a Border is made up of.
    struct Segments {
        Segment north      = Glyph{U'─'};
        Segment south      = Glyph{U'─'};
        Segment east       = Glyph{U'│'};
        Segment west       = Glyph{U'│'};
        Segment north_west = Glyph{U'┌'};
        Segment north_east = Glyph{U'┐'};
        Segment south_west = Glyph{U'└'};
        Segment south_east = Glyph{U'┘'};

        /// Disable all Segments.
        void disable_all();

        /// Enable all corners.
        /** Corners are north_west, north_east, south_west, and south_east. */
        void enable_corners();

        /// Disable all corners.
        /** Corners are north_west, north_east, south_west, and south_east. */
        void disable_corners();

        /// Enable all sides.
        /** Sides are north, south, east, and west. */
        void enable_sides();

        /// Disable all sides.
        /** Sides are north, south, east, and west. */
        void disable_sides();
    };

   public:
    /// Contains the look/appearance and enabled state for each segment.
    Segments segments;

   public:
    /// Enable the Border.
    /** This will give it space within its Widget and make it displayable.
     *  Segments are only displayed if their Border is enabled. */
    void enable() { enabled_ = true; }

    /// Disable the Border.
    void disable() { enabled_ = false; }

    /// Return whether the border is enabled.
    [[nodiscard]] auto is_enabled() const -> bool { return enabled_; }

   private:
    bool enabled_ = false;
};
}  // namespace ox
#endif  // CATERM_WIDGET_BORDER_HPP
