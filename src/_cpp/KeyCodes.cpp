#include "KeyCodes.h"

pybind11::dict getKeys() {
	pybind11::dict d;

	d["a"] = SDL_SCANCODE_A;
	d["b"] = SDL_SCANCODE_B;
	d["c"] = SDL_SCANCODE_C;
	d["d"] = SDL_SCANCODE_D;
	d["e"] = SDL_SCANCODE_E;
	d["f"] = SDL_SCANCODE_F;
	d["g"] = SDL_SCANCODE_G;
	d["h"] = SDL_SCANCODE_H;
	d["i"] = SDL_SCANCODE_I;
	d["j"] = SDL_SCANCODE_J;
	d["k"] = SDL_SCANCODE_K;
	d["l"] = SDL_SCANCODE_L;
	d["m"] = SDL_SCANCODE_M;
	d["n"] = SDL_SCANCODE_N;
	d["o"] = SDL_SCANCODE_O;
	d["p"] = SDL_SCANCODE_P;
	d["q"] = SDL_SCANCODE_Q;
	d["r"] = SDL_SCANCODE_R;
	d["s"] = SDL_SCANCODE_S;
	d["t"] = SDL_SCANCODE_T;
	d["u"] = SDL_SCANCODE_U;
	d["v"] = SDL_SCANCODE_V;
	d["w"] = SDL_SCANCODE_W;
	d["x"] = SDL_SCANCODE_X;
	d["y"] = SDL_SCANCODE_Y;
	d["z"] = SDL_SCANCODE_Z;

	d["1"] = SDL_SCANCODE_1;
	d["2"] = SDL_SCANCODE_2;
	d["3"] = SDL_SCANCODE_3;
	d["4"] = SDL_SCANCODE_4;
	d["5"] = SDL_SCANCODE_5;
	d["6"] = SDL_SCANCODE_6;
	d["7"] = SDL_SCANCODE_7;
	d["8"] = SDL_SCANCODE_8;
	d["9"] = SDL_SCANCODE_9;
	d["0"] = SDL_SCANCODE_0;

	d["Return"] = SDL_SCANCODE_RETURN;
	d["Enter"] = SDL_SCANCODE_RETURN;
	d["Esc"] = SDL_SCANCODE_ESCAPE;
	d["Escape"] = SDL_SCANCODE_ESCAPE;
	d["Backspace"] = SDL_SCANCODE_BACKSPACE;
	d["Tab"] = SDL_SCANCODE_TAB;
	d["Space"] = SDL_SCANCODE_SPACE;

	d["-"] = SDL_SCANCODE_MINUS;
	d["="] = SDL_SCANCODE_EQUALS;
	d["["] = SDL_SCANCODE_LEFTBRACKET;
	d["]"] = SDL_SCANCODE_RIGHTBRACKET;
	d["\\"] = SDL_SCANCODE_BACKSLASH;

	d[";"] = SDL_SCANCODE_SEMICOLON;
	d["'"] = SDL_SCANCODE_APOSTROPHE;
	d["`"] = SDL_SCANCODE_GRAVE;
	
	d[","] = SDL_SCANCODE_COMMA;
	d["."] = SDL_SCANCODE_PERIOD;
	d["/"] = SDL_SCANCODE_SLASH;

	d["Caps Lock"] = SDL_SCANCODE_CAPSLOCK;

	d["F1"] = SDL_SCANCODE_F1;
	d["F2"] = SDL_SCANCODE_F2;
	d["F3"] = SDL_SCANCODE_F3;
	d["F4"] = SDL_SCANCODE_F4;
	d["F5"] = SDL_SCANCODE_F5;
	d["F6"] = SDL_SCANCODE_F6;
	d["F7"] = SDL_SCANCODE_F7;
	d["F8"] = SDL_SCANCODE_F8;
	d["F9"] = SDL_SCANCODE_F9;
	d["F10"] = SDL_SCANCODE_F10;
	d["F11"] = SDL_SCANCODE_F11;
	d["F12"] = SDL_SCANCODE_F12;

	d["Print Screen"] = SDL_SCANCODE_PRINTSCREEN;
	d["PrtSc"] = SDL_SCANCODE_PRINTSCREEN;
	d["Scroll Lock"] = SDL_SCANCODE_SCROLLLOCK;
	d["Pause"] = SDL_SCANCODE_PAUSE;
	d["Insert"] = SDL_SCANCODE_INSERT;

	d["Home"] = SDL_SCANCODE_HOME;
	d["Page Up"] = SDL_SCANCODE_PAGEUP;
	d["Delete"] = SDL_SCANCODE_DELETE;
	d["Del"] = SDL_SCANCODE_DELETE;
	d["End"] = SDL_SCANCODE_END;
	d["Page Down"] = SDL_SCANCODE_PAGEDOWN;
	d["Right"] = SDL_SCANCODE_RIGHT;
	d["Left"] = SDL_SCANCODE_LEFT;
	d["Up"] = SDL_SCANCODE_DOWN;
	d["Down"] = SDL_SCANCODE_UP;
	d["ArrowRight"] = SDL_SCANCODE_RIGHT;
	d["ArrowLeft"] = SDL_SCANCODE_LEFT;
	d["ArrowUp"] = SDL_SCANCODE_DOWN;
	d["ArrowDown"] = SDL_SCANCODE_UP;

	d["Num Lock"] = SDL_SCANCODE_NUMLOCKCLEAR;
	d["Clear"] = SDL_SCANCODE_NUMLOCKCLEAR;

	d["Numpad /"] = SDL_SCANCODE_KP_DIVIDE;
	d["Numpad *"] = SDL_SCANCODE_KP_MULTIPLY;
	d["Numpad -"] = SDL_SCANCODE_KP_MINUS;
	d["Numpad +"] = SDL_SCANCODE_KP_PLUS;
	d["Numpad Enter"] = SDL_SCANCODE_KP_ENTER;
	d["Numpad Return"] = SDL_SCANCODE_KP_ENTER;
	d["Numpad 1"] = SDL_SCANCODE_KP_1;
	d["Numpad 2"] = SDL_SCANCODE_KP_2;
	d["Numpad 3"] = SDL_SCANCODE_KP_3;
	d["Numpad 4"] = SDL_SCANCODE_KP_4;
	d["Numpad 5"] = SDL_SCANCODE_KP_5;
	d["Numpad 6"] = SDL_SCANCODE_KP_6;
	d["Numpad 7"] = SDL_SCANCODE_KP_7;
	d["Numpad 8"] = SDL_SCANCODE_KP_8;
	d["Numpad 9"] = SDL_SCANCODE_KP_9;
	d["Numpad 0"] = SDL_SCANCODE_KP_0;
	d["Numpad ."] = SDL_SCANCODE_KP_PERIOD;

	d["Non-US Backslash"] = SDL_SCANCODE_NONUSBACKSLASH;
	d["Non-US \\"] = SDL_SCANCODE_NONUSBACKSLASH;

	d["Application"] = SDL_SCANCODE_APPLICATION;
	d["Power Button"] = SDL_SCANCODE_POWER;
	d["Power Btn"] = SDL_SCANCODE_POWER;
	d["Power"] = SDL_SCANCODE_POWER;

	d["Numpad Equals"] = SDL_SCANCODE_KP_EQUALS;
	d["Numpad ="] = SDL_SCANCODE_KP_EQUALS;
	d["F13"] = SDL_SCANCODE_F13;
	d["F14"] = SDL_SCANCODE_F14;
	d["F15"] = SDL_SCANCODE_F15;
	d["F16"] = SDL_SCANCODE_F16;
	d["F17"] = SDL_SCANCODE_F17;
	d["F18"] = SDL_SCANCODE_F18;
	d["F19"] = SDL_SCANCODE_F19;
	d["F20"] = SDL_SCANCODE_F20;
	d["F21"] = SDL_SCANCODE_F21;
	d["F22"] = SDL_SCANCODE_F22;
	d["F23"] = SDL_SCANCODE_F23;
	d["F24"] = SDL_SCANCODE_F24;
	d["Execute"] = SDL_SCANCODE_EXECUTE;
	d["Exec"] = SDL_SCANCODE_EXECUTE;
	d["Help"] = SDL_SCANCODE_HELP;
	d["Menu"] = SDL_SCANCODE_MENU;
	d["Select"] = SDL_SCANCODE_SELECT;
	d["AC Stop"] = SDL_SCANCODE_STOP;
	d["AC Redo/Repeat"] = SDL_SCANCODE_AGAIN;
	d["AC Undo"] = SDL_SCANCODE_UNDO;
	d["AC Cut"] = SDL_SCANCODE_CUT;
	d["AC Copy"] = SDL_SCANCODE_COPY;
	d["AC Paste"] = SDL_SCANCODE_PASTE;
	d["AC Find"] = SDL_SCANCODE_FIND;
	d["Mute"] = SDL_SCANCODE_MUTE;
	d["Volume Up"] = SDL_SCANCODE_VOLUMEUP;
	d["Volume Down"] = SDL_SCANCODE_VOLUMEDOWN;

	d["Numpad ,"] = SDL_SCANCODE_KP_COMMA;
	d["Equals As 400"] = SDL_SCANCODE_KP_EQUALSAS400;

	d["Erase-Eaze"] = SDL_SCANCODE_ALTERASE;
	d["Alt Erase"] = SDL_SCANCODE_ALTERASE;
	d["Sys Request"] = SDL_SCANCODE_SYSREQ;
	d["SysRq"] = SDL_SCANCODE_SYSREQ;
	d["Cancel"] = SDL_SCANCODE_CANCEL;
	d["Clear"] = SDL_SCANCODE_CLEAR;
	d["Prior"] = SDL_SCANCODE_PRIOR;
	d["Enter2"] = SDL_SCANCODE_RETURN2;
	d["Return2"] = SDL_SCANCODE_RETURN2;
	d["Separator"] = SDL_SCANCODE_SEPARATOR;
	d["Out"] = SDL_SCANCODE_OUT;
	d["Oper"] = SDL_SCANCODE_OPER;
	d["Clear Again"] = SDL_SCANCODE_CLEARAGAIN;
	d["CRSEL"] = SDL_SCANCODE_CRSEL;
	d["EXSEL"] = SDL_SCANCODE_EXSEL;

	d["Left Ctrl"] = SDL_SCANCODE_LCTRL;
	d["Left Shift"] = SDL_SCANCODE_LSHIFT;
	d["Left Alt"] = SDL_SCANCODE_LALT;
	d["Left GUI"] = SDL_SCANCODE_LGUI;
	d["Right Ctrl"] = SDL_SCANCODE_RCTRL;
	d["Right Shift"] = SDL_SCANCODE_RSHIFT;
	d["Right Alt"] = SDL_SCANCODE_RALT;
	d["Right GUI"] = SDL_SCANCODE_RGUI;

	d["Mode"] = SDL_SCANCODE_MODE;

	return d;
}