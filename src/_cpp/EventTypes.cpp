#include "EventTypes.h"
#include "Window.h"

NAMESPACE

/*
	Functions that do nothing - they are placeholders.
*/

void doNothing() {}
void doNothingi(int a) {}
void doNothingii(int a, int b) {}

/*
	The QuitEvent class. It just holds a QuitEvent.
*/

QuitEvent::QuitEvent(Window* win, keycall call) : window(win), callback(call) {}

QuitEvent* QuitEvent::instance() {
	return this;
}

void QuitEvent::operator()() {
	callback();
	window->destroy();
}

void QuitEvent::operator=(const QuitEvent& other) {
	callback = other.callback;
	window = other.window;
}

END