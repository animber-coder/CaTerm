#include <cppurses/painter/detail/extended_char.hpp>

#include <map>

#include <ncurses.h>

namespace cppurses {
namespace detail {

const std::map<wchar_t, chtype>& get_ext_chars(){
    static const std::map<wchar_t, chtype> extended_chars{
        {L'┌', ACS_ULCORNER},   {L'┍', ACS_ULCORNER},   {L'┎', ACS_ULCORNER},
        {L'┏', ACS_ULCORNER},   {L'╒', ACS_ULCORNER},   {L'╓', ACS_ULCORNER},
        {L'╔', ACS_ULCORNER},   {L'╭', ACS_ULCORNER},

        {L'└', ACS_LLCORNER},   {L'┕', ACS_LLCORNER},   {L'┖', ACS_LLCORNER},
        {L'┗', ACS_LLCORNER},   {L'╘', ACS_LLCORNER},   {L'╙', ACS_LLCORNER},
        {L'╚', ACS_LLCORNER},   {L'╰', ACS_LLCORNER},

        {L'┐', ACS_URCORNER},   {L'┑', ACS_URCORNER},   {L'┒', ACS_URCORNER},
        {L'┓', ACS_URCORNER},   {L'╕', ACS_URCORNER},   {L'╖', ACS_URCORNER},
        {L'╗', ACS_URCORNER},   {L'╮', ACS_URCORNER},

        {L'┘', ACS_LRCORNER},   {L'┙', ACS_LRCORNER},   {L'┚', ACS_LRCORNER},
        {L'┛', ACS_LRCORNER},   {L'╛', ACS_LRCORNER},   {L'╜', ACS_LRCORNER},
        {L'╝', ACS_LRCORNER},   {L'╯', ACS_LRCORNER},

        {L'├', ACS_LTEE},       {L'┝', ACS_LTEE},       {L'┞', ACS_LTEE},
        {L'┟', ACS_LTEE},       {L'┠', ACS_LTEE},       {L'┡', ACS_LTEE},
        {L'┢', ACS_LTEE},       {L'┣', ACS_LTEE},       {L'╞', ACS_LTEE},
        {L'╟', ACS_LTEE},       {L'╠', ACS_LTEE},

        {L'┤', ACS_RTEE},       {L'┥', ACS_RTEE},       {L'┦', ACS_RTEE},
        {L'┧', ACS_RTEE},       {L'┨', ACS_RTEE},       {L'┩', ACS_RTEE},
        {L'┪', ACS_RTEE},       {L'┫', ACS_RTEE},       {L'╡', ACS_RTEE},
        {L'╢', ACS_RTEE},       {L'╣', ACS_RTEE},

        {L'┴', ACS_BTEE},       {L'┵', ACS_BTEE},       {L'┶', ACS_BTEE},
        {L'┷', ACS_BTEE},       {L'┸', ACS_BTEE},       {L'┹', ACS_BTEE},
        {L'┺', ACS_BTEE},       {L'┻', ACS_BTEE},       {L'╧', ACS_BTEE},
        {L'╨', ACS_BTEE},       {L'╩', ACS_BTEE},

        {L'┬', ACS_TTEE},       {L'┭', ACS_TTEE},       {L'┮', ACS_TTEE},
        {L'┯', ACS_TTEE},       {L'┰', ACS_TTEE},       {L'┱', ACS_TTEE},
        {L'┲', ACS_TTEE},       {L'┳', ACS_TTEE},       {L'╤', ACS_TTEE},
        {L'╥', ACS_TTEE},       {L'╦', ACS_TTEE},

        {L'─', ACS_HLINE},      {L'━', ACS_HLINE},      {L'┄', ACS_HLINE},
        {L'┅', ACS_HLINE},      {L'┈', ACS_HLINE},      {L'┉', ACS_HLINE},
        {L'╌', ACS_HLINE},      {L'╍', ACS_HLINE},      {L'═', ACS_HLINE},
        {L'╼', ACS_HLINE},      {L'╾', ACS_HLINE},      {L'╸', ACS_HLINE},
        {L'╺', ACS_HLINE},      {L'╶', ACS_HLINE},      {L'╴', ACS_HLINE},

        {L'│', ACS_VLINE},      {L'┃', ACS_VLINE},      {L'┆', ACS_VLINE},
        {L'┇', ACS_VLINE},      {L'┊', ACS_VLINE},      {L'┋', ACS_VLINE},
        {L'╎', ACS_VLINE},      {L'╏', ACS_VLINE},      {L'║', ACS_VLINE},
        {L'╵', ACS_VLINE},      {L'╷', ACS_VLINE},      {L'╹', ACS_VLINE},
        {L'╻', ACS_VLINE},      {L'╽', ACS_VLINE},      {L'╿', ACS_VLINE},

        {L'┼', ACS_PLUS},       {L'┽', ACS_PLUS},       {L'┾', ACS_PLUS},
        {L'┿', ACS_PLUS},       {L'╀', ACS_PLUS},       {L'╁', ACS_PLUS},
        {L'╂', ACS_PLUS},       {L'╃', ACS_PLUS},       {L'╄', ACS_PLUS},
        {L'╅', ACS_PLUS},       {L'╆', ACS_PLUS},       {L'╇', ACS_PLUS},
        {L'╈', ACS_PLUS},       {L'╉', ACS_PLUS},       {L'╊', ACS_PLUS},
        {L'╋', ACS_PLUS},       {L'╪', ACS_PLUS},       {L'╫', ACS_PLUS},
        {L'╬', ACS_PLUS},

        {L'◆', ACS_DIAMOND},    {L'⋄', ACS_DIAMOND},    {L'⌺', ACS_DIAMOND},
        {L'⍚', ACS_DIAMOND},    {L'◇', ACS_DIAMOND},    {L'◈', ACS_DIAMOND},
        {L'♢', ACS_DIAMOND},    {L'♦', ACS_DIAMOND},    {L'⛋', ACS_DIAMOND},
        {L'❖', ACS_DIAMOND},    {L'⬖', ACS_DIAMOND},    {L'⬗', ACS_DIAMOND},
        {L'⬘', ACS_DIAMOND},    {L'⬙', ACS_DIAMOND},    {L'⬥', ACS_DIAMOND},
        {L'⬦', ACS_DIAMOND},    {L'⬩', ACS_DIAMOND},    {L'⯁', ACS_DIAMOND},
        {L'🞜', ACS_DIAMOND}, {L'🞛', ACS_DIAMOND}, {L'🞚', ACS_DIAMOND},
        {L'🞙', ACS_DIAMOND},

        {L'▒', ACS_CKBOARD},    {L'░', ACS_CKBOARD},    {L'▓', ACS_CKBOARD},
        {L'°', ACS_DEGREE},     {L'±', ACS_PLMINUS},    {L'·', ACS_BULLET},
        {L'⎺', ACS_S1},         {L'⎻', ACS_S3},         {L'⎼', ACS_S7},
        {L'⎽', ACS_S9},

        {L'←', ACS_LARROW},     {L'◀', ACS_LARROW},     {L'↩', ACS_LARROW},
        {L'↞', ACS_LARROW},     {L'↢', ACS_LARROW},     {L'↤', ACS_LARROW},
        {L'↫', ACS_LARROW},     {L'↰', ACS_LARROW},     {L'↵', ACS_LARROW},
        {L'↼', ACS_LARROW},     {L'↽', ACS_LARROW},     {L'⇐', ACS_LARROW},
        {L'⇚', ACS_LARROW},     {L'⇠', ACS_LARROW},     {L'⇜', ACS_LARROW},
        {L'⇦', ACS_LARROW},     {L'⇷', ACS_LARROW},     {L'⇺', ACS_LARROW},
        {L'⇺', ACS_LARROW},     {L'⇽', ACS_LARROW},     {L'⟵', ACS_LARROW},
        {L'⟸', ACS_LARROW},     {L'⟽', ACS_LARROW},     {L'⤆', ACS_LARROW},
        {L'⤌', ACS_LARROW},     {L'⤎', ACS_LARROW},     {L'⤶', ACS_LARROW},
        {L'⬅', ACS_LARROW},     {L'⏎', ACS_LARROW},     {L'⍃', ACS_LARROW},
        {L'⍇', ACS_LARROW},     {L'⏴', ACS_LARROW},

        {L'→', ACS_RARROW},     {L'▶', ACS_RARROW},     {L'➔', ACS_RARROW},
        {L'➙', ACS_RARROW},     {L'➛', ACS_RARROW},     {L'➜', ACS_RARROW},
        {L'➝', ACS_RARROW},     {L'➟', ACS_RARROW},     {L'➡', ACS_RARROW},
        {L'➢', ACS_RARROW},     {L'➣', ACS_RARROW},     {L'➤', ACS_RARROW},
        {L'➥', ACS_RARROW},     {L'➦', ACS_RARROW},     {L'↪', ACS_RARROW},
        {L'↠', ACS_RARROW},     {L'↣', ACS_RARROW},     {L'↦', ACS_RARROW},
        {L'↬', ACS_RARROW},     {L'↱', ACS_RARROW},     {L'↳', ACS_RARROW},
        {L'⇀', ACS_RARROW},     {L'⇁', ACS_RARROW},     {L'⇒', ACS_RARROW},
        {L'⇛', ACS_RARROW},     {L'⇝', ACS_RARROW},     {L'⇢', ACS_RARROW},
        {L'⇥', ACS_RARROW},     {L'⇨', ACS_RARROW},     {L'⇰', ACS_RARROW},
        {L'⇶', ACS_RARROW},     {L'⇸', ACS_RARROW},     {L'⇻', ACS_RARROW},
        {L'⇾', ACS_RARROW},     {L'⟶', ACS_RARROW},     {L'⟹', ACS_RARROW},
        {L'⟾', ACS_RARROW},     {L'⟼', ACS_RARROW},     {L'⤃', ACS_RARROW},
        {L'⤅', ACS_RARROW},     {L'⤁', ACS_RARROW},     {L'⟿', ACS_RARROW},
        {L'⤀', ACS_RARROW},     {L'⤇', ACS_RARROW},     {L'⤍', ACS_RARROW},
        {L'⤏', ACS_RARROW},     {L'⤐', ACS_RARROW},     {L'⤑', ACS_RARROW},
        {L'⤔', ACS_RARROW},     {L'⤕', ACS_RARROW},     {L'⤖', ACS_RARROW},
        {L'⤘', ACS_RARROW},     {L'⤗', ACS_RARROW},     {L'⤷', ACS_RARROW},
        {L'➧', ACS_RARROW},     {L'➳', ACS_RARROW},     {L'➲', ACS_RARROW},
        {L'➱', ACS_RARROW},     {L'➯', ACS_RARROW},     {L'➮', ACS_RARROW},
        {L'➭', ACS_RARROW},     {L'➬', ACS_RARROW},     {L'➫', ACS_RARROW},
        {L'➪', ACS_RARROW},     {L'➩', ACS_RARROW},     {L'➨', ACS_RARROW},
        {L'➵', ACS_RARROW},     {L'➸', ACS_RARROW},     {L'➺', ACS_RARROW},
        {L'➾', ACS_RARROW},     {L'➽', ACS_RARROW},     {L'➼', ACS_RARROW},
        {L'➻', ACS_RARROW},     {L'⍄', ACS_RARROW},     {L'⍈', ACS_RARROW},
        {L'⏵', ACS_RARROW},

        {L'▼', ACS_DARROW},     {L'↓', ACS_DARROW},     {L'↡', ACS_DARROW},
        {L'↧', ACS_DARROW},     {L'↴', ACS_DARROW},     {L'⤵', ACS_DARROW},
        {L'⇂', ACS_DARROW},     {L'⇃', ACS_DARROW},     {L'⇓', ACS_DARROW},
        {L'⇓', ACS_DARROW},     {L'⇣', ACS_DARROW},     {L'⇩', ACS_DARROW},
        {L'⤋', ACS_DARROW},     {L'⬇', ACS_DARROW},     {L'⬎', ACS_DARROW},
        {L'⬐', ACS_DARROW},     {L'⍗', ACS_DARROW},     {L'⍌', ACS_DARROW},

        {L'↑', ACS_UARROW},     {L'▲', ACS_UARROW},     {L'↟', ACS_UARROW},
        {L'↥', ACS_UARROW},     {L'↾', ACS_UARROW},     {L'↿', ACS_UARROW},
        {L'⇑', ACS_UARROW},     {L'⇞', ACS_UARROW},     {L'⇡', ACS_UARROW},
        {L'⇪', ACS_UARROW},     {L'⇧', ACS_UARROW},     {L'⇮', ACS_UARROW},
        {L'⇯', ACS_UARROW},     {L'⇭', ACS_UARROW},     {L'⇬', ACS_UARROW},
        {L'⇫', ACS_UARROW},     {L'⤉', ACS_UARROW},     {L'⤊', ACS_UARROW},
        {L'⤒', ACS_UARROW},     {L'⤴', ACS_UARROW},     {L'⥔', ACS_UARROW},
        {L'⥘', ACS_UARROW},     {L'⥜', ACS_UARROW},     {L'⥠', ACS_UARROW},
        {L'⬆', ACS_UARROW},     {L'⬏', ACS_UARROW},     {L'⬑', ACS_UARROW},
        {L'⍐', ACS_UARROW},     {L'⍓', ACS_UARROW},     {L'⍍', ACS_UARROW},

        {L'▚', ACS_BOARD},      {L'▞', ACS_BOARD},      {L'␋', ACS_LANTERN},
        {L'█', ACS_BLOCK},      {L'≤', ACS_LEQUAL},     {L'≥', ACS_GEQUAL},
        {L'π', ACS_PI},         {L'≠', ACS_NEQUAL},     {L'£', ACS_STERLING},

        {L'×', 'x'},            {L'╳', 'X'},            {L'☓', 'x'},
        {L'✕', 'X'},            {L'✖', 'X'},            {L'⨉', 'X'},
        {L'⨯', 'X'},            {L'🗙', 'X'},            {L'🗴', 'X'},
        {L'🞩', 'X'},

        {L'✓', 'x'},            {L'✔', 'x'},            {L'🗸', 'x'},
        {L'🗹', 'x'},            {L'☑', 'x'},            {L'☒', 'x'},
        {L'⊠', 'x'},            {L'⊗', 'x'},            {L'⛒', 'x'},
        {L'◉', 'x'},            {L'■', 'x'},            {L'▣', 'x'},

        {L'☐', ACS_BLOCK},      {L'⊙', ACS_BLOCK},      {L'○', ACS_BLOCK},
        {L'▢', ACS_BLOCK},      {L'□', ACS_BLOCK},

        {L'♝', 'B'},            {L'♚', 'K'},            {L'♞','N'},
        {L'♟', 'P'},            {L'♛','Q'},             {L'♜','R'},

        {L'⁸', '8'},            {L'⁷', '7'},            {L'⁶', '6'},
        {L'⁵', '5'},            {L'⁴', '4'},            {L'³', '3'},
        {L'²', '2'},            {L'¹', '1'},

        {L'ᵃ', 'a'},            {L'ᵇ', 'b'},            {L'ᶜ', 'c'},
        {L'ᵈ', 'd'},            {L'ᵉ', 'e'},            {L'ᶠ', 'f'},
        {L'ᵍ', 'g'},            {L'ʰ', 'h'}};
    return extended_chars;
}

// Find corresponding chtype from wchar_t for extended char set.
chtype find_chtype(wchar_t sym, bool* use_addch) {
    if (sym < 128) {
        return static_cast<chtype>(sym);
    }
    if (get_ext_chars().count(sym) != 0) {
        *use_addch = true;
        return get_ext_chars().find(sym)->second;
    }
    return '?';
}

}  // namespace detail
}  // namespace cppurses
