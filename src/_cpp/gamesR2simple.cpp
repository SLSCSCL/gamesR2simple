#include "gamesR2simple.h"

NAMESPACE

unsigned int sdlAttr = SDL_INIT_VIDEO;

void useAudio() {
    sdlAttr |= SDL_INIT_AUDIO;
}

void start() {
    int count = 0;
    while (!SDL_Init(sdlAttr) && count != 1000)
        count++;
    if (count == 1000) {
        throw WindowOpeningError(string("Could not initialize everything: %s", SDL_GetError()).c_str());
    }
}


void run() {
    keyMap keys = getKeys();
    Events e(&keys);
    while (!windows.empty()) {
        updateAll();
        Events::checkEvents();
        
        //Actually destroy the destroyed windows
        windows.erase(
            remove_if(windows.begin(), windows.end(),
                [](const unique_ptr<Window>& w) {
                    return w->destroyed;
                }),
            windows.end()
        );
    }
    quit();
}

END