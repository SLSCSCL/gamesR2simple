#include "WindowEventHandler.h"

NAMESPACE

/*
	The WindowEventHandler. Like the name implies, it handles the events for a specific Window.
*/

WindowEventHandler::WindowEventHandler(Window* _win) :
	win(_win),
	mousedown(std::make_unique<mouse>()),
	umousedown(std::make_unique<umouse>()),

	mousedrag(std::make_unique<mouse>()),
	umousedrag(std::make_unique<umouse>()),

	uscroll(std::make_unique<Uscroll>()),

	keydown(std::make_unique<key>()),
	keyhold(std::make_unique<key>()),

	ukeydown(std::make_unique<ukey>()),
	ukeyhold(std::make_unique<ukey>()),

	quit(std::make_unique<Quit>()),

	keycombos(std::make_unique<kcombos>()),
	mousekeycombos(std::make_unique<mkcombos>()),

	umousemove(std::make_unique<umousecall>()),
	umouseup(std::make_unique<umousecall>())
{
	scroll = doNothingi;
	mouseup = doNothingii;
	mousemove = doNothingii;
	keydownhandler = doNothingi;
	keyholdhandler = doNothingi;
}

WindowEventHandler::~WindowEventHandler() {
	//Clear all std::vectors and std::maps.
	mousedown->clear();
	umousedown->clear();

	mousedrag->clear();
	umousedrag->clear();

	uscroll->clear();

	keydown->clear();
	keyhold->clear();

	ukeydown->clear();
	ukeyhold->clear();

	quit->clear();

	keycombos->clear();
	mousekeycombos->clear();

	umousemove->clear();
	umouseup->clear();
}

void WindowEventHandler::addME(MouseEvents type, mousecall callback) {
	//addMEHelp<mouse>(type, callback);
	switch (type) {
	case MouseEvents::L_CLICK:
	case MouseEvents::R_CLICK:
	case MouseEvents::WHL_CLICK:
		(*mousedown)[type] = callback;
		break;
	case MouseEvents::L_DRAG:
	case MouseEvents::R_DRAG:
	case MouseEvents::WHL_DRAG:
		(*mousedrag)[type] = callback;
		break;
	case MouseEvents::MOUSE_MOVE:
		mousemove = callback;
		break;
	case MouseEvents::MOUSE_UP:
		mouseup = callback;
		break;
	case MouseEvents::BACK_THUMB:
	case MouseEvents::FWD_THUMB:
		break;
	default:
		raise<TypeError>("The 'type' parameter must be of type gamesR2simple.MouseEvents!");
	}
}

void WindowEventHandler::addME(MouseEvents type, func callback) {
	if (type != MouseEvents::MOUSE_UP)
		raise<ArgumentMismatchError>(
			"If a mouse event callback doesn't take parameters, it must be a mouseup event!"
		);
	mouseup = [callback](int x, int y) {
		callback();
		};
}

void WindowEventHandler::addME(MouseEvents type, mousecall callback, int uid) {
	//addMEHelp<umouse>(type, callback, uid);
	umouse* events;
	switch (type) {
	case MouseEvents::L_CLICK:
	case MouseEvents::R_CLICK:
	case MouseEvents::WHL_CLICK:
		events = umousedown.get();
		break;
	case MouseEvents::L_DRAG:
	case MouseEvents::R_DRAG:
	case MouseEvents::WHL_DRAG:
		events = umousedrag.get();
		break;
	case MouseEvents::BACK_THUMB:
	case MouseEvents::FWD_THUMB:
		events = umousethumb.get();
		break;
	default:
		raise<TypeError>("The 'type' parameter must be of type gamesR2simple.MouseEvents!");
	}
	(*events)[uid][type] = callback;
}

void WindowEventHandler::addME(MouseEvents type, func callback, int uid) {
	if (type != MouseEvents::MOUSE_UP)
		raise<ArgumentMismatchError>(
			"If a mouse event callback doesn't take parameters, it must be a mouseup event!"
		);
	(*umouseup)[uid] = [callback](int x, int y) {
		callback();
		};
}

void WindowEventHandler::addSE(scrollcall callback) {
	scroll = callback;
}

void WindowEventHandler::addSE(scrollcall callback, int uid) {
	(*uscroll)[uid] = callback;
}

void WindowEventHandler::addKE(KeyEvents type, keycall callback, int _key) {
	key* events;
	switch (type) {
	case KeyEvents::KEY_DOWN:
		events = keydown.get();
		break;
	case KeyEvents::KEY_HOLD:
		events = keyhold.get();
		break;
	default:
		raise<TypeError>("The 'type' parameter must be of type gamesR2simple.KeyEvents!");
	}
	(*events)[_key] = callback;
}

void WindowEventHandler::addKE(KeyEvents type, keycall callback, int _key, int uid) {
	ukey* events;
	switch (type) {
	case KeyEvents::KEY_DOWN:
		events = ukeydown.get();
		break;
	case KeyEvents::KEY_HOLD:
		events = ukeyhold.get();
		break;
	default:
		raise<TypeError>("The 'type' parameter must be of type gamesR2simple.KeyEvents!");
	}
	(*events)[uid][_key] = callback;
}

void WindowEventHandler::addKEH(KeyEvents type, keyhcall handle) {
	switch (type) {
	case KeyEvents::KEY_DOWN:
		keydownhandler = handle;
		break;
	case KeyEvents::KEY_HOLD:
		keyholdhandler = handle;
	}
}

void WindowEventHandler::addQE(int _key, keycall callback) {
	if (keydown->find(_key) == keydown->end()) {
		quit->insert_or_assign(_key, QuitEvent(win, callback));
	}
}

void WindowEventHandler::addKC(KeyCombination combo) {
	keycombos->push_back(combo);
}

void WindowEventHandler::addMKC(MouseKeyCombination combo) {
	mousekeycombos->push_back(combo);
}

void WindowEventHandler::popME(MouseEvents type) {
	switch (type) {
	case MouseEvents::L_CLICK:
	case MouseEvents::R_CLICK:
	case MouseEvents::WHL_CLICK:
		popItem(mousedown.get(), type);
		break;
	case MouseEvents::L_DRAG:
	case MouseEvents::R_DRAG:
	case MouseEvents::WHL_DRAG:
		popItem(mousedrag.get(), type);
		break;
	case MouseEvents::BACK_THUMB:
	case MouseEvents::FWD_THUMB:
		popItem(mousethumb.get(), type);
		break;
	case MouseEvents::MOUSE_UP:
		mouseup = doNothingii;
		break;
	default:
		raise<TypeError>("The 'type' parameter must be of type gamesR2simple.MouseEvents!");
	}
}

void WindowEventHandler::popUME(MouseEvents type, int uid) {
	switch (type) {
	case MouseEvents::L_CLICK:
	case MouseEvents::R_CLICK:
	case MouseEvents::WHL_CLICK:
		popItem(&(*umousedown)[uid], type);
		break;
	case MouseEvents::L_DRAG:
	case MouseEvents::R_DRAG:
	case MouseEvents::WHL_DRAG:
		popItem(&(*umousedrag)[uid], type);
		break;
	case MouseEvents::BACK_THUMB:
	case MouseEvents::FWD_THUMB:
		popItem(&(*umousethumb)[uid], type);
		break;
	}
}

void WindowEventHandler::popSE() {
	scroll = doNothingi;
}

void WindowEventHandler::popSE(int uid) {
	(*uscroll)[uid] = doNothingi;
}

void WindowEventHandler::popKE(KeyEvents type, int _key) {
	switch (type) {
	case KeyEvents::KEY_DOWN:
		popItem(keydown.get(), _key);
		break;
	case KeyEvents::KEY_HOLD:
		popItem(keyhold.get(), _key);
		break;
	}
}

void WindowEventHandler::popKE(KeyEvents type, int _key, int uid) {
	switch (type) {
	case KeyEvents::KEY_DOWN:
		popItem(&(*ukeydown)[uid], _key);
		break;
	case KeyEvents::KEY_HOLD:
		popItem(&(*ukeyhold)[uid], _key);
		break;
	}
}

void WindowEventHandler::popKEH(KeyEvents type) {
	addKEH(type, doNothingi);
}

void WindowEventHandler::popQE(int _key) {
	popItem(quit.get(), _key);
}

void WindowEventHandler::popKC(KeyCombination combo) {
	popItem(keycombos.get(), combo);
}

void WindowEventHandler::popMKC(MouseKeyCombination combo) {
	popItem(mousekeycombos.get(), combo);
}

END