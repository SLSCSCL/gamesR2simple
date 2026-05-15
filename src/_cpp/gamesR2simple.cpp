#include "gamesR2simple.h"

NAMESPACE

// The quit() function stops the entire program.
[[noreturn]] void quit() {
    windows.clear();
    SDL_Quit();
    TTF_Quit();
    raise<ProgramExit>("");
}

unsigned int sdlAttr = SDL_INIT_VIDEO | SDL_INIT_AUDIO;

void start() {
    if (!SDL_Init(sdlAttr)) {
        raise<SDLInitError>(
            std::string(
                "Could not initialize SDL. For nerds, here is the SDL error:\n%s", 
                SDL_GetError()
            ).c_str()
        );
	}
    if (!TTF_Init()) {
        SDL_Quit();
        raise<SDLInitError>("Could not initialize SDL_ttf.");
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
				win->show();
            }
        }
        catch (const ProgramExit&) {
            break;
        }
        catch (...) {
            windows.clear();
            SDL_Quit();
            TTF_Quit();
            throw;
        }
        
        if (windowDestroyed) {
            //Actually destroy the destroyed windows
            windows.erase(
                remove_if(windows.begin(), windows.end(),
                    [](const std::unique_ptr<Window>& w) {
                        return w->destroyed;
                    }),
                windows.end()
            );
            windowDestroyed = false;
        }
    }

    SDL_Quit();
    TTF_Quit();
}

void addUpdateFunc(Window* win, func f) {
    win->update = f;
}

UpdateOrder updateOrder = UpdateOrder::UPDATE_FIRST;
void setUpdateOrder(UpdateOrder order) {
    switch (order) {
    case UpdateOrder::UPDATE_FIRST:
    case UpdateOrder::EVENTS_FIRST:
        updateOrder = order;
        break;
    default:
        raise<TypeError>(
            "You must pass a value from the UpdateOrder enum to set the update order!"
        );
    }
}

END