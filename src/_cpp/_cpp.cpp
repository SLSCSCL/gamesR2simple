#include <pybind11/embed.h>
#include <pybind11/native_enum.h>
#include <pybind11/pybind11.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

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
    if (!SDL_Init(sdlAttr)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }
    
	py::scoped_interpreter guard{};

    Window win("Hello", 800, 400);

    // Clear to black and draw a single white point at center
    int w, h;
    win.setMaximized(true);

    // Sit in a tiny loop until window close
    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }
        SDL_Delay(10);

        win.getSize(&w, &h);
        win.setColor(0, 0, 0);
        win.clear();
        win.setColor(255, 255, 255);
        win.point(w / 2, h / 2);
        win.show();
    }

    quit();
    return 0;
}

PYBIND11_MODULE(_cpp, m) {
    m.add_object("keys", getKeys());

    py::class_<Window>(m, "Window")
        .def(py::init<pybind11::str, int, int>())
        .def("destroy", &Window::destroy)
        //setter funcs
        .def("setResizable", &Window::setResizable)
        .def("setMinimized", &Window::setMinimized)
        .def("setMaximized", &Window::setMaximized)
        //size funcs
        .def("resize", &Window::resize)
        .def("getSize", py::overload_cast<>(&Window::getSize))
        //drawing funcs
        .def("setColor", &Window::setColor)
        .def("point", &Window::point)
        .def("line", &Window::line)
        .def("fillRect", &Window::fillRect)
        .def("strokeRect", &Window::strokeRect)
        .def("clear", &Window::clear)
        .def("show", &Window::show)
        .def_readwrite("id", &Window::id);
    m.def("quit", quit);
    m.def("update", update);

    py::module mod = m.def_submodule("combos");

    py::class_<Combination>(mod, "KeyCombination")
        .def(py::init<Key, Key, py::function>())
        .def(py::init<Key, Key, Key, py::function>());

    py::class_<Combination>(mod, "MouseKeyCombination")
        .def(py::init<Key, Key, py::function>())
        .def(py::init<Key, Key, Key, py::function>());

    mod = m.def_submodule("events");

    py::class_<Events>(mod, "Events")
        .def(py::init<>())
        .def("check_events", &Events::checkEvents);

    py::native_enum<MouseEvents>(mod, "MouseEvents", "enum.Enum")
        .value("L_CLICK", MouseEvents::L_CLICK)
        .value("R_CLICK", MouseEvents::R_CLICK)
        .value("WHL_CLICK", MouseEvents::WHL_CLICK)
        .value("L_DRAG", MouseEvents::L_DRAG)
        .value("R_DRAG", MouseEvents::R_DRAG)
        .value("WHL_DRAG", MouseEvents::WHL_DRAG)
        .value("MOUSEMOVE", MouseEvents::MOUSE_MOVE)
        .value("MOUSEUP", MouseEvents::MOUSE_UP)
        .export_values()
        .finalize();

    py::native_enum<KeyEvents>(mod, "KeyEvents", "enum.Enum")
        .value("KEYDOWN", KeyEvents::KEY_DOWN)
        .value("KEYUP", KeyEvents::KEY_UP)
        .value("KEYHOLD", KeyEvents::KEY_HOLD)
        .export_values()
        .finalize();

    using weh = WindowEventHandler;
    py::class_<weh>(mod, "WinEvents")
        .def("add_mouse_event", &weh::addME);
}