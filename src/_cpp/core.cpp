// See core.h for detailed documentation.

#include "core.h"

NAMESPACE

std::vector<unique_ptr<Window>> windows;

/*
	Functions that do nothing - they are placeholders.
*/

void doNothing() {}
void doNothingi(int a) {}
void doNothingTup(py::tuple t) {}

/*
	The QuitEvent class. It just holds a QuitEvent.
*/

QuitEvent::QuitEvent(Window* win, keycall call) : window(win), callback(call) {}

QuitEvent* QuitEvent::instance() {
	return this;
}

void QuitEvent::operator()() {
	callback();
	window->destroy();
}

void QuitEvent::operator=(const QuitEvent& other) {
	callback = other.callback;
	window = other.window;
}

/*
	The WindowEventHandler. Like the name implies, it handles the events for a specific Window.
*/

WindowEventHandler::WindowEventHandler(Window* _win) :
	win(_win),
	mousedown(make_shared<mouse>()),
	umousedown(make_shared<umouse>()),
	mousedrag(make_shared<mouse>()),
	umousedrag(make_shared<umouse>()),
	uscroll(make_shared<Uscroll>()),
	keydown(make_shared<key>()),
	keyhold(make_shared<key>()),
	quit(make_shared<Quit>()),
	ukeydown(make_shared<ukey>()),
	ukeyhold(make_shared<ukey>()),
	keycombos(make_shared<kcombos>()),
	mousekeycombos(make_shared<mkcombos>())
{
	scroll = doNothingi; 
	mouseup = doNothing; 
	mousemove = doNothingTup;
	keyhandle = doNothingi;
}

void WindowEventHandler::addME(MouseEvents type, mousecall callback) {
	switch (type) {
	case MouseEvents::L_CLICK:
	case MouseEvents::R_CLICK:
	case MouseEvents::WHL_CLICK:
		(*mousedown)[type] = callback;
		break;
	case MouseEvents::L_DRAG:
	case MouseEvents::R_DRAG:
	case MouseEvents::WHL_DRAG:
		(*mousedrag)[type] = callback;
		break;
	case MouseEvents::MOUSE_MOVE:
		mousemove = callback;
		break;
	case MouseEvents::MOUSE_UP:
		throw ArgumentMismatchError("The mouseup callback should not recieve any parameters.");
		break;
	case MouseEvents::BACK_THUMB:
		break;
	case MouseEvents::FWD_THUMB:
		break;
	default:
		throw TypeError("The 'type' parameter must be of type gamesR2simple.MouseEvents!");
	}
}

void WindowEventHandler::addMU(MouseEvents type, func callback) {
	mouseup = callback;
}

void WindowEventHandler::addMU(func callback) {
	mouseup = callback;
}

void WindowEventHandler::addME(MouseEvents type, mousecall callback, int uid) {
	shared_ptr<umouse> events;
	switch (type) {
	case MouseEvents::L_CLICK:
	case MouseEvents::R_CLICK:
	case MouseEvents::WHL_CLICK:
		events = umousedown;
		break;
	case MouseEvents::L_DRAG:
	case MouseEvents::R_DRAG:
	case MouseEvents::WHL_DRAG:
		events = umousedrag;
		break;
	case MouseEvents::BACK_THUMB:
	case MouseEvents::FWD_THUMB:
		events = umousethumb;
		break;
	default:
		throw TypeError("The 'type' parameter must be of type gamesR2simple.MouseEvents!");
	}
	(*events)[uid][type] = callback;
}

void WindowEventHandler::addSE(scrollcall callback) {
	scroll = callback;
}

void WindowEventHandler::addSE(scrollcall callback, int uid) {
	(*uscroll)[uid] = callback;
}

void WindowEventHandler::addKE(KeyEvents type, keycall callback, int _key) {
	shared_ptr<key> events;
	switch (type) {
	case KeyEvents::KEY_DOWN:
		events = keydown;
		break;
	case KeyEvents::KEY_HOLD:
		events = keyhold;
		break;
	default:
		throw TypeError("The 'type' parameter must be of type gamesR2simple.KeyEvents!");
	}
	(*events)[_key] = callback;
}

void WindowEventHandler::addKE(KeyEvents type, keycall callback, int _key, int uid) {
	shared_ptr<ukey> events;
	switch (type) {
	case KeyEvents::KEY_DOWN:
		events = ukeydown;
		break;
	case KeyEvents::KEY_HOLD:
		events = ukeyhold;
		break;
	default:
		throw TypeError("The 'type' parameter must be of type gamesR2simple.KeyEvents!");
	}
	(*events)[uid][_key] = callback;
}

void WindowEventHandler::addKEH(keyhcall handle) {
	if (keyhandler)
		throw KeyHandlerExistsError("A key event handler has already been declared.");
	keyhandler = true;
	keyhandle = handle;
}

void WindowEventHandler::addQE(int _key, keycall callback) {
	if (keydown->find(_key) == keydown->end()) {
		quit->insert_or_assign(_key, QuitEvent(win, callback));
	}
}

void WindowEventHandler::addKC(KeyCombination combo) {
	keycombos->push_back(combo);
}

void WindowEventHandler::addMKC(MouseKeyCombination combo) {
	mousekeycombos->push_back(combo);
}

void WindowEventHandler::popME(MouseEvents type) {
	switch (type) {
	case MouseEvents::L_CLICK:
	case MouseEvents::R_CLICK:
	case MouseEvents::WHL_CLICK:
		popItem(mousedown, type);
		break;
	case MouseEvents::L_DRAG:
	case MouseEvents::R_DRAG:
	case MouseEvents::WHL_DRAG:
		popItem(mousedrag, type);
		break;
	case MouseEvents::BACK_THUMB:
	case MouseEvents::FWD_THUMB:
		popItem(mousethumb, type);
		break;
	default:
		throw TypeError("The 'type' parameter must be of type gamesR2simple.MouseEvents!");
	}
}

void WindowEventHandler::popUME(MouseEvents type, int uid) {
	switch (type) {
	case MouseEvents::L_CLICK:
	case MouseEvents::R_CLICK:
	case MouseEvents::WHL_CLICK:
		popItem(&(*umousedown)[uid], type);
		break;
	case MouseEvents::L_DRAG:
	case MouseEvents::R_DRAG:
	case MouseEvents::WHL_DRAG:
		popItem(&(*umousedrag)[uid], type);
		break;
	case MouseEvents::BACK_THUMB:
	case MouseEvents::FWD_THUMB:
		popItem(&(*umousethumb)[uid], type);
		break;
	}
}

void WindowEventHandler::popMU() {
	mouseup = doNothing;
}

void WindowEventHandler::popSE() {
	scroll = doNothingi;
}

void WindowEventHandler::popSE(int uid) {
	(*uscroll)[uid] = doNothingi;
}

void WindowEventHandler::popKE(KeyEvents type, int _key) {
	switch (type) {
	case KeyEvents::KEY_DOWN:
		popItem(keydown, _key);
		break;
	case KeyEvents::KEY_HOLD:
		popItem(keyhold, _key);
		break;
	}
}

void WindowEventHandler::popKE(KeyEvents type, int _key, int uid) {
	switch (type) {
	case KeyEvents::KEY_DOWN:
		popItem(&(*ukeydown)[uid], _key);
		break;
	case KeyEvents::KEY_HOLD:
		popItem(&(*ukeyhold)[uid], _key);
		break;
	}
}

void WindowEventHandler::popKEH() {
	keyhandler = false;
	keyhandle = doNothingi;
}

void WindowEventHandler::popQE(int _key) {
	popItem(quit, _key);
}

void WindowEventHandler::popKC(KeyCombination combo) {
	popItem(keycombos, combo);
}

void WindowEventHandler::popMKC(MouseKeyCombination combo) {
	popItem(mousekeycombos, combo);
}

/*
	The Window class acts as a wrapper for SDL_Window and Renderer.
*/

void Window::construct() {
	win = SDL_CreateWindow(name.c_str(), width, height, attr);
	ren = SDL_CreateRenderer(win, nullptr);
	id = SDL_GetWindowID(win);
}

void Window::construct(int width_, int height_, string name_) {
	width = width_;
	height = height_;
	name = name_;
	construct();
}

void Window::destroySDLWin() {
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
}

Window::Window(string name_, int width_, int height_) : handler(this) {
	construct(width_, height_, name_);
}

Window::Window() : name(), handler(this) {
	construct(200, 100, "gamesR2simple window");
}

Window::~Window() {
	destroySDLWin();
}

void Window::destroy() {
	destroySDLWin();
	destroyed = true;
}

void Window::setBgColor(int r, int g, int b, int a) {
	bgR = r;
	bgG = g;
	bgB = b;
	bgA = a;
}

void Window::setResizable(bool set) {
	destroySDLWin();

	if (set) attr |= SDL_WINDOW_RESIZABLE;
	else attr ^= SDL_WINDOW_RESIZABLE;
	
	construct(width, height, name);
}

void Window::setMinimized(bool set) {
	if (set) {
		setResizable(true);
		SDL_MinimizeWindow(win);
	}
}

void Window::setMaximized(bool set) {
	if (set) {
		setResizable(true);
		SDL_MaximizeWindow(win);
	}
}

void Window::resize(int newW, int newH) {
	if (attr & SDL_WINDOW_RESIZABLE) {
		win = SDL_CreateWindow(name.c_str(), newW, newH, attr);
		ren = SDL_CreateRenderer(win, nullptr);
		id = SDL_GetWindowID(win);
	}
}

void Window::getSize(int* width, int* height) {
	SDL_GetWindowSizeInPixels(win, width, height);
}

py::tuple Window::getSize() {
	int w, h;
	getSize(&w, &h);
	return py::make_tuple(w, h);
}

void Window::setColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(ren, r, g, b, a);
}

void Window::point(int x, int y) {
	SDL_RenderPoint(ren, x, y);
}

void Window::line(int x1, int y1, int x2, int y2) {
	SDL_RenderLine(ren, x1, y1, x2, y2);
}

void Window::fillRect(int x, int y, int width, int height) {
	SDL_FRect r{};
	r.x = x;
	r.y = y;
	r.w = width;
	r.h = height;
	SDL_RenderFillRect(ren, &r);
}

void Window::strokeRect(int x, int y, int width, int height) {
	SDL_RenderLine(ren, x, y, x + width, y);                   // -------
	SDL_RenderLine(ren, x, y + height, x, y);                  // |
	SDL_RenderLine(ren, x + width, y, x + width, y + height);  //       |
	SDL_RenderLine(ren, x + width, y + height, x, y + height); // -------
}

void Window::clear() {
	setColor(bgR, bgG, bgB, bgA);
	SDL_RenderClear(ren);
}

void Window::show() {
	SDL_RenderPresent(ren);
}

WindowEventHandler* Window::getHandle() {
	return &handler;
}

/*
	The DialogWindow class creates a window for a
	dialog box, like when you right click.
*/

DialogWindow::DialogWindow(string name_, int width_, int height_, Window* parent_) 
	: parent(parent_) {
	attr = SDL_WINDOW_POPUP_MENU;
	construct(width_, height_, name_);
}

/*
	Creates a Window by creating a unique pointer 
	to the instantiation and move it to the windows
	vector.

	\param const char* name: the name of the window.

	\param int width: the width of the window.

	\param int height: the height of the window.	
*/
winEventPair createWindow(string name, int width, int height) {
	unique_ptr<Window> win = make_unique<Window>(name, width, height);
	windows.push_back(move(win));
	Window* winPtr = windows.back().get();
	return make_pair(winPtr, winPtr->getHandle());
}

/*
	The quit() function stops the entire program.
*/

void quit() {
	windows.clear();
	SDL_Quit();
	_exit(0);
}

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

	py::tuple coord = py::make_tuple(x, y);

	self->pressedBtns[btn] = true;

	//Regular events
	auto& list = handler->mousedown;
	if (list->find(type) != list->end())
		(*list)[type](coord);

	//Utility events
	for (auto& pair : *handler->umousedown)
		if (pair.second.find(type) != pair.second.end())
			pair.second[type](coord);

	//Mouse-key combinations
	for (MouseKeyCombination& combo : *handler->mousekeycombos)
		if (self->heldKeys[combo.key])
			combo(coord);
}

void Events::checkMM(WindowEventHandler* handler, int x, int y) {
	handler->mousemove(py::make_tuple(x, y));
}

void Events::checkMDrag(WindowEventHandler* handler, int x, int y) {
	py::tuple coord = py::make_tuple(x, y);
	shared_ptr<mouse>& mousedrag = handler->mousedrag;

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

		if (mousedrag->find(type) != mousedrag->end())
			(*mousedrag)[type](coord);

		//Utility events
		for (auto& pair : *handler->umousedrag)
			if (btnPair.second && pair.second.find(type) != pair.second.end())
				pair.second[type](coord);
	}
}

void Events::checkSE(WindowEventHandler* handler, int dir) {
	handler->scroll(dir);
	for (auto& pair : *handler->uscroll)
		pair.second(dir);
}

void Events::checkKD(WindowEventHandler* handler, SDL_Scancode keycode) {
	self->heldKeys[keycode] = true;
	auto& keys = handler->keydown;
	auto& quit = handler->quit;

	handler->keyhandle(keycode);

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
			handler->mouseup();
			break;
		case SDL_EVENT_MOUSE_MOTION:
			self->checkMM(handler, e.motion.x, e.motion.y);
			self->checkMDrag(handler, e.motion.x, e.motion.y);
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

std::vector<func> updateFuncs;

void addUpdateFunc(func f) {
	updateFuncs.push_back(f);
}

void updateAll() {
	//Clear all windows
	for (auto& win : windows)
		win->clear();

	//Update
	for (auto& func : updateFuncs)
		func();

	//Show all windows
	for(auto& win : windows)
		win->show();
}

END