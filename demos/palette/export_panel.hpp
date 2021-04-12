#ifndef CATERM_DEMOS_PALETTE_EXPORT_PANEL_HPP
#define CATERM_DEMOS_PALETTE_EXPORT_PANEL_HPP
#include <caterm/widget/layouts/vertical.hpp>
#include <caterm/widget/widgets/confirm_button.hpp>
#include <caterm/widget/widgets/textline.hpp>

namespace palette {

/// Holds interface to export the Palette as a C++ header file.
class Export_panel : public ox::layout::Vertical<> {
   public:
    Export_panel();

   private:
    ox::Textline& name_edit_ = make_child<ox::Textline>(U"Enter name...");

    ox::Confirm_button& export_btn_ =
        make_child<ox::Confirm_button>(U"Export Palette");
};

}  // namespace palette
#endif  // CATERM_DEMOS_PALETTE_EXPORT_PANEL_HPP
