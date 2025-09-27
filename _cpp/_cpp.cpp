#include <pybind11/pybind11.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "KeyCodes.h"
#include "common.h"

#include <random>
namespace py = pybind11;
using namespace std;

auto sdlAttr = SDL_INIT_VIDEO;

int randInt(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distr(min, max);

    return distr(gen) % (max - min) + min;
}

void useAudio() {
    sdlAttr |= SDL_INIT_AUDIO;
}

void start() {
    initKeys();
    int count = 0;
    while (!SDL_Init(sdlAttr)) {
        count++;
        if (count == 1000) { //Something must be wrong
            break;
        }
    }
}

int main(int, char**)
{
    /* the real main() that will be used after testing
    
    */
    if (!SDL_Init(sdlAttr)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    Window win{"Hello", 800, 400};

    // Clear to black and draw a single white point at center
    int w, h;
    win.getSize(w, h);
    win.clear();
    win.setColor(255, 255, 255);
    win.point(w / 2, h / 2);
    win.show();

    // Sit in a tiny loop until window close
    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }
        SDL_Delay(10);
    }

    quit();
    return 0;
}

PYBIND11_MODULE(_cpp, m) {
    py::module_ mod = m.def_submodule("window");

    py::class_<Window>(mod, "Window")
        .def(py::init<pybind11::str, int, int>())
        .def("quit", &Window::quit)
        //setter funcs
        .def("setResizable", &Window::setResizable)
        .def("setMinimized", &Window::setMinimized)
        .def("setMaximized", &Window::setMaximized)
        //size funcs
        .def("resize", &Window::resize)
        .def("getSize", &Window::getSize)
        //drawing funcs
        .def("setColor", &Window::setColor)
        .def("point", &Window::point)
        .def("line", &Window::line)
        .def("fillRect", &Window::fillRect)
        .def("strokeRect", &Window::strokeRect)
        .def("clear", &Window::clear)
        .def("show", &Window::show)
        .def_readwrite("id", &Window::id);

    mod = m.def_submodule("keys");

    mod = m.def_submodule("events");
    using weh = WindowEventHandler;
    py::class_<weh>(mod, "WinEvents")
        .def("add_mouse_event", &weh::addME);
}