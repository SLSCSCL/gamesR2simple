#include "common.h"

std::vector<Window*> windows;

Window::Window(const char* name_, int width_, int height_) : name(name_) {
	width = width_;
	height = height_;
	win = SDL_CreateWindow(name, width, height, SDL_WINDOW_MAXIMIZED);
	ren = SDL_CreateRenderer(win, nullptr);
	id = SDL_GetWindowID(win);
	windows.push_back(this);
}

Window::~Window() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	//Remove this window from the window list
	windows.erase(std::remove(windows.begin(), windows.end(), this), windows.end());
}

void Window::destroy() {
	this->~Window();
}

void Window::setResizable(bool set) {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	if (set) attr |= SDL_WINDOW_RESIZABLE;
	else attr ^= SDL_WINDOW_RESIZABLE;
	win = SDL_CreateWindow(name, width, height, attr);
	ren = SDL_CreateRenderer(win, nullptr);
	id = SDL_GetWindowID(win);
}

void Window::setMinimized(bool set) {
	setResizable(true);
	SDL_MinimizeWindow(win);
}

void Window::setMaximized(bool set) {
	setResizable(true);
	SDL_MaximizeWindow(win);
}

void Window::resize(int newW, int newH) {
	if (attr & SDL_WINDOW_RESIZABLE) {
		win = SDL_CreateWindow(name, newW, newH, attr);
		ren = SDL_CreateRenderer(win, nullptr);
		id = SDL_GetWindowID(win);
	}
}
void Window::getSize(int* width, int* height) {
	SDL_GetWindowSize(win, width, height);
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
	SDL_FRect r{};
	r.x = x;
	r.y = y;
	r.w = width;
	r.h = height;
	SDL_RenderLine(ren, x, y, x + width, y);                   // -------
	SDL_RenderLine(ren, x, y + height, x, y);                  // |
	SDL_RenderLine(ren, x + width, y, x + width, y + height);  //       |
	SDL_RenderLine(ren, x + width, y + height, x, y + height); // -------
}

void Window::clear() {
	SDL_RenderClear(ren);
}

void Window::show() {
	SDL_RenderPresent(ren);
}

WindowEventHandler* Window::getHandle() {
	return &handler;
}

void quit() {
	for (Window* win : windows)
		win->~Window();
	windows.clear();
	SDL_Quit();
}

Events* Events::self = nullptr;
Events::Events() {
	assert(self == nullptr);
	self = this;
}

void Events::checkMD(WindowEventHandler* handler, float x, float y, Uint8 btn) {
	mouse list = *(handler->mousedown);
	py::function func;
	py::tuple point = py::make_tuple(x, y);
	MouseEvents type;
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
	default:
		type = MouseEvents::NONE;
	}
	if (list.find(type) != list.end()) //MouseEvents::NONE will never have a callback
		list[type]();
}

void Events::checkKD(WindowEventHandler* handler, SDL_Keycode keycode) {
	key keys = *(handler->keydown);
	if (keys.find(keycode) != keys.end())
		keys[keycode]();
}

void Events::checkKH(WindowEventHandler* handler) {
	const bool* state = SDL_GetKeyboardState(nullptr);

}

void Events::checkEvents() {
	Window* winPtr = nullptr;
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		for (Window* win : windows)
			if (win->id == e.window.windowID) {
				winPtr = win;
				break;
			}

		switch (e.type) {
		case SDL_EVENT_QUIT:
			winPtr->~Window();
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			self->checkMD(winPtr->getHandle(), e.button.x, e.button.y, e.button.button);
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			break;
		case SDL_EVENT_KEY_DOWN:
			self->checkKD(winPtr->getHandle(), e.key.key);
			break;
		case SDL_EVENT_KEY_UP:
			break;
		}
	}
	for (Window* win : windows) {
		if (!win->getHandle()->keyhold->empty())
			self->checkKH(win->getHandle());
	}

}

WindowEventHandler::WindowEventHandler(Window* _win) : 
	win(_win),
	mousedown(make_shared<mouse>()),
	umousedown(make_shared<mouse>()),
	mousedrag(make_shared<mouse>()),
	umousedrag(make_shared<mouse>()),
	keydown(make_shared<key>()),
	keyhold(make_shared<key>()),
	quit(make_shared<key>()),
	keycombos(make_shared<combos>()),
	mousekeycombos(make_shared<combos>())
{}

void WindowEventHandler::addME(MouseEvents type, py::function callback, bool utility) {
	mouse events;
	switch (type) {
	case MouseEvents::L_CLICK:
	case MouseEvents::R_CLICK:
	case MouseEvents::WHL_CLICK:
		events = *(utility ? umousedown : mousedown);
		events[type] = callback;
		break;
	case MouseEvents::L_DRAG:
	case MouseEvents::R_DRAG:
	case MouseEvents::WHL_DRAG:
		events = *(utility ? umousedrag : mousedrag);
		events[type] = callback;
		break;
	case MouseEvents::MOUSE_MOVE:
		break;
	case MouseEvents::MOUSE_UP:
		break;
	}
}
void WindowEventHandler::addKE(KeyEvents type, int key, py::function callback) {
	
}

std::vector<py::function> updateFuncs;

void update() {
	for (auto& func : updateFuncs)
		func();
}