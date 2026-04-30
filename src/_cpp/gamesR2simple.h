#pragma once
#include <SDL3_ttf/SDL_ttf.h>

#include "core.h"

NAMESPACE

//This is used privately to start up SDL.
extern unsigned int sdlAttr;

//This configures sdlAttr to also use audio.
void useAudio();

//Starts up SDL.
void start();

//Main loop.
void run();

END