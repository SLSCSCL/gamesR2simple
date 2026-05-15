#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_ttf/SDL_textengine.h>

#include "Combinations.h"
#include "Errors.h"
#include "Events.h"
#include "EventTypes.h"
#include "FuncTypes.h"
#include "KeyCodes.h"
#include "macro.h"
#include "Timing.h"
#include "Window.h"
#include "WindowEventHandler.h"

NAMESPACE

[[noreturn]] void quit();

//This is used privately to start up SDL.
extern unsigned int sdlAttr;

//Starts up SDL.
void start();

//Main loop.
void run();

//Add an update function. Of course, you can just set gr2s::Window::update.
void addUpdateFunc(Window* win, func f);

enum class UpdateOrder {
	UPDATE_FIRST = 12, //Continue from where the event enums end - for Python
	EVENTS_FIRST
};

extern UpdateOrder updateOrder;

void setUpdateOrder(UpdateOrder order);

END