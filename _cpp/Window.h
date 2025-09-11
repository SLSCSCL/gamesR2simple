#pragma once
#ifndef WINDOW_
#define WINDOW_
#include <pybind11/typing.h>
#include <SDL3/SDL.h>
#include <vector>

class Window;

extern std::vector<Window*> windows;

class Window {
private:
	SDL_Window* win;
	SDL_Renderer* ren;

	const char* name;
	int width, height, attr = 0;
	Uint32 id;

public:
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

#endif