#pragma once
#ifndef WINDOW
#define WINDOW
#include <memory>
#include <queue>
#include <string>

#include <SDL3/SDL.h>

#include "DrawCommand.h"
#include "FuncTypes.h"
#include "macro.h"
#include "TextArea.h"
#include "WindowEventHandler.h"

NAMESPACE

extern bool windowDestroyed;
extern bool inWinUpdate;

//This is the Window class. It handles resizing and drawing.
class Window {
protected:
	//SDL pointers for the window
	SDL_Window* win;
	SDL_Renderer* ren;

	/*
		The event handler - WindowEventHandler needs a
		direct pointer to the Window instance, and thus,
		needs to be destroyed at the same time as the Window.
		This was the simplest way I could think of.
	*/
	WindowEventHandler handler;

	//Name of the window
	std::string name;
	//Window dimensions
	int width = 0, height = 0;
	//Attributes for creating a window
	Uint8 attr = 0;

	//Background color
	int bgR = 0, bgG = 0, bgB = 0, bgA = 255;
	//Has the background color changed?
	bool bgChanged = false;
	//Current color
	int r, g, b, a;

	//Is there a saved screen?
	bool savedFrame = false;

	//Canvas for drawing
	SDL_Texture* canvas;
	//Texture for when save() is called to store the current frame
	SDL_Texture* savedBuffer;

	//A queue for DrawCommands - used when things are drawn in the event loop
	std::queue<DrawCommand> cache;

	//Construct the window. This is the same every time.
	void construct();
	//Construct the window for the first time.
	void construct(int width_, int height_, std::string name_);

	//Construct and return a buffer
	SDL_Texture* constructBuffer();

	//Destroy the SDL window and renderer
	void destroySDLWin();
public:
	//The actual width and height of the window - useful for when maximized
	int realWidth = 0, realHeight = 0;
	//The SDL_Window's ID
	SDL_WindowID id = 0;

	//Is the window destroyed?
	bool destroyed = false;

	//Update function
	func update;

	//Construct canvas and savedBuffer
	void constructBuffers();

	//Destroy canvas and savedBuffer
	void destroyBuffers();

	/*
		Construct the Window immediately.

		\param const char* name: the name of the window.

		\param int _width: the width of the window, in pixels.

		\param int _height: the height of the window, in pixels.
	*/
	Window(std::string name_, int width_, int height_);
	//Creates an empty window instance with the default width and height of an HTML canvas
	Window();
	//Destructor
	~Window();
	/*
		This sets the destroyed property to true. Before
		the current cycle ends, this window will be destroyed.
	*/
	void destroy();

	/*
		Set the background color of the window. Warning: if you have
		called save() previously in the current frame, it will not be
		drawn after the call to setBgColor(). This is because save()
		would completely overwrite the background color, resulting in
		no visual change at all.

		\param int r: red value from 0 - 255

		\param int g: green value from 0 - 255

		\param int b: blue value from 0 - 255

		\param int a: alpha value from 0 - 255
	*/
	void setBgColor(int r, int g, int b, int a = 255);

	/*
		Make the window resizable.

		\param bool set: set it to resizable or not?

		\returns void
	*/
	void setResizable(bool set = true);

	/*
		Minimize the window. May have no effect if on fullscreen,
		according to the SDL documentation.

		\param bool set: set it to minimized or not?

		\returns void
	*/
	void setMinimized(bool set = true);

	/*
		Maximize the window.

		\param bool set: set it to maximized or not?

		\returns void
	*/
	void setMaximized(bool set = true);

	/*
		Resize the window.

		\param int newW: the new width of the window.

		\param int newH: the new height of the window.

		\returns void
	*/
	void resize(int newW, int newH);

	//Size getters

	/*
		Get the size of the window.

		\param int* width: a pointer to the width variable.

		\param int* height: a pointer to the height variable.

		\returns void
	*/
	void getSize(int* width, int* height);

	//Drawing functions

	/*
		Set the current drawing color.

		\param int r: red

		\param int g: green

		\param int b: blue

		\param int a: alpha
	*/
	void setColor(int r, int g, int b, int a = 255);
	
	//Draw a point at (x, y)
	void point(int x, int y);
	//Draw a line from (x1, y1) to (x2, y2)
	void line(int x1, int y1, int x2, int y2);
	//Draw a filled rectangle at (x, y)
	void fillRect(int x, int y, int width, int height);
	//Draw the outline of a rectangle at (x, y)
	void strokeRect(int x, int y, int width, int height);
	//Draw text at (x, y)
	void text(TextArea& text, int x, int y, int width = 0, int height = 0);

	//Run each drawing command stored in cache
	void dumpCache();

	//Save the current frame to be used as the background for the next. setBgColor() overrides this behavior.
	void save();
	//Clear the current frame
	void clear();
	//Show the current frame
	void show();

	//Get the WindowEventHandler
	WindowEventHandler* getHandle();
};

//This holds all window instances.
extern std::vector<std::unique_ptr<Window>> windows;

typedef std::pair<Window*, WindowEventHandler*> winEventPair;
/*
	Creates a Window by creating a unique pointer
	to the instantiation and moving it to the windows
	vector.

	\param const char* name: the name of the window.

	\param int width: the width of the window.

	\param int height: the height of the window.
*/
winEventPair createWindow(
	std::string name = "gamesR2simple window",
	int width = 200,
	int height = 100
);

END
#endif