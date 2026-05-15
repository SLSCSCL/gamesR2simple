#include "Events.h"
#include "gamesR2simple.h"

NAMESPACE

/*
	The Events class handles all events.
*/

Events* Events::self = nullptr;
Events::Events(keyMap* _keys) : keys(_keys) {
	assert(self == nullptr);
	self = this;
	for (auto& kv : *(self->keys))
		self->heldKeys[kv.second] = false;
}

void Events::checkMD(WindowEventHandler* handler, int x, int y, Uint8 btn) {
	MouseEvents type = MouseEvents::NONE;
	switch (btn) {
	case SDL_BUTTON_LEFT:
		type = MouseEvents::L_CLICK;
		break;
	case SDL_BUTTON_RIGHT:
		type = MouseEvents::R_CLICK;
		break;
	case SDL_BUTTON_MIDDLE:
		type = MouseEvents::WHL_CLICK;
		break;
	case SDL_BUTTON_X1:
		type = MouseEvents::BACK_THUMB;
		break;
	case SDL_BUTTON_X2:
		type = MouseEvents::FWD_THUMB;
		break;
	}

	self->pressedBtns[btn] = true;

	//Utility events
	for (auto& pair : *handler->umousedown)
		if (pair.second.find(type) != pair.second.end())
			pair.second[type](x, y);

	//Regular events
	auto& list = handler->mousedown;
	if (list->find(type) != list->end())
		(*list)[type](x, y);

	//Mouse-key combinations
	for (MouseKeyCombination& combo : *handler->mousekeycombos)
		if (self->heldKeys[combo.key])
			combo(x, y);
}

void Events::checkMM(WindowEventHandler* handler, int x, int y) {
	handler->mousemove(x, y);
}

bool Events::checkMDrag(WindowEventHandler* handler, int x, int y) {
	mouse* mousedrag = handler->mousedrag.get();
	bool foundDragEvent = false;

	MouseEvents type;
	for (auto& btnPair : self->pressedBtns) {
		if (!btnPair.second) continue;

		type = MouseEvents::NONE;
		switch (btnPair.first) {
		case SDL_BUTTON_LEFT:
			type = MouseEvents::L_DRAG;
			break;
		case SDL_BUTTON_RIGHT:
			type = MouseEvents::R_DRAG;
			break;
		case SDL_BUTTON_MIDDLE:
			type = MouseEvents::WHL_DRAG;
			break;
		}

		//Utility events
		for (auto& pair : *handler->umousedrag)
			if (btnPair.second && pair.second.find(type) != pair.second.end()) {
				pair.second[type](x, y);
				foundDragEvent = true;
			}

		if (mousedrag->find(type) != mousedrag->end()) {
			(*mousedrag)[type](x, y);
			foundDragEvent = true;
		}
	}
	return foundDragEvent;
}

void Events::checkSE(WindowEventHandler* handler, int dir) {
	for (auto& pair : *handler->uscroll)
		pair.second(dir);
	handler->scroll(dir);
}

void Events::checkKD(WindowEventHandler* handler, SDL_Scancode keycode) {
	self->heldKeys[keycode] = true;
	auto& keys = handler->keydown;
	auto& quit = handler->quit;

	handler->keydownhandler(keycode);

	//Quit events
	if (quit->find(keycode) != quit->end())
		handler->win->destroy();

	//Keydown events
	if (keys->find(keycode) != keys->end())
		(*keys)[keycode]();

	//Utility keydown events
	for (auto& pair : *handler->ukeydown)
		if (pair.second.find(keycode) != pair.second.end())
			pair.second[keycode]();

	//Key combination events
	for (KeyCombination& combo : *handler->keycombos)
		if (self->heldKeys[combo.key1] &&
			self->heldKeys[combo.key2] &&
			(self->heldKeys[combo.key3] || combo.key3 == 0)) combo();
}

void Events::checkKH(WindowEventHandler* handler, bool u) {
	const bool* state = SDL_GetKeyboardState(nullptr);
	int code;
	auto& events = handler->keyhold;
	for (auto& kv : *(self->keys)) {
		code = kv.second;
		if (state[code]) {
			if (events->find(code) != events->end())
				(*events)[code]();
			for (auto& pair : *handler->ukeyhold)
				pair.second[code]();
			handler->keyholdhandler(code);
		}
	}
}

void Events::checkEvents() {
	Window* winPtr;
	WindowEventHandler* handler;
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		winPtr = nullptr;
		for (auto it = windows.begin(); it != windows.end(); ++it) {
			winPtr = it->get();
			if (winPtr->id == e.window.windowID) break; //We have found our target

			winPtr = nullptr;
		}
		if (!winPtr) continue;
		handler = winPtr->getHandle();

		switch (e.type) {
		case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
			winPtr->realWidth = e.window.data1;
			winPtr->realHeight = e.window.data2;
			winPtr->constructBuffers();
			break;
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			winPtr->destroy();
			break;
		case SDL_EVENT_QUIT:
			quit();
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			self->checkMD(handler, e.button.x, e.button.y, e.button.button);
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			self->pressedBtns[e.button.button] = false;
			handler->mouseup(e.button.x, e.button.y);
			break;
		case SDL_EVENT_MOUSE_MOTION:
			//Make sure that we don't fire a mousemove event if the mouse is dragging
			if (!self->checkMDrag(handler, e.motion.x, e.motion.y))
				self->checkMM(handler, e.motion.x, e.motion.y);
			break;
		case SDL_EVENT_MOUSE_WHEEL:
			self->checkSE(handler, e.wheel.integer_y);
			break;
		case SDL_EVENT_KEY_DOWN:
			self->checkKD(handler, SDL_GetScancodeFromKey(e.key.key, nullptr));
			break;
		case SDL_EVENT_KEY_UP:
			self->heldKeys[SDL_GetScancodeFromKey(e.key.key, nullptr)] = false;
			break;
		}
	}
	for (auto& win : windows) {
		handler = win->getHandle();
		if (!handler->keyhold->empty())
			self->checkKH(handler);
		if (!handler->ukeyhold->empty())
			self->checkKH(handler, true);
	}
}

END