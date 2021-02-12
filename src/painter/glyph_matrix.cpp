#include <caterm/painter/glyph_matrix.hpp>

#include <caterm/painter/glyph.hpp>
#include <caterm/widget/area.hpp>

namespace ox {

void Glyph_matrix::resize(Area area)
{
    matrix_.resize(area.height);
    matrix_.shrink_to_fit();
    for (auto& row : matrix_) {
        row.resize(area.width, U' ');
        row.shrink_to_fit();
    }
}

}  // namespace ox
