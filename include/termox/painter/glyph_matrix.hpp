#ifndef CATERM_PAINTER_GLYPH_MATRIX_HPP
#define CATERM_PAINTER_GLYPH_MATRIX_HPP
#include <cstddef>
#include <vector>

#include <caterm/painter/glyph.hpp>

namespace ox {

/// Holds a matrix of Glyphs, provides simple access by indices.
class Glyph_matrix {
   public:
    /// Construct with a set width and height, or defaults to 0 for each.
    /** Glyphs default constructed(space char with no colors or traits). */
    explicit Glyph_matrix(std::size_t width = 0, std::size_t height = 0)
        : matrix_{height, std::vector<Glyph>(width, U' ')}
    {}

    /// Resize the width and height of the matrix.
    /** New Glyphs will be default constructed, Glyphs no longer within the
     *  bounds of the matrix will be destructed. */
    void resize(std::size_t width, std::size_t height);

    /// Remove all Glyphs from the matrix and set width/height to 0.
    void clear() { matrix_.clear(); }

    /// Return the width of the matrix.
    auto width() const -> std::size_t
    {
        return matrix_.empty() ? 0 : matrix_.at(0).size();
    }

    /// Return the height of the matrix.
    std::size_t height() const { return matrix_.size(); }

    /// Glyph access operator. (0, 0) is top left. x grows south and y east.
    /** Provides no bounds checking. */
    auto operator()(std::size_t x, std::size_t y) -> Glyph&
    {
        return matrix_[y][x];
    }

    /// Glyph access operator. (0, 0) is top left. x grows south and y east.
    /** Provides no bounds checking. */
    auto operator()(std::size_t x, std::size_t y) const -> Glyph
    {
        return matrix_[y][x];
    }

    /// Glyph access operator. (0, 0) is top left. x grows south and y east.
    /** Has bounds checking and throws std::out_of_range if not within range. */
    auto at(std::size_t x, std::size_t y) -> Glyph&
    {
        return matrix_.at(y).at(x);
    }

    /// Glyph access operator. (0, 0) is top left. x grows south and y east.
    /** Has bounds checking and throws std::out_of_range if not within range. */
    auto at(std::size_t x, std::size_t y) const -> Glyph
    {
        return matrix_.at(y).at(x);
    }

   private:
    std::vector<std::vector<Glyph>> matrix_;
};

}  // namespace ox
#endif  // CATERM_PAINTER_GLYPH_MATRIX_HPP
