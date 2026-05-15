#pragma once
#ifndef EVENTS
#define EVENTS
#include <assert.h>
#include <map>

#include <SDL3/SDL_events.h>

#include "KeyCodes.h"
#include "macro.h"
#include "Window.h"
#include "WindowEventHandler.h"

NAMESPACE

class Events {
private:
	std::map<Uint8, bool> pressedBtns;
	keyMap* keys;
	std::map<int, bool> heldKeys;

	static Events* self;

	static void checkMD(WindowEventHandler* handler, int x, int y, Uint8 btn);
	static void checkMM(WindowEventHandler* handler, int x, int y);
	static bool checkMDrag(WindowEventHandler* handler, int x, int y);
	static void checkSE(WindowEventHandler* handler, int dir);
	static void checkKD(WindowEventHandler* handler, SDL_Scancode keycode);
	static void checkKH(WindowEventHandler* handler, bool u = false);
public:
	Events(keyMap* _keys);

	static void checkEvents();
};

END
#endif