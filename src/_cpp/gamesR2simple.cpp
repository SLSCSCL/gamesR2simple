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
        throw WindowOpeningError(
            string(
                "Could not initialize everything. For nerds, here is the SDL error:\n%s", 
                SDL_GetError()
            ).c_str()
        );
    }
}


void run() {
    keyMap keys = getKeys();
    Events e(&keys);
    while (!windows.empty()) {
        try {
            Events::checkEvents();
            for (auto& win : windows) {
                win->clear();
                inWinUpdate = true;

                if (updateOrder == UpdateOrder::EVENTS_FIRST)
                    win->dumpCache();

				win->update();

                if (updateOrder == UpdateOrder::UPDATE_FIRST)
					win->dumpCache();

                inWinUpdate = false;

                //Show all windows
                win->updateSave();
				win->show();
            }
        }
        catch (const ProgramExit&) {
            break;
        }
        catch (...) {
            throw;
        }
        
        if (windowDestroyed) {
            //Actually destroy the destroyed windows
            windows.erase(
                remove_if(windows.begin(), windows.end(),
                    [](const unique_ptr<Window>& w) {
                        return w->destroyed;
                    }),
                windows.end()
            );
            windowDestroyed = false;
        }
    }
}

END