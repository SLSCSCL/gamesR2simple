//#define CPP_TESTING

#ifndef CPP_TESTING
#define USING_PYBIND11
#endif

#include "gamesR2simple.h"
using namespace gr2s;
namespace py = pybind11;


#ifdef CPP_TESTING
#include <iostream>
#include <sstream>
#include <SDL3/SDL_main.h>

string getCoord(int x, int y) {
    stringstream ss{};
    ss << "(" << x << ", " << y << ")";
    return ss.str();
}

void mousedown(int x, int y) {
    cout << "Mousedown at " << getCoord(x, y) << "\n";
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

void deleteBlock(int x, int y) {
    cout << "Block deleted at " << getCoord(x, y) << "!\n";
}

void mouseup() {
    cout << "Mouse up!\n";
}

void ldrag(int x, int y) {
    cout << "Mouse is being l-dragged! Now at " << getCoord(x, y) << "!\n";
}

void rdrag(int x, int y) {
    cout << "Mouse is being r-dragged! Now at " << getCoord(x, y) << "!\n";
}

void whldrag(int x, int y) {
    cout << "Mouse is being whl-dragged! Now at " << getCoord(x, y) << "!\n";
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

    events->addME(MouseEvents::MOUSE_UP, mouseup); //Works!
    events->popME(MouseEvents::MOUSE_UP);        //Works!

    events->addME(MouseEvents::L_DRAG, ldrag);     //Works!
    events->addME(MouseEvents::R_DRAG, rdrag);     //Works!
    events->addME(MouseEvents::WHL_DRAG, whldrag); //Works!

    events->popME(MouseEvents::L_DRAG);   //Works!
    events->popME(MouseEvents::R_DRAG);   //Works!
    events->popME(MouseEvents::WHL_DRAG); //Works!

    events->addSE(scroll); //Works!
    events->popSE();       //Works!

    events->addKEH(KeyEvents::KEY_DOWN, keyhandler); //Works!
    //events->popKEH(KeyEvents::KEY_DOWN);             //Works!
    
    win->setMaximized(false);

	addUpdateFunc(win, update);

	run();
    return 0;
}

#else

#include <pybind11/functional.h>
#include <pybind11/native_enum.h>
#include <pybind11/stl.h>

#include "documentation.h"

inline void translateErr(obj type, const string& msg) {
    obj err = type(msg);
    err.attr("__cause__") = py::none();
    PyErr_SetObject(type.ptr(), err.ptr());
}

PYBIND11_MODULE(_cpp, m) {
    m.attr("keys") = getKeys();
    m.def("start", start);
    m.def("run", run);

    m.def("quit", quit);
    
    m.def("create_window", createWindow);
    m.def("add_update_func", addUpdateFunc).doc();
    m.def("use_audio", useAudio);

    py::native_enum<UpdateOrder>(m, "UpdateOrder", "enum.Enum")
        .value("UPDATE_FIRST", UpdateOrder::UPDATE_FIRST)
        .value("EVENTS_FIRST", UpdateOrder::EVENTS_FIRST)
        .export_values()
        .finalize();

    m.def("set_update_order", setUpdateOrder, py::arg("update_order"));

    Errs::Quit = py::register_exception<ProgramExit>(
        m, "ProgramExit"
    );
    Errs::WinOpen = py::register_exception<WindowOpeningError>(
        m, "WindowOpeningError", 
        PyExc_RuntimeError
    );
    Errs::Arg = py::register_exception<ArgumentMismatchError>(
        m, "ArgumentMismatchError", 
        PyExc_TypeError
    );
    Errs::KHandle = py::register_exception<KeyHandlerExistsError>(
        m, "KeyHandlerExistsError", 
        PyExc_RuntimeError
    );

    py::register_exception_translator(
        [](std::exception_ptr ptr) {
            windows.clear();
            SDL_Quit();
            try {
                if (ptr) std::rethrow_exception(ptr);
            }
            catch (ProgramExit&) {}
            catch (TypeError& e) {
                translateErr(Errs::Type, e.what());
            }
            catch (ArgumentMismatchError& e) {
                translateErr(Errs::Arg, e.what());
            }
            catch (KeyHandlerExistsError& e) {
                translateErr(Errs::KHandle, e.what());
            }
            catch (WindowOpeningError& e) {
                translateErr(Errs::WinOpen, e.what());
            }
            catch (exception& e) {
                translateErr(Errs::Runtime, e.what());
            }
        }
    );
    
    py::class_<Window>(m, "Window", "docstring")
        .def(py::init<string, int, int>())
        .def("destroy", &Window::destroy)
        //setter funcs
        .def("set_resizable", &Window::setResizable, py::arg("set") = true)
        .def("set_minimized", &Window::setMinimized, py::arg("set") = true)
        .def("set_maximized", &Window::setMaximized, py::arg("set") = true)
        //size funcs
        .def("resize", &Window::resize, py::arg("new_width"), py::arg("new_height"))
        .def("get_size", [](Window& win) {
            int w, h;
            win.getSize(&w, &h);
            return make_pair(w, h);
        })
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
        .def("point", &Window::point, py::arg("x"), py::arg("y"))
        .def(
            "draw_line", &Window::line
            , py::arg("x1"), py::arg("y1")
            , py::arg("x2"), py::arg("y2")
        )
        .def(
            "fill_rect", &Window::fillRect, 
            py::arg("x"), py::arg("y"), 
            py::arg("width"), py::arg("height")
        )
        .def(
            "stroke_rect", &Window::strokeRect,
            py::arg("x"), py::arg("y"),
            py::arg("width"), py::arg("height")
        )
        .def("save", &Window::save)
        .def("clear", &Window::clear)
        .def_readonly("id", &Window::id);

    py::class_<KeyCombination>(m, "KeyCombination")
        .def(
            py::init<int, int, func>(), 
            py::arg("key1"), 
            py::arg("key2"), 
            py::arg("callback")
        )
        .def(
            py::init<int, int, int, func>(), 
            py::arg("key1"), 
            py::arg("key2"), 
            py::arg("key3"), 
            py::arg("callback")
        );

    py::class_<MouseKeyCombination>(m, "MouseKeyCombination")
        .def(py::init<int, mousecall>(), py::arg("key"), py::arg("callback"));

    py::native_enum<MouseEvents>(m, "MouseEvents", "enum.Enum", "All possible mouse events.")
        .value("L_CLICK", MouseEvents::L_CLICK)
        .value("LEFT_CLICK", MouseEvents::L_CLICK)
        .value("R_CLICK", MouseEvents::R_CLICK)
        .value("RIGHT_CLICK", MouseEvents::R_CLICK)
        .value("WHL_CLICK", MouseEvents::WHL_CLICK)
        .value("WHEEL_CLICK", MouseEvents::WHL_CLICK)
        .value("L_DRAG", MouseEvents::L_DRAG)
        .value("LEFT_DRAG", MouseEvents::L_DRAG)
        .value("R_DRAG", MouseEvents::R_DRAG)
        .value("RIGHT_DRAG", MouseEvents::R_DRAG)
        .value("WHL_DRAG", MouseEvents::WHL_DRAG)
        .value("WHEEL_DRAG", MouseEvents::WHL_DRAG)
        .value("BACK_THUMB", MouseEvents::BACK_THUMB)
        .value("FWD_THUMB", MouseEvents::FWD_THUMB)
        .value("FORWARD_THUMB", MouseEvents::FWD_THUMB)
        .value("MOUSE_MOVE", MouseEvents::MOUSE_MOVE)
        .value("MOUSE_UP", MouseEvents::MOUSE_UP)
        .export_values()
        .finalize();

    py::native_enum<KeyEvents>(m, "KeyEvents", "enum.Enum", "All possible key events.")
        .value("KEY_DOWN", KeyEvents::KEY_DOWN)
        .value("KEY_HOLD", KeyEvents::KEY_HOLD)
        .export_values()
        .finalize();

    using weh = WindowEventHandler;
    py::class_<weh>(m, "WindowEventHandler")
        //Add events
        .def(
            "add_mouse_event",
            [](weh& handler, MouseEvents type, py::function callback) {
                int argCount = callback.attr("__code__").attr("co_argcount").cast<int>();
                bool hasSelf = false;

                if (!callback.attr("__self__").is_none()) {
                    argCount--;
                    hasSelf = true;
                }

                auto getSelf = [hasSelf]() {
                    return hasSelf ? "self, " : "";
                };
                switch (argCount) {
                case 0:
                    handler.addME(type, [callback]() {
                        callback();
                    });
                    break;
                case 1:
                    handler.addME(type, [callback](int x, int y) {
                        callback(py::make_tuple(x, y));
                    });
                    break;
                case 2:
                    handler.addME(type, [callback](int x, int y) {
                        callback(x, y);
                    });
                    break;
                default:
                    stringstream ss{};
                    ss << "The callback for a mouse event must have parameters "
                       << "of either (" << getSelf() << "x, y) or (" << getSelf() 
                       << "coord). However, the callback has " << argCount + hasSelf
                       << " arguments.";
                    throw ArgumentMismatchError(ss.str().c_str());
                }
            },
            py::arg("event_type"),
            py::arg("callback")
        )
        .def(
            "add_utility_mouse_event",
            [](weh& handler, MouseEvents type, py::function callback, int uid) {
                int argCount = callback.attr("__code__").attr("co_argcount").cast<int>();
                bool hasSelf = false;

                try {
                    if (!callback.attr("__self__").is_none()) {
                        argCount--;
                        hasSelf = true;
                    }
                }
                catch (py::error_already_set&) {}

                auto getSelf = [hasSelf]() {
                    return hasSelf ? "self, " : "";
                    };
                switch (argCount) {
                case 1:
                    handler.addME(type, [callback](int x, int y) {
                        callback(py::make_tuple(x, y));
                    }, uid);
                    break;
                case 2:
                    handler.addME(type, [callback](int x, int y) {
                        callback(x, y);
                    }, uid);
                    break;
                default:
                    stringstream ss{};
                    ss << "The callback for a mouse event must have parameters "
                        << "of either (" << getSelf() << "x, y) or (" << getSelf()
                        << "coord). However, the callback has " << argCount + hasSelf
                        << " arguments.";
                    throw ArgumentMismatchError(ss.str().c_str());
                }
            },
            py::arg("event_type"),
            py::arg("callback"),
            py::arg("utility_id")
        )
        .def(
            "add_scroll_event", 
            py::overload_cast<scrollcall>(&weh::addSE),
            py::arg("callback")
        )
        .def(
            "add_utility_scroll_event", 
            py::overload_cast<scrollcall, int>(&weh::addSE),
            py::arg("callback"),
            py::arg("utility_id")
        )
        .def(
            "add_key_event", 
            py::overload_cast<KeyEvents, keycall, int>(&weh::addKE),
            py::arg("event_type"),
            py::arg("callback"),
            py::arg("key")
        )
        .def(
            "add_utility_key_event", 
            py::overload_cast<KeyEvents, keycall, int, int>(&weh::addKE),
            py::arg("event_type"),
            py::arg("callback"),
            py::arg("key"),
            py::arg("utility_id")
        )
        .def(
            "add_key_event_handler", &weh::addKEH, 
            py::arg("event_type"),
            py::arg("key_event_handler")
        )
        .def(
            "add_quit_event", &weh::addQE, 
            py::arg("key"), 
            py::arg("callback")// = doNothing
        )
        .def(
            "add_key_combination", &weh::addKC, 
            py::arg("combo")
        )
        .def(
            "add_mouse_key_combination", 
            &weh::addMKC,
            py::arg("combo")
        )

        //Pop events
        .def(
            "pop_mouse_event", 
            py::overload_cast<MouseEvents>(&weh::popME),
            py::arg("event_type")
        )
        .def(
            "pop_utility_mouse_event", 
            py::overload_cast<MouseEvents, int>(&weh::popUME),
            py::arg("event_type"),
            py::arg("utility_id")
        )
        .def(
            "pop_scroll_event", 
            py::overload_cast<>(&weh::popSE)
        )
        .def(
            "pop_utility_scroll_event", 
            py::overload_cast<int>(&weh::popSE),
            py::arg("utility_id")
        )
        .def(
            "pop_key_event", 
            py::overload_cast<KeyEvents, int>(&weh::popKE),
            py::arg("event_type"),
            py::arg("key")
        )
        .def(
            "pop_utility_key_event", 
            py::overload_cast<KeyEvents, int, int>(&weh::popKE),
            py::arg("event_type"),
            py::arg("key"),
            py::arg("utility_id")
        )
        .def(
            "pop_key_event_handler", &weh::popKEH,
            py::arg("event_type")
        )
        .def(
            "pop_quit_event", &weh::popQE,
            py::arg("key")
        )
        .def(
            "pop_key_combination", &weh::popKC,
            py::arg("combo")
        )
        .def(
            "pop_mouse_key_combination", &weh::popMKC,
            py::arg("combo")
        );
}

#endif