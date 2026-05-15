#pragma once
#ifndef EVENT_TYPES
#define EVENT_TYPES
#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "FuncTypes.h"
#include "macro.h"

NAMESPACE

/*
	Below are the enumerations that contain each type of event.
*/

//All possible mouse events are contained in this enum.
enum class MouseEvents {
	NONE = -1, //Only for use in core.cpp
	MOUSE_MOVE,
	MOUSE_UP,
	L_CLICK,
	R_CLICK,
	WHL_CLICK,
	L_DRAG,
	R_DRAG,
	WHL_DRAG,
	BACK_THUMB,
	FWD_THUMB
};
//All key events are contained here.
enum class KeyEvents {
	//Continue from where MouseEvents left off, so that Python can't send a MouseEvents value
	KEY_DOWN = 10,
	KEY_HOLD
};

//Functions that, surprisingly, do nothing.
void doNothing();
void doNothingi(int);
void doNothingii(int, int);

//Types for event handling
typedef std::map<MouseEvents, mousecall> mouse; //mouse events
typedef std::map<int, mouse> umouse;            //mouse events for utilities
typedef std::map<int, mousecall> umousecall;    //mousecall for utilities
typedef std::map<int, scrollcall> Uscroll;      //scroll events for utilities
typedef std::map<int, keycall> key;             //key events
typedef std::map<int, key> ukey;                //key events for utilities

class Window;

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

typedef std::map<int, QuitEvent> Quit; //quit events

class KeyCombination;
class MouseKeyCombination;

typedef std::vector<KeyCombination> kcombos;       //key combinations
typedef std::vector<MouseKeyCombination> mkcombos; //mouse key combinations

END
#endif