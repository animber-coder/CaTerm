#ifndef KEY_HPP
#define KEY_HPP

enum class Key {
    // Control Characters
    Null = 0,    // Ctrl + Space, or Ctrl + 2, OR Ctrl + @
    Ctrl_a,      // Start of heading
    Ctrl_b,      // Start of text
    Ctrl_c,      // End of text
    Ctrl_d,      // End of transmission
    Ctrl_e,      // Enquiry
    Ctrl_f,      // Acknowledge
    Ctrl_g,      // Bell
    Backspace_,  // Not used? ascii value 8 check with keypad
    Tab,         // Ctrl + I
    Enter,       // Ctrl + J, or Ctrl + M, AKA Line Feed, AKA Carriage Return
    Ctrl_k,      // Vertical Tab
    Ctrl_l,      // Form Feed
    Carriage_return_,     // not used? check with keypad, ascii 13 maybe make it
                          // keypad_enter
    Ctrl_n,               // Shift Out
    Ctrl_o,               // Shift In
    Ctrl_p,               // Data Link Escape
    Ctrl_q,               // Device Control One
    Ctrl_r,               // Device Control Two
    Ctrl_s,               // Device Control Three
    Ctrl_t,               // Device Control Four
    Ctrl_u,               // Negative Acknowledge
    Ctrl_v,               // Synchronous Idle
    Ctrl_w,               // End of Transmission Block
    Ctrl_x,               // Cancel
    Ctrl_y,               // End of Medium
    Ctrl_z,               // Substitute
    Escape,               // Ctrl + [, or Ctrl + 3
    Ctrl_backslash,       // Ctrl + 4, File Separator
    Ctrl_closed_bracket,  // Ctrl + 5, Group Separator
    Ctrl_caret,           // Ctrl + 6, Record Separator
    Ctrl_underscore,      // Ctrl + 7, Unit Separator
    Backspace = 127,      // Ctrl + 8

    // Printable Characters
    Space = 32,
    Exclamation_mark,
    Double_quotation,
    Hash,
    Dollar,
    Percent,
    Ampersand,
    Apostrophe,
    Left_parenthesis,
    Right_parenthesis,
    Asterisk,
    Plus,
    Comma,
    Minus,
    Period,
    Forward_slash,
    Zero,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Colon,
    Semicolon,
    Less_than,
    Equals,
    Greater_than,
    Question_mark,
    At_sign,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Left_bracket,
    Backslash,
    Right_bracket,
    Caret,
    Underscore,
    Accent,
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    Left_curly_bracket,
    Vertical_bar,
    Right_curly_bracket,
    Tilde,

    // Curses Specialty Characters
    Arrow_down = 258,
    Arrow_up,
    Arrow_left,
    Arrow_right,
    Home,
    Backspace_2,     // unused? int 263
    Function = 264,  // Add function number to enum when used ex) F5 key =
                     // Key::Function + 5;
    // up to 63 function keys...
    Delete_line = 328,
    Insert_line,
    Delete_character,
    Insert_character,
    EIC,  // sent by rmir or smir in insert mode
    Clear_screen,
    Clear_to_end_of_screen,
    Clear_to_end_of_line,
    Scroll_forward,
    Scroll_backward,
    Next_page,
    Previous_page,
    Set_tab,
    Clear_tab,
    Clear_all_tabs,
    Possibly_keypad_enter_,  // might be Keypad_enter? check it out, function
                             // key and Enter
                             // int 343
    Print = 346,
    Home_down,  // Lower left keypad? Home down key? check with larger keyboard
    Keypad_7,
    Keypad_9,
    Keypad_5,  // other keypad numbers are in arrow keys, make sure this is
               // correct
    Keypad_1,
    Keypad_3,
    Back_tab,
    Begin,
    Cancel_dup_,  // look into this to see if its the same as the above cancel
                  // key
    Close,
    Command,
    Copy,
    Create,
    End,
    Exit,
    Find,
    Help,
    Mark,
    Message,
    Move,
    Next,
    Open,
    Options,
    Previous,
    Redo,
    Reference,
    Refresh,
    Replace,
    Restart,
    Resume,
    Save,
    Shift_begin,
    Shift_cancel,
    Shift_command,
    Shift_copy,
    Shift_create,
    Shift_delete_character,
    Shift_delete_line,
    Select,
    Shift_end,
    Shift_clear_to_end_of_line,
    Shift_exit,
    Shift_find,
    Shift_help,
    Shift_home,
    Shift_insert_character,
    Shift_left_arrow,
    Shift_message,
    Shift_move,
    Shift_next,
    Shift_options,
    Shift_previous,
    Shift_print,
    Shift_redo,
    Shift_replace,
    Shift_right_arrow,
    Shift_resume,
    Shift_save,
    Shift_suspend,
    Shift_undo,
    Suspend,
    Undo
};

#endif  // KEY_HPP
