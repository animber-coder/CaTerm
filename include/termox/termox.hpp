#ifndef CATERM_CATERM_HPP
#define CATERM_CATERM_HPP

#include <signals_light/signal.hpp>

#include <caterm/common/mb_to_u32.hpp>
#include <caterm/common/u32_to_mb.hpp>

#include <caterm/painter/palette/amstrad_cpc.hpp>
#include <caterm/painter/palette/apple_ii.hpp>
#include <caterm/painter/palette/ashes.hpp>
#include <caterm/painter/palette/basic.hpp>
#include <caterm/painter/palette/basic8.hpp>
#include <caterm/painter/palette/cga.hpp>
#include <caterm/painter/palette/commodore_64.hpp>
#include <caterm/painter/palette/commodore_vic20.hpp>
#include <caterm/painter/palette/dawn_bringer16.hpp>
#include <caterm/painter/palette/dawn_bringer32.hpp>
#include <caterm/painter/palette/en4.hpp>
#include <caterm/painter/palette/gameboy.hpp>
#include <caterm/painter/palette/gameboy_pocket.hpp>
#include <caterm/painter/palette/macintosh_ii.hpp>
#include <caterm/painter/palette/msx.hpp>
#include <caterm/painter/palette/nes.hpp>
#include <caterm/painter/palette/savanna.hpp>
#include <caterm/painter/palette/secam.hpp>
#include <caterm/painter/palette/stormy6.hpp>
#include <caterm/painter/palette/teletext.hpp>
#include <caterm/painter/palette/thomson_m05.hpp>
#include <caterm/painter/palette/windows.hpp>
#include <caterm/painter/palette/windows_console.hpp>
#include <caterm/painter/palette/zx_spectrum.hpp>

#include <caterm/painter/brush.hpp>
#include <caterm/painter/color.hpp>
#include <caterm/painter/dynamic_colors.hpp>
#include <caterm/painter/glyph.hpp>
#include <caterm/painter/glyph_matrix.hpp>
#include <caterm/painter/glyph_string.hpp>
#include <caterm/painter/painter.hpp>
#include <caterm/painter/trait.hpp>

#include <caterm/system/animation_engine.hpp>
#include <caterm/system/event.hpp>
#include <caterm/system/event_loop.hpp>
#include <caterm/system/key.hpp>
#include <caterm/system/mouse.hpp>
#include <caterm/system/shortcuts.hpp>
#include <caterm/system/system.hpp>

#include <caterm/terminal/key_mode.hpp>
#include <caterm/terminal/mouse_mode.hpp>
#include <caterm/terminal/signals.hpp>
#include <caterm/terminal/terminal.hpp>

#include <caterm/widget/layouts/fixed.hpp>
#include <caterm/widget/layouts/float.hpp>
#include <caterm/widget/layouts/horizontal.hpp>
#include <caterm/widget/layouts/opposite.hpp>
#include <caterm/widget/layouts/passive.hpp>
#include <caterm/widget/layouts/selecting.hpp>
#include <caterm/widget/layouts/set.hpp>
#include <caterm/widget/layouts/stack.hpp>
#include <caterm/widget/layouts/vertical.hpp>

#include <caterm/widget/widgets/accordion.hpp>
#include <caterm/widget/widgets/banner.hpp>
#include <caterm/widget/widgets/button.hpp>
#include <caterm/widget/widgets/button_list.hpp>
#include <caterm/widget/widgets/checkbox.hpp>
#include <caterm/widget/widgets/color_select.hpp>
#include <caterm/widget/widgets/confirm_button.hpp>
#include <caterm/widget/widgets/cycle_box.hpp>
#include <caterm/widget/widgets/cycle_stack.hpp>
#include <caterm/widget/widgets/graph.hpp>
#include <caterm/widget/widgets/hideable.hpp>
#include <caterm/widget/widgets/label.hpp>
#include <caterm/widget/widgets/line.hpp>
#include <caterm/widget/widgets/line_edit.hpp>
#include <caterm/widget/widgets/log.hpp>
#include <caterm/widget/widgets/matrix_view.hpp>
#include <caterm/widget/widgets/menu.hpp>
#include <caterm/widget/widgets/menu_stack.hpp>
#include <caterm/widget/widgets/notify_light.hpp>
#include <caterm/widget/widgets/number_edit.hpp>
#include <caterm/widget/widgets/number_view.hpp>
#include <caterm/widget/widgets/read_file.hpp>
#include <caterm/widget/widgets/scrollbar.hpp>
#include <caterm/widget/widgets/selectable.hpp>
#include <caterm/widget/widgets/slider.hpp>
#include <caterm/widget/widgets/spinner.hpp>
#include <caterm/widget/widgets/text_view.hpp>
#include <caterm/widget/widgets/textbox.hpp>
#include <caterm/widget/widgets/tile.hpp>
#include <caterm/widget/widgets/titlebar.hpp>
#include <caterm/widget/widgets/toggle_button.hpp>
#include <caterm/widget/widgets/write_file.hpp>

#include <caterm/widget/align.hpp>
#include <caterm/widget/area.hpp>
#include <caterm/widget/array.hpp>
#include <caterm/widget/bordered.hpp>
#include <caterm/widget/boundary.hpp>
#include <caterm/widget/cursor.hpp>
#include <caterm/widget/focus_policy.hpp>
#include <caterm/widget/growth.hpp>
#include <caterm/widget/layout.hpp>
#include <caterm/widget/pair.hpp>
#include <caterm/widget/pipe.hpp>
#include <caterm/widget/point.hpp>
#include <caterm/widget/size_policy.hpp>
#include <caterm/widget/tuple.hpp>
#include <caterm/widget/widget.hpp>
#include <caterm/widget/widget_slots.hpp>

#endif  // CATERM_CATERM_HPP
