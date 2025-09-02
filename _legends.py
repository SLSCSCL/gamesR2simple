import pygame as pg
keys = {
    "ArrowUp": pg.K_UP, "ArrowDown": pg.K_DOWN, "ArrowLeft": pg.K_LEFT,
    "ArrowRight": pg.K_RIGHT, "a": pg.K_a, "b": pg.K_b, "c": pg.K_c,
    "d": pg.K_d, "e": pg.K_e, "f": pg.K_f, "g": pg.K_g, "h": pg.K_h,
    "i": pg.K_i, "j": pg.K_j, "k": pg.K_k, "l": pg.K_l, "m": pg.K_m,
    "n": pg.K_n, "o": pg.K_o, "p": pg.K_p, "q": pg.K_q, "r": pg.K_r,
    "s": pg.K_s, "t": pg.K_t, "u": pg.K_u, "v": pg.K_v, "w": pg.K_w,
    "x": pg.K_x, "y": pg.K_y, "z": pg.K_z, "1": pg.K_1, "2": pg.K_2,
    "3": pg.K_3, "4": pg.K_4, "5": pg.K_5, "6": pg.K_6, "7": pg.K_7,
    "8": pg.K_8, "9": pg.K_9, "0": pg.K_0, "+": pg.K_PLUS, 
    "-": pg.K_MINUS, "=": pg.K_EQUALS, "`": pg.K_BACKQUOTE,
    "Escape": pg.K_ESCAPE, "Backspace": pg.K_BACKSPACE,
    "Left-hand shift": pg.K_LSHIFT, "Right-hand shift": pg.K_RSHIFT,
    "Left-hand ctrl": pg.K_LCTRL, "Right-hand ctrl": pg.K_RCTRL,
    "Left-hand alt": pg.K_LALT, "Right-hand alt": pg.K_RALT,
    "!": pg.K_EXCLAIM, "@": pg.K_AT, "#": pg.K_HASH, "$": pg.K_DOLLAR,
    "%": pg.K_PERCENT, "^": pg.K_CARET, "&": pg.K_AMPERSAND,
    "*": pg.K_ASTERISK, "(": pg.K_LEFTPAREN, ")": pg.K_RIGHTPAREN,
    "_": pg.K_UNDERSCORE, "[": pg.K_LEFTBRACKET, "]": pg.K_RIGHTBRACKET, 
    ":": pg.K_COLON, ";": pg.K_SEMICOLON, "'": pg.K_QUOTE,
    '"': pg.K_QUOTEDBL, "\\": pg.K_BACKSLASH, ",": pg.K_COMMA,
    ".": pg.K_PERIOD, "<": pg.K_LESS, ">": pg.K_GREATER, "/": pg.K_SLASH,
    "?": pg.K_QUESTION, "Tab": pg.K_TAB, "Caps lock": pg.K_CAPSLOCK,
    "Insert": pg.K_INSERT, "Home": pg.K_HOME, "Page up": pg.K_PAGEUP,
    "Page down": pg.K_PAGEDOWN, "Delete": pg.K_DELETE, "End": pg.K_END,
    "F1": pg.K_F1, "F2": pg.K_F2, "F3": pg.K_F3, "F4": pg.K_F4,
    "F5": pg.K_F5, "F6": pg.K_F6, "F7": pg.K_F7, "F8": pg.K_F8,
    "F9": pg.K_F9, "F10": pg.K_F10, "F11": pg.K_F11, "F12": pg.K_F12,
    "Num Lock": pg.K_NUMLOCK, "Space": pg.K_SPACE
}

pressed_keys = {attr: False for attr in keys.values()}

pressed_btns = {
    "left": False,
    "mid": False,
    "right": False
}
