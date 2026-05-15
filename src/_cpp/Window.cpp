//See Window.h for detailed documentation
#include "Window.h"

NAMESPACE

/*
	The Window class acts as a wrapper for SDL_Window and Renderer.
*/

bool inWinUpdate = false;
bool windowDestroyed = false;

void Window::construct() {
	win = SDL_CreateWindow(name.c_str(), width, height, attr);
	ren = SDL_CreateRenderer(win, nullptr);
	id = SDL_GetWindowID(win);
}

void Window::construct(int width_, int height_, std::string name_) {
	width = realWidth = width_;
	height = realHeight = height_;
	name = name_;
	construct();
	constructBuffers();
}

SDL_Texture* Window::constructBuffer() {
	return SDL_CreateTexture(
		ren,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		realWidth,
		realHeight
	);
}

void Window::destroySDLWin() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
}

void Window::constructBuffers() {
	if (canvas)
		destroyBuffers(); //Both buffers are created at the same function call, so this is safe

	canvas = constructBuffer();
	savedBuffer = constructBuffer();
}

void Window::destroyBuffers() {
	SDL_DestroyTexture(canvas);
	SDL_DestroyTexture(savedBuffer);
}

Window::Window(std::string name_, int width_, int height_) : handler(this) {
	construct(width_, height_, name_);
}

Window::Window() : name(), handler(this) {
	construct(200, 100, "gamesR2simple window");
}

Window::~Window() {
	destroyBuffers();
	destroySDLWin();
}

void Window::destroy() {
	destroyed = true;
	windowDestroyed = true;
}

void Window::setBgColor(int r, int g, int b, int a) {
	bgR = r;
	bgG = g;
	bgB = b;
	bgA = a;
	bgChanged = true;
	savedFrame = false; //If a frame is saved, it will completely overwrite the new background color.
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
		constructBuffers();
	}
}

void Window::setMaximized(bool set) {
	if (set) {
		setResizable(true);
		SDL_MaximizeWindow(win);
		constructBuffers();
	}
}

void Window::resize(int newW, int newH) {
	if (attr & SDL_WINDOW_RESIZABLE)
		construct(newW, newH, name);
}

void Window::getSize(int* width, int* height) {
	SDL_GetWindowSizeInPixels(win, width, height);
}

void Window::setColor(int _r, int _g, int _b, int _a) {
	SDL_SetRenderDrawColor(ren, _r, _g, _b, _a);
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

void Window::point(int x, int y) {
	if (!inWinUpdate) {
		DrawCommand draw{ ShapeType::POINT, r, g, b, a };
		draw.point = { x, y };

		cache.push(draw);
	}
	else
		SDL_RenderPoint(ren, x, y);
}

void Window::line(int x1, int y1, int x2, int y2) {
	if (!inWinUpdate) {
		DrawCommand draw{ ShapeType::LINE, r, g, b, a };
		draw.line = { x1, y1, x2, y2 };

		cache.push(draw);
	}
	else
		SDL_RenderLine(ren, x1, y1, x2, y2);
}

void Window::fillRect(int x, int y, int width, int height) {
	if (!inWinUpdate) {
		DrawCommand draw{ ShapeType::FILL_RECT, r, g, b, a };
		draw.rect = { x, y, width, height };

		cache.push(draw);
	}
	else {
		SDL_FRect r{};
		r.x = x;
		r.y = y;
		r.w = width;
		r.h = height;
		SDL_RenderFillRect(ren, &r);
	}
}

void Window::strokeRect(int x, int y, int width, int height) {
	if (!inWinUpdate) {
		DrawCommand draw{ ShapeType::STROKE_RECT, r, g, b, a };
		draw.rect = { x, y, width, height };

		cache.push(draw);
	}
	else {
		SDL_RenderLine(ren, x, y, x + width, y);                   // -------
		SDL_RenderLine(ren, x, y + height, x, y);                  // |
		SDL_RenderLine(ren, x + width, y, x + width, y + height);  //       |
		SDL_RenderLine(ren, x + width, y + height, x, y + height); // -------
	}
}

void Window::text(TextArea& text, int x, int y, int width, int height) {
	text.draw(ren, x, y, width, height);
}

void Window::dumpCache() {
	DrawCommand* cmd;
	while (!cache.empty()) {
		cmd = &cache.front();
		setColor(cmd->r, cmd->g, cmd->b, cmd->a);
		switch (cmd->type) {
		case ShapeType::POINT:
			point(cmd->point.x, cmd->point.y);
			break;
		case ShapeType::LINE:
			line(cmd->line.x1, cmd->line.y1, cmd->line.x2, cmd->line.y2);
			break;
		case ShapeType::FILL_RECT:
			fillRect(cmd->rect.x, cmd->rect.y, cmd->rect.w, cmd->rect.h);
			break;
		case ShapeType::STROKE_RECT:
			strokeRect(cmd->rect.x, cmd->rect.y, cmd->rect.w, cmd->rect.h);
			break;
		case ShapeType::FILL_TRI:
			//Not supported yet
			break;
		case ShapeType::STROKE_TRI:
			//Not supported yet
			break;
		}
		cache.pop();
	}
}

void Window::save() {
	if (bgChanged) return;
	SDL_SetRenderTarget(ren, savedBuffer);
	SDL_RenderTexture(ren, canvas, nullptr, nullptr);
	SDL_SetRenderTarget(ren, canvas);
	savedFrame = true;
}

void Window::clear() {
	SDL_SetRenderTarget(ren, canvas);
	setColor(bgR, bgG, bgB, bgA);
	SDL_RenderClear(ren);

	if (savedFrame) {
		SDL_RenderTexture(ren, savedBuffer, nullptr, nullptr);
		savedFrame = false;
	}
	bgChanged = false;
}

void Window::show() {
	SDL_SetRenderTarget(ren, nullptr);
	SDL_RenderTexture(ren, canvas, nullptr, nullptr);
	SDL_RenderPresent(ren);
}

WindowEventHandler* Window::getHandle() {
	return &handler;
}

std::vector<std::unique_ptr<Window>> windows;

/*
	Creates a Window by creating a unique pointer
	to the instantiation and move it to the windows
	vector.

	\param const char* name: the name of the window.

	\param int width: the width of the window.

	\param int height: the height of the window.
*/
winEventPair createWindow(std::string name, int width, int height) {
	windows.push_back(std::make_unique<Window>(name, width, height));
	Window* winPtr = windows.back().get();
	return std::make_pair(winPtr, winPtr->getHandle());
}

END