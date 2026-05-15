#pragma once
#ifndef WIN_EVENT_HANDLER
#define WIN_EVENT_HANDLER
#include <memory>
#include <map>
#include <vector>

#include "Combinations.h"
#include "Errors.h"
#include "macro.h"
#include "EventTypes.h"

NAMESPACE

/*
	Below, we have each overload of popItem().
	The popItem() function can erase an item from
	a std::vector or std::map.
*/

template<class ValTy>
void popItem(std::vector<ValTy>* obj, ValTy item) {
	obj->erase(remove(obj->begin(), obj->end(), item), obj->end());
}

template<class KeyTy, class ValTy>
void popItem(std::map<KeyTy, ValTy>* obj, KeyTy key) {
	obj->erase(key);
}

class Window;

//A class that manages the adding and removing of events for a specific window.
class WindowEventHandler {
private:
	/*template<class EventsType>
	void addMEHelp(MouseEvents type, mousecall callback, int uid = -1) {
		unique_ptr<EventsType> events;

		switch (type) {
		case MouseEvents::L_CLICK:
		case MouseEvents::R_CLICK:
		case MouseEvents::WHL_CLICK:
			//Error when EventsType is umouse
			if (is_same_v<EventsType, mouse>) events = mousedown;
			//Error when EventsType is mouse
			else events = umousedown;
			break;
		case MouseEvents::L_DRAG:
		case MouseEvents::R_DRAG:
		case MouseEvents::WHL_DRAG:
			//Error when EventsType is umouse
			if (uid == -1) events = mousedrag;
			//Error when EventsType is mouse
			else events = umousedrag;
			break;
		case MouseEvents::BACK_THUMB:
		case MouseEvents::FWD_THUMB:
			//Error when EventsType is umouse
			if (uid == -1) events = mousethumb;
			//Error when EventsType is mouse
			else events = umousethumb;
			break;
		case MouseEvents::MOUSE_MOVE:
			if (uid == -1) mousemove = callback;
			else (*umousemove)[uid] = callback;
			return;
		case MouseEvents::MOUSE_UP:
			if (uid == -1) mouseup = callback;
			else (*umouseup)[uid] = callback;
			return;
		default:
			raise<TypeError>("The 'type' parameter must be of type gamesR2simple.MouseEvents!");
		}

		//If uid is provided, it means that we are adding a
		//utility mouse event. Thus, we provide the uid to the
		//map. This way we can get the element from type in both
		//cases.
		((uid != -1) ? (*events)[uid] : (*events))[type] = callback;
	}*/
public:
	Window* win;

	/*
		Why the unique_ptrs? Well, on the old, old computer I developed
		this module on, VS was giving me so many errors related to the
		std::maps and std::vectors until I used std::unique_ptrs.

		¯\_(ツ)_/¯
	*/

	//Normal events
	std::unique_ptr<mouse> mousedown, mousedrag, mousethumb;     //mousedown, drag, and thumb events
	mousecall mousemove;                                         //the mousemove event
	mousecall mouseup;                                           //the mouseup event
	scrollcall scroll;                                           //the scroll event
	std::unique_ptr<key> keydown, keyhold;                       //keydown and keyhold events
	//the keyhandling function for keydown events - if there is one.
	keyhcall keydownhandler;
	keyhcall keyholdhandler;
	std::unique_ptr<Quit> quit;                                  //quit events for the window
	std::unique_ptr<kcombos> keycombos;							 //key combinations
	std::unique_ptr<mkcombos> mousekeycombos;					 //mouse key combinations

	//Utility events
	std::unique_ptr<umouse> umousedown, umousedrag, umousethumb; //utility mousedown, drag, and thumb events
	std::unique_ptr<umousecall> umousemove;                      //utility mousemove events
	std::unique_ptr<umousecall> umouseup;                        //utility mouseup events
	std::unique_ptr<Uscroll> uscroll;                            //utility scroll events
	std::unique_ptr<ukey> ukeydown, ukeyhold;                    //utility keydown and keyhold events

	/*
		Constructs the instance. Really only initialises all the unique_ptrs
		and the Window pointer.
	*/
	WindowEventHandler(Window* _win);

	//Clear the std::vectors and std::maps - they contain lambdas that capture pybind11::functions
	~WindowEventHandler();

	/*
		=================================================
		Below are the functions to add and remove events.
		=================================================
	*/

	/*
		Add a mouse event.

		\param MouseEvents type: the type of event.
		\param mousecall callback: the callback function.

		\returns void
	*/
	void addME(MouseEvents type, mousecall callback);

	/*
		Add a mouse event.

		\param MouseEvents type: the type of event.
		\param func callback: the callback function.

		\returns void
	*/
	void addME(MouseEvents type, func callback);

	/*
		Add a utility mouse event.

		\param MouseEvents type: the type of event.
		\param mousecall callback: the callback function.
		\param int uid: the id of the utility.

		\returns void
	*/
	void addME(MouseEvents type, mousecall callback, int uid);

	/*
		Add a utility mouse event.

		\param MouseEvents type: the type of event.
		\param func callback: the callback function.
		\param int uid: the id of the utility.

		\returns void
	*/
	void addME(MouseEvents type, func callback, int uid);

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
						 A std::map containing these scancodes
						 can be found in KeyCodes.h.

		\returns void
	*/
	void addKE(KeyEvents type, keycall callback, int _key);

	/*
		Add a utility key event.

		\param KeyEvents type: the type of event.
		\param keycall callback: the callback function.
		\param int _key: the static_cast<int>(SDL_Scancode::SCANCODE).
						 A std::map containing these scancodes
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
	void addKEH(KeyEvents type, keyhcall handle);

	/*
		Add a quit event.

		\param int _key: the static_cast<int>(SDL_Scancode::SCANCODE).
						 A std::map containing these scancodes
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
						 A std::map containing these scancodes
						 can be found in KeyCodes.h.

		\returns void
	*/
	void popKE(KeyEvents type, int _key);

	/*
		Remove a utility key event.

		\param KeyEvents type: the type of event.
		\param int _key: the static_cast<int>(SDL_Scancode::SCANCODE).
						 A std::map containing these scancodes
						 can be found in KeyCodes.h.
		\param int uid: the id of the utility.

		\returns void
	*/
	void popKE(KeyEvents type, int _key, int uid);

	/*
		Remove a key event handler.

		\returns void
	*/
	void popKEH(KeyEvents type);

	/*
		Remove a key event.

		\param int _key: the static_cast<int>(SDL_Scancode::SCANCODE).
						 A std::map containing these scancodes
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

END
#endif