#include "gamesR2simple.h"
using namespace gr2s;
namespace py = pybind11;

//#define CPP_TESTING

#ifdef CPP_TESTING
#include <iostream>
#include <sstream>
#include <SDL3/SDL_main.h>

string getCoord(py::tuple coord) {
    stringstream ss;
    ss << "(" << coord[0].cast<int>() << ", " << coord[1].cast<int>() << ")";
    return ss.str();
}

void mousedown(py::tuple coord) {
    cout << "Mousedown at " << getCoord(coord) << "\n";
}

void keydownW() {
    cout << "W was pressed!\n";
}

void keyholdW() {
    cout << "W is held!\n";
}

void ctrlC() {
    cout << "Copied!\n";
}

void deleteBlock(py::tuple coord) {
    cout << "Block deleted at " << getCoord(coord) << "!\n";
}

void mouseup() {
    cout << "Mouse up!\n";
}

void ldrag(py::tuple coord) {
    cout << "Mouse is being l-dragged! Now at " << getCoord(coord) << "!\n";
}

void rdrag(py::tuple coord) {
    cout << "Mouse is being r-dragged! Now at " << getCoord(coord) << "!\n";
}

void whldrag(py::tuple coord) {
    cout << "Mouse is being whl-dragged! Now at " << getCoord(coord) << "!\n";
}


void scroll(int dx) {
    cout << "Scrolled " << (dx < 0 ? "down " : "up ") << dx << "!\n";
}

void keyhandler(int key) {
    keyMap keys = getKeys();
    if (key == keys["w"])
        cout << "W\n";
    else if (key == keys["a"])
        cout << "A\n";
    else if (key == keys["s"])
        cout << "S\n";
    else if (key == keys["d"])
        cout << "D\n";
}

Window* win;
void update() {
    int w, h;

    win->getSize(&w, &h);
    win->setColor(0, 0, 0);
    win->clear();
    win->setColor(255, 255, 255);
    win->point(w / 2, h / 2);
    win->show();

    SDL_Delay(10);
}

int main(int, char**) {
    start();
    
	py::scoped_interpreter guard{};

    keyMap keys = getKeys();

    winEventPair data = createWindow(string("Hello"), 800, 400);

    win = data.first;

    WindowEventHandler* events = data.second;

    events->addME(MouseEvents::L_CLICK, mousedown); //Works!
    events->popME(MouseEvents::L_CLICK);            //Works!

    events->addKE(KeyEvents::KEY_DOWN, keydownW, keys["w"]); //Works!
    events->popKE(KeyEvents::KEY_DOWN, keys["w"]);           //Works!

    events->addKE(KeyEvents::KEY_HOLD, keyholdW, keys["w"]); //Works!
    events->popKE(KeyEvents::KEY_HOLD, keys["w"]);           //Works!

    events->addQE(keys["q"]); //Works!
    events->popQE(keys["q"]); //Works!

    KeyCombination keycombo(keys["Left Ctrl"], keys["c"], ctrlC);
    events->addKC(keycombo); //Works!
    events->popKC(keycombo); //Works!

    MouseKeyCombination mousekeycombo(keys["x"], deleteBlock);
    events->addMKC(mousekeycombo); //Works!
    events->popMKC(mousekeycombo); //Works!

    events->addMU(mouseup); //Works!
    events->popMU();        //Works!

    events->addME(MouseEvents::L_DRAG, ldrag);     //Works!
    events->addME(MouseEvents::R_DRAG, rdrag);     //Works!
    events->addME(MouseEvents::WHL_DRAG, whldrag); //Works!

    events->popME(MouseEvents::L_DRAG);   //Works!
    events->popME(MouseEvents::R_DRAG);   //Works!
    events->popME(MouseEvents::WHL_DRAG); //Works!

    events->addSE(scroll); //Works!
    events->popSE();       //Works!

    events->addKEH(keyhandler); //Works!
    events->popKEH();           //Works!
    
    win->setMaximized(false);

	addUpdateFunc(update);

	run();

    quit();
    return 0;
}

#else
#include <pybind11/functional.h>
#include <pybind11/native_enum.h>
#include <pybind11/stl.h>

PYBIND11_MODULE(_cpp, m) {
    m.attr("keys") = getKeys();
    m.def("start", start);
    m.def("run", run);

    m.def("quit", quit);
    m.def("update", updateAll);
    
    m.def("create_window", createWindow);
    m.def("add_update_func", addUpdateFunc);
    m.def("use_audio", useAudio);
    
    py::class_<Window>(m, "Window")
        .def(py::init<string, int, int>())
        .def("destroy", &Window::destroy)
        //setter funcs
        .def("set_resizable", &Window::setResizable)
        .def("set_minimized", &Window::setMinimized)
        .def("set_maximized", &Window::setMaximized)
        //size funcs
        .def("resize", &Window::resize)
        .def("get_size", py::overload_cast<>(&Window::getSize))
        //drawing funcs
        .def(
            "set_color", 
            &Window::setColor,
            "Set the drawing color.",
            py::arg("red"), 
            py::arg("green"),
            py::arg("blue"),
            py::arg("alpha") = 255
        )
        .def("point", &Window::point)
        .def("line", &Window::line)
        .def("fill_rect", &Window::fillRect)
        .def("stroke_rect", &Window::strokeRect)
        .def("clear", &Window::clear)
        .def_readonly("id", &Window::id);

    py::class_<KeyCombination>(m, "KeyCombination")
        .def(py::init<int, int, func>())
        .def(py::init<int, int, int, func>());

    py::class_<MouseKeyCombination>(m, "MouseKeyCombination")
        .def(py::init<int, mousecall>());

    py::native_enum<MouseEvents>(m, "MouseEvents", "enum.Enum")
        .value("L_CLICK", MouseEvents::L_CLICK)
        .value("R_CLICK", MouseEvents::R_CLICK)
        .value("WHL_CLICK", MouseEvents::WHL_CLICK)
        .value("L_DRAG", MouseEvents::L_DRAG)
        .value("R_DRAG", MouseEvents::R_DRAG)
        .value("WHL_DRAG", MouseEvents::WHL_DRAG)
        .value("MOUSE_MOVE", MouseEvents::MOUSE_MOVE)
        .value("MOUSE_UP", MouseEvents::MOUSE_UP)
        .export_values()
        .finalize();

    py::native_enum<KeyEvents>(m, "KeyEvents", "enum.Enum")
        .value("KEY_DOWN", KeyEvents::KEY_DOWN)
        .value("KEY_HOLD", KeyEvents::KEY_HOLD)
        .export_values()
        .finalize();

    using weh = WindowEventHandler;
    py::class_<weh>(m, "WindowEventHandler")
        //Add events
        .def("add_mouse_event", py::overload_cast<MouseEvents, mousecall>(&weh::addME))
        .def("add_mouse_event", py::overload_cast<MouseEvents, gr2s::func>(&weh::addMU))
        .def("add_mouseup_event", py::overload_cast<gr2s::func>(&weh::addMU))
        .def("add_utility_mouse_event", py::overload_cast<MouseEvents, mousecall, int>(&weh::addME))
        .def("add_scroll_event", py::overload_cast<scrollcall>(&weh::addSE))
        .def("add_utility_scroll_event", py::overload_cast<scrollcall, int>(&weh::addSE))
        .def("add_key_event", py::overload_cast<KeyEvents, keycall, int>(&weh::addKE))
        .def("add_utility_key_event", py::overload_cast<KeyEvents, keycall, int, int>(&weh::addKE))
        .def("add_key_event_handler", &weh::addKEH)
        .def("add_quit_event", &weh::addQE)
        .def("add_key_combination", &weh::addKC)
        .def("add_key_mouse_combination", &weh::addMKC)

        //Pop events
        .def("pop_mouse_event", py::overload_cast<MouseEvents>(&weh::popME))
        .def("pop_utility_mouse_event", py::overload_cast<MouseEvents, int>(&weh::popUME))
        .def("pop_scroll_event", py::overload_cast<>(&weh::popSE))
        .def("pop_utility_scroll_event", py::overload_cast<int>(&weh::popSE))
        .def("pop_key_event", py::overload_cast<KeyEvents, int>(&weh::popKE))
        .def("pop_utility_key_event", py::overload_cast<KeyEvents, int, int>(&weh::popKE))
        .def("pop_key_event_handler", &weh::popKEH)
        .def("pop_quit_event", &weh::popQE)
        .def("pop_key_combination", &weh::popKC)
        .def("pop_mouse_key_combination", &weh::popMKC);
}

#endif