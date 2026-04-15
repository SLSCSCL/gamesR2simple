#include "KeyCodes.h"

NAMESPACE

inline int cast(SDL_Scancode code) {
	return static_cast<int>(code);
}

keyMap getKeys() {
	keyMap d;

	d["a"] = cast(SDL_SCANCODE_A);
	d["b"] = cast(SDL_SCANCODE_B);
	d["c"] = cast(SDL_SCANCODE_C);
	d["d"] = cast(SDL_SCANCODE_D);
	d["e"] = cast(SDL_SCANCODE_E);
	d["f"] = cast(SDL_SCANCODE_F);
	d["g"] = cast(SDL_SCANCODE_G);
	d["h"] = cast(SDL_SCANCODE_H);
	d["i"] = cast(SDL_SCANCODE_I);
	d["j"] = cast(SDL_SCANCODE_J);
	d["k"] = cast(SDL_SCANCODE_K);
	d["l"] = cast(SDL_SCANCODE_L);
	d["m"] = cast(SDL_SCANCODE_M);
	d["n"] = cast(SDL_SCANCODE_N);
	d["o"] = cast(SDL_SCANCODE_O);
	d["p"] = cast(SDL_SCANCODE_P);
	d["q"] = cast(SDL_SCANCODE_Q);
	d["r"] = cast(SDL_SCANCODE_R);
	d["s"] = cast(SDL_SCANCODE_S);
	d["t"] = cast(SDL_SCANCODE_T);
	d["u"] = cast(SDL_SCANCODE_U);
	d["v"] = cast(SDL_SCANCODE_V);
	d["w"] = cast(SDL_SCANCODE_W);
	d["x"] = cast(SDL_SCANCODE_X);
	d["y"] = cast(SDL_SCANCODE_Y);
	d["z"] = cast(SDL_SCANCODE_Z);

	d["1"] = cast(SDL_SCANCODE_1);
	d["2"] = cast(SDL_SCANCODE_2);
	d["3"] = cast(SDL_SCANCODE_3);
	d["4"] = cast(SDL_SCANCODE_4);
	d["5"] = cast(SDL_SCANCODE_5);
	d["6"] = cast(SDL_SCANCODE_6);
	d["7"] = cast(SDL_SCANCODE_7);
	d["8"] = cast(SDL_SCANCODE_8);
	d["9"] = cast(SDL_SCANCODE_9);
	d["0"] = cast(SDL_SCANCODE_0);

	d["Return"] = cast(SDL_SCANCODE_RETURN);
	d["Enter"] = cast(SDL_SCANCODE_RETURN);
	d["Esc"] = cast(SDL_SCANCODE_ESCAPE);
	d["Escape"] = cast(SDL_SCANCODE_ESCAPE);
	d["Backspace"] = cast(SDL_SCANCODE_BACKSPACE);
	d["Tab"] = cast(SDL_SCANCODE_TAB);
	d["Space"] = cast(SDL_SCANCODE_SPACE);

	d["-"] = cast(SDL_SCANCODE_MINUS);
	d["="] = cast(SDL_SCANCODE_EQUALS);
	d["["] = cast(SDL_SCANCODE_LEFTBRACKET);
	d["]"] = cast(SDL_SCANCODE_RIGHTBRACKET);
	d["\\"] = cast(SDL_SCANCODE_BACKSLASH);

	d[";"] = cast(SDL_SCANCODE_SEMICOLON);
	d["'"] = cast(SDL_SCANCODE_APOSTROPHE);
	d["`"] = cast(SDL_SCANCODE_GRAVE);
	
	d[","] = cast(SDL_SCANCODE_COMMA);
	d["."] = cast(SDL_SCANCODE_PERIOD);
	d["/"] = cast(SDL_SCANCODE_SLASH);

	d["Caps Lock"] = cast(SDL_SCANCODE_CAPSLOCK);

	d["F1"] = cast(SDL_SCANCODE_F1);
	d["F2"] = cast(SDL_SCANCODE_F2);
	d["F3"] = cast(SDL_SCANCODE_F3);
	d["F4"] = cast(SDL_SCANCODE_F4);
	d["F5"] = cast(SDL_SCANCODE_F5);
	d["F6"] = cast(SDL_SCANCODE_F6);
	d["F7"] = cast(SDL_SCANCODE_F7);
	d["F8"] = cast(SDL_SCANCODE_F8);
	d["F9"] = cast(SDL_SCANCODE_F9);
	d["F10"] = cast(SDL_SCANCODE_F10);
	d["F11"] = cast(SDL_SCANCODE_F11);
	d["F12"] = cast(SDL_SCANCODE_F12);

	d["Print Screen"] = cast(SDL_SCANCODE_PRINTSCREEN);
	d["PrtSc"] = cast(SDL_SCANCODE_PRINTSCREEN);
	d["Scroll Lock"] = cast(SDL_SCANCODE_SCROLLLOCK);
	d["Pause"] = cast(SDL_SCANCODE_PAUSE);
	d["Insert"] = cast(SDL_SCANCODE_INSERT);

	d["Home"] = cast(SDL_SCANCODE_HOME);
	d["Page Up"] = cast(SDL_SCANCODE_PAGEUP);
	d["Delete"] = cast(SDL_SCANCODE_DELETE);
	d["Del"] = cast(SDL_SCANCODE_DELETE);
	d["End"] = cast(SDL_SCANCODE_END);
	d["Page Down"] = cast(SDL_SCANCODE_PAGEDOWN);
	d["Right"] = cast(SDL_SCANCODE_RIGHT);
	d["Left"] = cast(SDL_SCANCODE_LEFT);
	d["Up"] = cast(SDL_SCANCODE_DOWN);
	d["Down"] = cast(SDL_SCANCODE_UP);
	d["ArrowRight"] = cast(SDL_SCANCODE_RIGHT);
	d["ArrowLeft"] = cast(SDL_SCANCODE_LEFT);
	d["ArrowUp"] = cast(SDL_SCANCODE_DOWN);
	d["ArrowDown"] = cast(SDL_SCANCODE_UP);

	d["Num Lock"] = cast(SDL_SCANCODE_NUMLOCKCLEAR);
	d["Clear"] = cast(SDL_SCANCODE_NUMLOCKCLEAR);

	d["Numpad /"] = cast(SDL_SCANCODE_KP_DIVIDE);
	d["Numpad *"] = cast(SDL_SCANCODE_KP_MULTIPLY);
	d["Numpad -"] = cast(SDL_SCANCODE_KP_MINUS);
	d["Numpad +"] = cast(SDL_SCANCODE_KP_PLUS);
	d["Numpad Enter"] = cast(SDL_SCANCODE_KP_ENTER);
	d["Numpad Return"] = cast(SDL_SCANCODE_KP_ENTER);
	d["Numpad 1"] = cast(SDL_SCANCODE_KP_1);
	d["Numpad 2"] = cast(SDL_SCANCODE_KP_2);
	d["Numpad 3"] = cast(SDL_SCANCODE_KP_3);
	d["Numpad 4"] = cast(SDL_SCANCODE_KP_4);
	d["Numpad 5"] = cast(SDL_SCANCODE_KP_5);
	d["Numpad 6"] = cast(SDL_SCANCODE_KP_6);
	d["Numpad 7"] = cast(SDL_SCANCODE_KP_7);
	d["Numpad 8"] = cast(SDL_SCANCODE_KP_8);
	d["Numpad 9"] = cast(SDL_SCANCODE_KP_9);
	d["Numpad 0"] = cast(SDL_SCANCODE_KP_0);
	d["Numpad ."] = cast(SDL_SCANCODE_KP_PERIOD);

	d["Non-US Backslash"] = cast(SDL_SCANCODE_NONUSBACKSLASH);
	d["Non-US \\"] = cast(SDL_SCANCODE_NONUSBACKSLASH);

	d["Application"] = cast(SDL_SCANCODE_APPLICATION);
	d["Power Button"] = cast(SDL_SCANCODE_POWER);
	d["Power Btn"] = cast(SDL_SCANCODE_POWER);
	d["Power"] = cast(SDL_SCANCODE_POWER);

	d["Numpad Equals"] = cast(SDL_SCANCODE_KP_EQUALS);
	d["Numpad ="] = cast(SDL_SCANCODE_KP_EQUALS);
	d["F13"] = cast(SDL_SCANCODE_F13);
	d["F14"] = cast(SDL_SCANCODE_F14);
	d["F15"] = cast(SDL_SCANCODE_F15);
	d["F16"] = cast(SDL_SCANCODE_F16);
	d["F17"] = cast(SDL_SCANCODE_F17);
	d["F18"] = cast(SDL_SCANCODE_F18);
	d["F19"] = cast(SDL_SCANCODE_F19);
	d["F20"] = cast(SDL_SCANCODE_F20);
	d["F21"] = cast(SDL_SCANCODE_F21);
	d["F22"] = cast(SDL_SCANCODE_F22);
	d["F23"] = cast(SDL_SCANCODE_F23);
	d["F24"] = cast(SDL_SCANCODE_F24);
	d["Execute"] = cast(SDL_SCANCODE_EXECUTE);
	d["Exec"] = cast(SDL_SCANCODE_EXECUTE);
	d["Help"] = cast(SDL_SCANCODE_HELP);
	d["Menu"] = cast(SDL_SCANCODE_MENU);
	d["Select"] = cast(SDL_SCANCODE_SELECT);
	d["AC Stop"] = cast(SDL_SCANCODE_STOP);
	d["AC Redo/Repeat"] = cast(SDL_SCANCODE_AGAIN);
	d["AC Undo"] = cast(SDL_SCANCODE_UNDO);
	d["AC Cut"] = cast(SDL_SCANCODE_CUT);
	d["AC Copy"] = cast(SDL_SCANCODE_COPY);
	d["AC Paste"] = cast(SDL_SCANCODE_PASTE);
	d["AC Find"] = cast(SDL_SCANCODE_FIND);
	d["Mute"] = cast(SDL_SCANCODE_MUTE);
	d["Volume Up"] = cast(SDL_SCANCODE_VOLUMEUP);
	d["Volume Down"] = cast(SDL_SCANCODE_VOLUMEDOWN);

	d["Numpad ,"] = cast(SDL_SCANCODE_KP_COMMA);
	d["Equals As 400"] = cast(SDL_SCANCODE_KP_EQUALSAS400);

	d["Erase-Eaze"] = cast(SDL_SCANCODE_ALTERASE);
	d["Alt Erase"] = cast(SDL_SCANCODE_ALTERASE);
	d["Sys Request"] = cast(SDL_SCANCODE_SYSREQ);
	d["SysRq"] = cast(SDL_SCANCODE_SYSREQ);
	d["Cancel"] = cast(SDL_SCANCODE_CANCEL);
	d["Clear"] = cast(SDL_SCANCODE_CLEAR);
	d["Prior"] = cast(SDL_SCANCODE_PRIOR);
	d["Enter2"] = cast(SDL_SCANCODE_RETURN2);
	d["Return2"] = cast(SDL_SCANCODE_RETURN2);
	d["Separator"] = cast(SDL_SCANCODE_SEPARATOR);
	d["Out"] = cast(SDL_SCANCODE_OUT);
	d["Oper"] = cast(SDL_SCANCODE_OPER);
	d["Clear Again"] = cast(SDL_SCANCODE_CLEARAGAIN);
	d["CRSEL"] = cast(SDL_SCANCODE_CRSEL);
	d["EXSEL"] = cast(SDL_SCANCODE_EXSEL);

	d["Left Ctrl"] = cast(SDL_SCANCODE_LCTRL);
	d["Left Shift"] = cast(SDL_SCANCODE_LSHIFT);
	d["Left Alt"] = cast(SDL_SCANCODE_LALT);
	d["Left GUI"] = cast(SDL_SCANCODE_LGUI);
	d["Right Ctrl"] = cast(SDL_SCANCODE_RCTRL);
	d["Right Shift"] = cast(SDL_SCANCODE_RSHIFT);
	d["Right Alt"] = cast(SDL_SCANCODE_RALT);
	d["Right GUI"] = cast(SDL_SCANCODE_RGUI);

	return d;
}

END