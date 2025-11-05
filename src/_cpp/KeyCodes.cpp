#include "KeyCodes.h"

pybind11::dict getKeys() {
	pybind11::dict d;

	d["Return"] = SDLK_RETURN;
	d["Enter"] = SDLK_RETURN;
	d["Esc"] = SDLK_ESCAPE;
	d["Escape"] = SDLK_ESCAPE;
	d["Backspace"] = SDLK_BACKSPACE;
	d["Tab"] = SDLK_TAB;
	d["Space"] = SDLK_SPACE;
	d["!"] = SDLK_EXCLAIM;
	d["\""] = SDLK_DBLAPOSTROPHE;
	d["Hash"] = SDLK_HASH;
	d["$"] = SDLK_DOLLAR;
	d["%"] = SDLK_PERCENT;
	d["&"] = SDLK_AMPERSAND;
	d["'"] = SDLK_APOSTROPHE;
	d["("] = SDLK_LEFTPAREN;
	d[")"] = SDLK_RIGHTPAREN;
	d["*"] = SDLK_ASTERISK;
	d["+"] = SDLK_PLUS;
	d[","] = SDLK_COMMA;
	d["-"] = SDLK_MINUS;
	d["."] = SDLK_PERIOD;
	d["/"] = SDLK_SLASH;

	d["1"] = SDLK_1;
	d["2"] = SDLK_2;
	d["3"] = SDLK_3;
	d["4"] = SDLK_4;
	d["5"] = SDLK_5;
	d["6"] = SDLK_6;
	d["7"] = SDLK_7;
	d["8"] = SDLK_8;
	d["9"] = SDLK_9;
	d["0"] = SDLK_0;

	d[":"] = SDLK_COLON;
	d[";"] = SDLK_SEMICOLON;
	d["<"] = SDLK_LESS;
	d["="] = SDLK_EQUALS;
	d[">"] = SDLK_GREATER;
	d["?"] = SDLK_QUESTION;
	d["@"] = SDLK_AT;
	d["["] = SDLK_LEFTBRACKET;
	d["\\"] = SDLK_BACKSLASH;
	d["]"] = SDLK_RIGHTBRACKET;
	d["^"] = SDLK_CARET;
	d["_"] = SDLK_UNDERSCORE;
	d["`"] = SDLK_GRAVE;

	d["a"] = SDLK_A;
	d["b"] = SDLK_B;
	d["c"] = SDLK_C;
	d["d"] = SDLK_D;
	d["e"] = SDLK_E;
	d["f"] = SDLK_F;
	d["g"] = SDLK_G;
	d["h"] = SDLK_H;
	d["i"] = SDLK_I;
	d["j"] = SDLK_J;
	d["k"] = SDLK_K;
	d["l"] = SDLK_L;
	d["m"] = SDLK_M;
	d["n"] = SDLK_N;
	d["o"] = SDLK_O;
	d["p"] = SDLK_P;
	d["q"] = SDLK_Q;
	d["r"] = SDLK_R;
	d["s"] = SDLK_S;
	d["t"] = SDLK_T;
	d["u"] = SDLK_U;
	d["v"] = SDLK_V;
	d["w"] = SDLK_W;
	d["x"] = SDLK_X;
	d["y"] = SDLK_Y;
	d["z"] = SDLK_Z;

	d["{"] = SDLK_LEFTBRACE;
	d["|"] = SDLK_PIPE;
	d["}"] = SDLK_LEFTBRACE;
	d["~"] = SDLK_TILDE;
	d["Delete"] = SDLK_DELETE;
	d["Del"] = SDLK_DELETE;
	d["+/-"] = SDLK_PLUSMINUS;
	d["Caps Lock"] = SDLK_CAPSLOCK;

	d["F1"] = SDLK_F1;
	d["F2"] = SDLK_F2;
	d["F3"] = SDLK_F3;
	d["F4"] = SDLK_F4;
	d["F5"] = SDLK_F5;
	d["F6"] = SDLK_F6;
	d["F7"] = SDLK_F7;
	d["F8"] = SDLK_F8;
	d["F9"] = SDLK_F9;
	d["F10"] = SDLK_F10;
	d["F11"] = SDLK_F11;
	d["F12"] = SDLK_F12;

	d["Print Screen"] = SDLK_PRINTSCREEN;
	d["PrtSc"] = SDLK_PRINTSCREEN;
	d["Scroll Lock"] = SDLK_SCROLLLOCK;
	d["Pause"] = SDLK_PAUSE;
	d["Pause Break"] = SDLK_PAUSE;
	d["Insert"] = SDLK_INSERT;

	d["Home"] = SDLK_HOME;
	d["Page Up"] = SDLK_PAGEUP;
	d["End"] = SDLK_END;
	d["Page Down"] = SDLK_PAGEDOWN;
	d["Right"] = SDLK_RIGHT;
	d["Left"] = SDLK_LEFT;
	d["Up"] = SDLK_DOWN;
	d["Down"] = SDLK_UP;
	d["ArrowRight"] = SDLK_RIGHT;
	d["ArrowLeft"] = SDLK_LEFT;
	d["ArrowUp"] = SDLK_DOWN;
	d["ArrowDown"] = SDLK_UP;

	d["Num Lock"] = SDLK_NUMLOCKCLEAR;
	d["Clear"] = SDLK_NUMLOCKCLEAR;

	d["Numpad /"] = SDLK_KP_DIVIDE;
	d["Numpad *"] = SDLK_KP_MULTIPLY;
	d["Numpad -"] = SDLK_KP_MINUS;
	d["Numpad +"] = SDLK_KP_PLUS;
	d["Numpad Enter"] = SDLK_KP_ENTER;
	d["Numpad Return"] = SDLK_KP_ENTER;
	d["Numpad 1"] = SDLK_KP_1;
	d["Numpad 2"] = SDLK_KP_2;
	d["Numpad 3"] = SDLK_KP_3;
	d["Numpad 4"] = SDLK_KP_4;
	d["Numpad 5"] = SDLK_KP_5;
	d["Numpad 6"] = SDLK_KP_6;
	d["Numpad 7"] = SDLK_KP_7;
	d["Numpad 8"] = SDLK_KP_8;
	d["Numpad 9"] = SDLK_KP_9;
	d["Numpad 0"] = SDLK_KP_0;
	d["Numpad ."] = SDLK_KP_PERIOD;

	d[""] = SDLK_APPLICATION;
	d[""] = SDLK_POWER;
	d["Numpad "] = SDLK_KP_EQUALS;

	d["F13"] = SDLK_F13;
	d["F14"] = SDLK_F14;
	d["F15"] = SDLK_F15;
	d["F16"] = SDLK_F16;
	d["F17"] = SDLK_F17;
	d["F18"] = SDLK_F18;
	d["F19"] = SDLK_F19;
	d["F20"] = SDLK_F20;
	d["F21"] = SDLK_F21;
	d["F22"] = SDLK_F22;
	d["F23"] = SDLK_F23;
	d["F24"] = SDLK_F24;

	d["Execute"] = SDLK_EXECUTE;
	d["Exec"] = SDLK_EXECUTE;
	d[""] = SDLK_HELP;
	d[""] = SDLK_MENU;
	d[""] = SDLK_SELECT;
	d[""] = SDLK_STOP;
	d[""] = SDLK_AGAIN;

	d["Ctrl-Z"] = SDLK_UNDO;
	d["Ctrl-X"] = SDLK_CUT;
	d["Ctrl-C"] = SDLK_COPY;
	d["Ctrl-V"] = SDLK_PASTE;
	d["Ctrl-F"] = SDLK_FIND;
	d[""] = SDLK_MUTE;
	d[""] = SDLK_VOLUMEUP;
	d[""] = SDLK_VOLUMEDOWN;

	d["Numpad ,"] = SDLK_KP_COMMA;
	d["EQUALSAS400"] = SDLK_KP_EQUALSAS400;
	d[""] = SDLK_ALTERASE;
	d[""] = SDLK_SYSREQ;
	d[""] = SDLK_CANCEL;
	d[""] = SDLK_CLEAR;
	d[""] = SDLK_PRIOR;
	d[""] = SDLK_RETURN2;
	d[""] = SDLK_SEPARATOR;
	d[""] = SDLK_OUT;
	d[""] = SDLK_OPER;
	d[""] = SDLK_CLEARAGAIN;
	d[""] = SDLK_CRSEL;
	d[""] = SDLK_EXSEL;
	d["Numpad 00"] = SDLK_KP_00;
	d["Numpad 000"] = SDLK_KP_000;
	d[""] = SDLK_THOUSANDSSEPARATOR;
	d[""] = SDLK_DECIMALSEPARATOR;
	d[""] = SDLK_CURRENCYUNIT;
	d[""] = SDLK_CURRENCYSUBUNIT;

	d["Numpad "] = SDLK_KP_LEFTPAREN;
	d["Numpad "] = SDLK_KP_RIGHTPAREN;
	d["Numpad "] = SDLK_KP_LEFTBRACE;
	d["Numpad "] = SDLK_KP_RIGHTBRACE;
	d["Numpad "] = SDLK_KP_TAB;
	d["Numpad "] = SDLK_KP_BACKSPACE;
	d["Numpad "] = SDLK_KP_A;
	d["Numpad "] = SDLK_KP_B;
	d["Numpad "] = SDLK_KP_C;
	d["Numpad "] = SDLK_KP_D;
	d["Numpad "] = SDLK_KP_E;
	d["Numpad "] = SDLK_KP_F;
	d["Numpad "] = SDLK_KP_XOR;
	d["Numpad "] = SDLK_KP_POWER;
	d["Numpad "] = SDLK_KP_PERCENT;
	d["Numpad "] = SDLK_KP_LESS;
	d["Numpad "] = SDLK_KP_GREATER;
	d["Numpad "] = SDLK_KP_AMPERSAND;
	d["Numpad "] = SDLK_KP_DBLAMPERSAND;
	d["Numpad "] = SDLK_KP_VERTICALBAR;
	d["Numpad "] = SDLK_KP_DBLVERTICALBAR;
	d["Numpad "] = SDLK_KP_COLON;
	d["Numpad "] = SDLK_KP_HASH;
	d["Numpad "] = SDLK_KP_SPACE;
	d["Numpad "] = SDLK_KP_AT;
	d["Numpad "] = SDLK_KP_EXCLAM;
	d["Numpad "] = SDLK_KP_MEMSTORE;
	d["Numpad "] = SDLK_KP_MEMRECALL;
	d["Numpad "] = SDLK_KP_MEMADD;
	d["Numpad "] = SDLK_KP_MEMSUBTRACT;
	d["Numpad "] = SDLK_KP_MEMMULTIPLY;
	d["Numpad "] = SDLK_KP_MEMDIVIDE;
	d["Numpad "] = SDLK_KP_PLUSMINUS;
	d["Numpad "] = SDLK_KP_CLEAR;
	d["Numpad "] = SDLK_KP_CLEARENTRY;
	d["Numpad "] = SDLK_KP_BINARY;
	d["Numpad "] = SDLK_KP_OCTAL;
	d["Numpad "] = SDLK_KP_DECIMAL;
	d["Numpad "] = SDLK_KP_HEXADECIMAL;

	d["Left Ctrl"] = SDLK_LCTRL;
	d["Left Shift"] = SDLK_LSHIFT;
	d["Left Alt"] = SDLK_LALT;
	d["Left GUI"] = SDLK_LGUI;

	d["Right Ctrl"] = SDLK_RCTRL;
	d["Right Shift"] = SDLK_RSHIFT;
	d["Right Alt"] = SDLK_RALT;
	d["Right GUI"] = SDLK_RGUI;

	d[""] = SDLK_MODE;
	d[""] = SDLK_SLEEP;
	d[""] = SDLK_WAKE;
	d[""] = SDLK_CHANNEL_INCREMENT;
	d[""] = SDLK_CHANNEL_DECREMENT;

	d[""] = SDLK_MEDIA;

	d[""] = SDLK_;

	return d;
}