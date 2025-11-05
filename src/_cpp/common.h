#pragma once
#include <assert.h>
#include <map>
#include <memory>
#include <vector>
#include <Python.h>
#include <pybind11/typing.h>
#include <pybind11/pybind11.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include "Combinations.h"
#include "KeyCodes.h"
using namespace std;
namespace py = pybind11;

enum class MouseEvents {
	MOUSE_MOVE,
	MOUSE_UP,
	L_CLICK,
	R_CLICK,
	WHL_CLICK,
	L_DRAG,
	R_DRAG,
	WHL_DRAG,
	BACK_THUMB,
	FWD_THUMB,
	NONE //Only for use in common.cpp
};
enum class KeyEvents {
	KEY_UP,
	KEY_DOWN,
	KEY_HOLD
};

class Window;
extern std::vector<Window*> windows;

class WindowEventHandler;

using mouse = map<MouseEvents, py::function>;
using key = map<SDL_Keycode, py::function>;
using combos = vector<Combination>;

class WindowEventHandler {
private:
	Window* win;
public:
	shared_ptr<mouse> mousedown, umousedown, mousedrag, umousedrag;
	shared_ptr<key> keydown, keyhold, quit;
	shared_ptr<combos> keycombos, mousekeycombos;

	WindowEventHandler(Window* _win);

	void addME(MouseEvents type, py::function callback, bool utility = false);
	void addKE(KeyEvents type, int key, py::function callback);
};


class Window {
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	WindowEventHandler handler{this};

	const char* name;
	int width, height, attr = 0;

public:
	SDL_WindowID id;

	template<typename... Args>
	Window(Args... args) {}
	Window(const char* name_, int width_, int height_);
	~Window();
	void destroy();

	void setResizable(bool set);
	void setMinimized(bool set);
	void setMaximized(bool set);

	void resize(int newW, int newH);
	void getSize(int* width, int* height);
	py::tuple getSize();

	void setColor(int r, int g, int b, int a = 255);
	void point(int x, int y);
	void line(int x1, int y1, int x2, int y2);
	void fillRect(int x, int y, int width, int height);
	void strokeRect(int x, int y, int width, int height);

	void clear();
	void show();

	WindowEventHandler* getHandle();
};

void quit();

enum class MouseBtns {
	LEFT,
	RIGHT,
	WHL,
	BACK_THUMB,
	FWD_THUMB
};

class Events {
private:
	map<MouseBtns, bool> pressedBtns;

	static Events* self;

	static void checkMD(WindowEventHandler* handler, float x, float y, Uint8 btn);
	static void checkKD(WindowEventHandler* handler, SDL_Keycode key);
	static void checkKH(WindowEventHandler* handler);
public:
	Events();

	static void checkEvents();
};

extern std::vector<py::function> updateFuncs;

void update();