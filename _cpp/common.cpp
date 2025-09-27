#include "common.h"

std::vector<Window*> windows;

Window::Window(const char* name_, int width_, int height_) : name(name_) {
	width = width_;
	height = height_;
	win = SDL_CreateWindow(name, width, height, 0);
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

void Window::quit() {
	this->~Window();
}

void Window::setResizable(bool set) {
	if (set) attr |= SDL_WINDOW_RESIZABLE;
	else attr ^= SDL_WINDOW_RESIZABLE;
	win = SDL_CreateWindow(name, width, height, attr);
	ren = SDL_CreateRenderer(win, nullptr);
	id = SDL_GetWindowID(win);
}

void Window::setMinimized(bool set) {
	if (set) attr |= SDL_WINDOW_MINIMIZED;
	else attr ^= SDL_WINDOW_MINIMIZED;

	win = SDL_CreateWindow(name, width, height, attr);
	ren = SDL_CreateRenderer(win, nullptr);
	id = SDL_GetWindowID(win);
}

void Window::setMaximized(bool set) {
	if (set) attr |= SDL_WINDOW_MAXIMIZED;
	else attr ^= SDL_WINDOW_MAXIMIZED;

	win = SDL_CreateWindow(name, width, height, attr);
	ren = SDL_CreateRenderer(win, nullptr);
	id = SDL_GetWindowID(win);
}

void Window::resize(int newW, int newH) {
	if (attr & SDL_WINDOW_RESIZABLE) {
		win = SDL_CreateWindow(name, newW, newH, attr);
		ren = SDL_CreateRenderer(win, nullptr);
		id = SDL_GetWindowID(win);
	}
}
void Window::getSize(int& width, int& height) {
	SDL_GetWindowSize(win, &width, &height);
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
	SDL_RenderLine(ren, x + width, y, x + width, y + height);  //       |
	SDL_RenderLine(ren, x + width, y + height, x, y + height); // -------
	SDL_RenderLine(ren, x, y + height, x, y);                  // |
}

void Window::clear() {
	SDL_RenderClear(ren);
}

void Window::show() {
	SDL_RenderPresent(ren);
}

void quit() {
	for (Window* win : windows) {
		win->~Window();
	}
	windows.clear();
	SDL_Quit();
}


Event::Event(
	Window* w,
	WindowEventHandler* h,
	MouseEvents e,
	PyFunctionObject& c
) : win(w), handler(h), callback(c) {
	event = (int)e;
}
Event::Event(
	Window* w,
	WindowEventHandler* h,
	KeyEvents e,
	PyFunctionObject& c
) : win(w), handler(h), callback(c) {
	event = (int)e;
}

Events* Events::self = nullptr;
Events::Events() {
	assert(self == nullptr);
	self = this;
}

void Events::add(EventType type, Event e) {
	auto& events = self->events;
	if (events.find(type) == events.end())
		events[type] = vec{};
	events[type].push_back(e);
}

void Events::checkMD(vec* events, Uint32 id) {
	for (auto& e : *(events)) {
		if (e.win->id == id) {
			//Find out how to call e.callback
		}
	}
}

void Events::checkEvents() {
	auto& events = self->events;

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		Uint32 id = e.window.windowID;
		switch (e.type) {
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			self->checkMD(&events[EventType::MOUSE], id);
		}
	}
}

WindowEventHandler::WindowEventHandler(Window* _win) : win(_win) {}

void WindowEventHandler::addME(MouseEvents type, PyFunctionObject& callback) {
	Events::add(EventType::MOUSE, Event(win, this, type, callback));
}
void WindowEventHandler::addKE(KeyEvents type, int key, PyFunctionObject& callback) {
	Events::add(EventType::KEY, Event(win, this, type, callback));
}