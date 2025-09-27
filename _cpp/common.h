#pragma once
#ifndef WINDOW_
#define WINDOW_
#include <assert.h>
#include <map>
#include <vector>
#include <Python.h>
#include <pybind11/typing.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include "KeyCodes.h"

enum class MouseEvents {
	MOUSE_MOVE,
	MOUSE_UP,
	L_CLICK,
	R_CLICK,
	WHL_CLICK,
	L_DRAG,
	R_DRAG,
	WHL_DRAG
};
enum class KeyEvents {
	KEY_UP = 8,
	KEY_DOWN,
	KEY_HOLD
};

enum class EventType {
	MOUSE,
	KEY,
	MOUSE_KEY,
	KEY_KEY,
	UTILITY_MOUSE,
	UTILITY_KEY,
	UTILITY_MOUSE_KEY,
	UTILITY_KEY_KEY,
};

class Window;
extern std::vector<Window*> windows;

class WindowEventHandler {
private:
	Window* win;
public:
	WindowEventHandler(Window* _win);

	void addME(MouseEvents type, PyFunctionObject& callback);
	void addKE(KeyEvents type, int key, PyFunctionObject& callback);
};


class Window {
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	WindowEventHandler handler{this};

	const char* name;
	int width, height, attr = 0;

public:
	Uint32 id;

	template<typename... Args>
	Window(Args... args) {}
	Window(const char* name_, int width_, int height_);
	~Window();
	void quit();

	void setResizable(bool set);
	void setMinimized(bool set);
	void setMaximized(bool set);

	void resize(int newW, int newH);
	void getSize(int& width, int& height);

	void setColor(int r, int g, int b, int a = 255);
	void point(int x, int y);
	void line(int x1, int y1, int x2, int y2);
	void fillRect(int x, int y, int width, int height);
	void strokeRect(int x, int y, int width, int height);

	void clear();
	void show();
};

void quit();

class WindowEventHandler;

class Event {
public:
	int event;
	Window* win;
	WindowEventHandler* handler;
	PyFunctionObject& callback;

	Event(Window* w, WindowEventHandler* h, MouseEvents e, PyFunctionObject& c);
	Event(Window* w, WindowEventHandler* h, KeyEvents e, PyFunctionObject& c);
};

using vec = std::vector<Event>;

class Events {
private:
	std::map<EventType, vec> events{};

	static Events* self;

	static void checkMD(vec* events, Uint32 id);
public:
	Events();
	static void add(EventType type, Event e);

	static void checkEvents();
};


#endif