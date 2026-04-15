#pragma once
#include <assert.h>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

#include "Combinations.h"
#include "Errors.h"
#include "KeyCodes.h"
#include "macro.h"

using namespace std;
namespace py = pybind11;

NAMESPACE

/*
	=========================================================================	
		  Below are the enumerations that contain each type of event.
	=========================================================================
*/

//All possible mouse events are contained in this enum.
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
	NONE //Only for use in core.cpp
};
//All key events are contained here.
enum class KeyEvents {
	KEY_DOWN,
	KEY_HOLD
};


/*
	Below, we have each overload of popItem().
	The popItem() function can erase an item from 
	a std::vector or std::shared_ptr<std::vector>,
	and can also remove an item by key from a 
	std::map or a std::shared_ptr<std::map>.
*/

//This erases an item from a std::vector
#define VEC_ERASE obj->erase(remove(obj->begin(), obj->end(), item), obj->end())

template<class ValTy>
void popItem(vector<ValTy>* obj, ValTy item) {
	VEC_ERASE;
}

template<class ValTy>
void popItem(shared_ptr<vector<ValTy>> obj, ValTy item) {
	VEC_ERASE;
}

template<class KeyTy, class ValTy>
void popItem(map<KeyTy, ValTy>* obj, KeyTy key) {
	obj->erase(key);
}

template<class KeyTy, class ValTy>
void popItem(shared_ptr<map<KeyTy, ValTy>> obj, KeyTy key) {
	obj->erase(key);
}


class Window;

//Functions that, surprisingly, do nothing.
void doNothing();
void doNothingi(int);
void doNothingTup(py::tuple t);

//This holds all window instances. The Window class automatically adds and removes itself.
extern std::vector<unique_ptr<Window>> windows;

//Function types
typedef function<void(int)> scrollcall, keyhcall; //scroll event callback
typedef function<void()> keycall;				  //key event callback

/*
	This class has a singular goal - contain a 
	quit event. It is only used within the core files.
*/
class QuitEvent {
public:
	/*
		The callback function run directly before
		destroying the window. Defaults to doNothing() (below).
	*/
	keycall callback;

	/*
		Pointer to the window to destroy. I couldn't figure out 
		how to just reference Window::destroy().
	*/
	Window* window;

	//Construct the quit event.
	QuitEvent(Window* win, keycall call = doNothing);

	//Get a pointer to this object.
	QuitEvent* instance();

	//Destroy the window.
	void operator()();
	//This is here because it can't be accessed for some reason in WindowEventHandler::addQE().
	void operator=(const QuitEvent& other);
};

//Types for event handling
typedef map<MouseEvents, mousecall> mouse;	  //mouse events
typedef map<int, mouse> umouse;				  //mouse events for utilities
typedef map<int, scrollcall> Uscroll;		  //scroll events for utilities
typedef map<int, keycall> key;				  //key events
typedef map<int, key> ukey;					  //key events for utilities
typedef map<int, QuitEvent> Quit;			  //quit events
typedef vector<KeyCombination> kcombos;		  //key combinations
typedef vector<MouseKeyCombination> mkcombos; //mouse key combinations

//A class that manages the adding and removing of events for a specific window.
class WindowEventHandler {
public:
	Window* win;

	//Has a key handler been added?
	bool keyhandler = false;

	/*
		Why the shared_ptrs? Well, on the old, old computer I developed 
		this module on, VS was giving me so many errors related to the 
		std::maps and std::vectors until I used std::shared_ptrs. 

		¯\_(ツ)_/¯
	*/

	//Normal events
	shared_ptr<mouse> mousedown, mousedrag, mousethumb;     //mousedown, drag, and thumb events
	mousecall mousemove;                                    //the mousemove event
	func mouseup;                                           //the mouseup event
	scrollcall scroll;                                      //the scroll event
	shared_ptr<key> keydown, keyhold;                       //keydown and keyhold events
	keyhcall keyhandle;                                     //the keyhandle function - if there is one.
	shared_ptr<Quit> quit;                                  //quit events for the window
	shared_ptr<kcombos> keycombos;							//key combinations
	shared_ptr<mkcombos> mousekeycombos;					//mouse key combinations

	//Utility events
	shared_ptr<umouse> umousedown, umousedrag, umousethumb; //utility mousedown, drag, and thumb events
	shared_ptr<Uscroll> uscroll;                            //utility scroll events
	shared_ptr<ukey> ukeydown, ukeyhold;                    //utility keydown and keyhold events

	/*
		Constructs the instance. Really only initialises all the shared_ptrs 
		and the Window pointer.
	*/
	WindowEventHandler(Window* _win);

	//Below are the functions to add and remove events.

	/*
		Add a mouse event.

		\param MouseEvents type: the type of event.
		\param mousecall callback: the callback function.

		\returns void
	*/
	void addME(MouseEvents type, mousecall callback);

	/*
		Add a mouseup event.

		\param MouseEvents type: the type of event. Useless, really,
								 but it's there so that in Python you
								 can call self.events.add_mouse_event(
									MouseEvents.MOUSE_UP, 
									<function object>
								)
		\param func callback: the callback function.

		\returns void
	*/
	void addMU(MouseEvents type, func callback);

	/*
		Add a mouseup event.

		\param func callback: the callback function.

		\returns void
	*/
	void addMU(func callback);

	/*
		Add a utility mouse event.

		\param MouseEvents type: the type of event.
		\param mousecall callback: the callback function.
		\param int uid: the id of the utility.

		\returns void
	*/
	void addME(MouseEvents type, mousecall callback, int uid);

	/*
		Add a scroll event.

		\param scrollcall callback: the callback function.

		\returns void
	*/
	void addSE(scrollcall callback);

	/*
		Add a utility scroll event.

		\param scrollcall callback: the callback function.
		\param int uid: the id of the utility.

		\returns void
	*/
	void addSE(scrollcall callback, int uid);

	/*
		Add a key event.

		\param KeyEvents type: the type of event.
		\param keycall callback: the callback function.
		\param int _key: the static_cast<int>(SDL_Scancode::SCANCODE).
		                 A pybind11::dict containing these scancodes 
						 can be found in KeyCodes.h.

		\returns void
	*/
	void addKE(KeyEvents type, keycall callback, int _key);

	/*
		Add a utility key event.

		\param KeyEvents type: the type of event.
		\param keycall callback: the callback function.
		\param int _key: the static_cast<int>(SDL_Scancode::SCANCODE).
		                 A pybind11::dict containing these scancodes 
						 can be found in KeyCodes.h.
		\param int uid: the id of the utility.

		\returns void
	*/
	void addKE(KeyEvents type, keycall, int _key, int uid);

	/*
		Add a key event handler.

		\param keyhcall callback: the callback function.

		\returns void
	*/
	void addKEH(keyhcall handle);

	/*
		Add a quit event.

		\param int _key: the static_cast<int>(SDL_Scancode::SCANCODE).
						 A pybind11::dict containing these scancodes 
						 can be found in KeyCodes.h.
		\param keycall callback: the callback function. Defaults to 
		                         doNothing() which, surprisingly, does nothing.

		\returns void
	*/
	void addQE(int _key, keycall callback = doNothing);

	/*
		Add a key combination event.

		\param KeyCombination combo: the KeyCombination instance.

		\returns void
	*/
	void addKC(KeyCombination combo);

	/*
		Add a mouse-key combination event.

		\param MouseKeyCombination combo: the MouseKeyCombination instance.

		\returns void
	*/
	void addMKC(MouseKeyCombination combo);



	/*
		Remove a mouse event.

		\param Events type: the type of event.

		\returns void
	*/
	void popME(MouseEvents type);

	/*
		Remove a utility mouse event.

		\param MouseEvents type: the type of event.
		\param int uid: the id of the utility.

		\returns void
	*/
	void popUME(MouseEvents type, int uid);

	/*
		Remove the mouseup event.

		\returns void
	*/
	void popMU();

	/*
		Remove a scroll event.

		\returns void
	*/
	void popSE();

	/*
		Remove a utility scroll event.

		\param int uid: the id of the utility.

		\returns void
	*/
	void popSE(int uid);

	/*
		Remove a key event.

		\param KeyEvents type: the type of event.
		\param int _key: the static_cast<int>(SDL_Scancode::SCANCODE).
		                 A pybind11::dict containing these scancodes
						 can be found in KeyCodes.h.

		\returns void
	*/
	void popKE(KeyEvents type, int _key);

	/*
		Remove a utility key event.

		\param KeyEvents type: the type of event.
		\param int _key: the static_cast<int>(SDL_Scancode::SCANCODE).
		                 A pybind11::dict containing these scancodes
						 can be found in KeyCodes.h.
		\param int uid: the id of the utility.

		\returns void
	*/
	void popKE(KeyEvents type, int _key, int uid);

	/*
		Remove a key event handler.

		\returns void
	*/
	void popKEH();

	/*
		Remove a key event.

		\param int _key: the static_cast<int>(SDL_Scancode::SCANCODE).
		                 A pybind11::dict containing these scancodes
						 can be found in KeyCodes.h.

		\returns void
	*/
	void popQE(int _key);

	/*
		Remove a key combination event.

		\param KeyCombination combo: the KeyCombination instance.

		\returns void
	*/
	void popKC(KeyCombination combo);

	/*
		Remove a mouse-key combination event.

		\param MouseKeyCombination combo: the MouseKeyCombination instance.

		\returns void
	*/
	void popMKC(MouseKeyCombination combo);
};

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

	//Simple attributes defining the window's properties.
	string name;
	int width = 0, height = 0;
	Uint8 attr = 0;
	int bgR = 0, bgG = 0, bgB = 0, bgA = 255;

	//Construct the window. This is the same every time.
	void construct();
	//Construct the window for the first time.
	void construct(int width_, int height_, string name_);

	void destroySDLWin();
public:
	//The SDL_Window's ID
	SDL_WindowID id = 0;

	bool destroyed = false;

	/*
		Construct the Window immediately.

		\param const char* name: the name of the window.

		\param int _width: the width of the window, in pixels.

		\param int _height: the height of the window, in pixels.
	*/
	Window(string name_, int width_, int height_);
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
		Set the background color of the window.

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
		Get the size of the window, C++ version.

		\param int* width: a pointer to the width variable.

		\param int* height: a pointer to the height variable.

		\returns void
	*/
	void getSize(int* width, int* height);

	/*
		Get the size of the window, Python version.

		\returns pybind11::tuple
	*/
	py::tuple getSize();

	//Drawing functions

	/*
		Set the current drawing color.

		\param int r
	*/
	void setColor(int r, int g, int b, int a = 255);
	void point(int x, int y);
	void line(int x1, int y1, int x2, int y2);
	void fillRect(int x, int y, int width, int height);
	void strokeRect(int x, int y, int width, int height);

	//Clear the current frame
	void clear();
	void show();

	WindowEventHandler* getHandle();
};

class DialogWindow : public Window {
private:
	Window* parent;
public:
	DialogWindow(string name_, int width_, int height_, Window* parent);
};


typedef pair<Window*, WindowEventHandler*> winEventPair;
/*
	Creates a Window by creating a unique pointer
	to the instantiation and moving it to the windows
	vector.

	\param const char* name: the name of the window.

	\param int width: the width of the window.

	\param int height: the height of the window.
*/
winEventPair createWindow(
	string name = "gamesR2simple window", 
	int width = 200, 
	int height = 100
);

void quit();


class Events {
private:
	map<Uint8, bool> pressedBtns;
	keyMap* keys;
	map<int, bool> heldKeys;

	static Events* self;

	static void checkMD(WindowEventHandler* handler, int x, int y, Uint8 btn);
	static void checkMM(WindowEventHandler* handler, int x, int y);
	static void checkMDrag(WindowEventHandler* handler, int x, int y);
	static void checkSE(WindowEventHandler* handler, int dir);
	static void checkKD(WindowEventHandler* handler, SDL_Scancode keycode);
	static void checkKH(WindowEventHandler* handler, bool u = false);
public:
	Events(keyMap* _keys);

	static void checkEvents();
};

extern std::vector<func> updateFuncs;

void addUpdateFunc(func f);

void updateAll();

END