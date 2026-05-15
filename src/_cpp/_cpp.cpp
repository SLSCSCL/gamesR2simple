//#define CPP_TESTING

#ifndef CPP_TESTING
#define USING_PYTHON
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <pybind11/pybind11.h>
namespace py = pybind11;
#endif

#include "gamesR2simple.h"
using namespace gr2s;


#ifdef CPP_TESTING
#include <iostream>
#include <sstream>

#include <SDL3/SDL_main.h>

using namespace std;

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
#include <exception>
#include <iostream>
#include <string>
using namespace std;

#include <pybind11/functional.h>
#include <pybind11/native_enum.h>
#include <pybind11/stl.h>

#include "documentation.h"

template<class Err>
inline void registerErr(py::module_ m, obj& err, const char* name, const char* doc, PyObject* parent = PyExc_Exception) {
    err = py::register_exception<Err>(m, name, parent);
    err.doc() = doc;
}

inline void translateErr(obj type, const string& msg) {
    obj err = type(msg);
    err.attr("__cause__") = py::none();
    PyErr_SetObject(type.ptr(), err.ptr());
}

PYBIND11_MODULE(_cpp, m) {
    m.attr("keys") = getKeys();
    m.def("start", start);
    m.def("run_", run);

    m.def("quit_", quit);
    
    m.def("createWindow", createWindow);
    m.def("win_num", []() { return windows.size(); });
    m.def("add_update_func", addUpdateFunc);

    py::native_enum<UpdateOrder>(m, "UpdateOrder", "enum.Enum", "Used to set the update order.")
        .value("UPDATE_FIRST", UpdateOrder::UPDATE_FIRST, "Call update() first, then handle events. This is the default.")
        .value("EVENTS_FIRST", UpdateOrder::EVENTS_FIRST, "Handle the events first, then call update().")
        .export_values()
        .finalize();

    m.def("set_update_order", setUpdateOrder, py::arg("update_order")).doc() = "Set the update order.";

    registerErr<ProgramExit>(m, Errs::Quit, "ProgramExit", "");
    registerErr<SDLInitError>(
        m, Errs::SDLInit, 
        "SDLInitError", 
        "What happens if SDL can't initialize?", 
        PyExc_RuntimeError
    );
    registerErr<ArgumentMismatchError>(
        m, Errs::Arg, 
        "ArgumentMismatchError", 
        "Invalid number of arguments", 
        PyExc_TypeError
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
            catch (SDLInitError& e) {
                translateErr(Errs::SDLInit, e.what());
            }
            catch (exception& e) {
                translateErr(Errs::Runtime, e.what());
            }
        }
    );
    
    py::class_<Window>(
        m, "Window", 
        "The Window class serves as a wrapper for SDL_Window and SDL_Renderer.\n"
        "Of course, I had to make sure it provides a simple interface!"
    )
        .def(py::init<string, int, int>())
        .def("destroy", &Window::destroy, "Destroy the window.")
        .def(
            "set_bg_color",
            &Window::setBgColor,
            "Set the background color. This also overrides the behavior of save().",
            py::arg("red"),
            py::arg("green"),
            py::arg("blue"),
            py::arg("alpha") = 255
        )
        //setter funcs
        .def(
            "set_resizable", 
            &Window::setResizable, 
            "Make the window resizable. This is automatically called when you maximize or minimize the window.",
            py::arg("set") = true
        )
        .def(
            "set_minimized", 
            &Window::setMinimized,
            "Minimize the window.",
            py::arg("set") = true
        )
        .def(
            "set_maximized", 
            &Window::setMaximized,
            "Maximize the window",
            py::arg("set") = true
        )
        //size funcs
        .def(
            "resize", 
            &Window::resize,
            "Resize the window.",
            py::arg("new_width"), 
            py::arg("new_height")
        )
        .def("get_size", [](Window& win) {
            int w, h;
            win.getSize(&w, &h);
            return make_pair(w, h);
        }, "Get the size of the window. Returns (width, height).")
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
        .def(
            "point", 
            &Window::point,
            "Draw a point at (x, y)",
            py::arg("x"), 
            py::arg("y")
        )
        .def(
            "draw_line", &Window::line, 
            "Draw a line from (x1, y1) to (x2, y2)",
            py::arg("x1"), py::arg("y1"), 
            py::arg("x2"), py::arg("y2")
        )
        .def(
            "fill_rect", &Window::fillRect, 
            "Draw a filled rectangle at (x, y)",
            py::arg("x"), py::arg("y"), 
            py::arg("width"), py::arg("height")
        )
        .def(
            "stroke_rect", &Window::strokeRect,
            "Draw the outline of a rectangle at (x, y)",
            py::arg("x"), py::arg("y"),
            py::arg("width"), py::arg("height")
        )
        .def(
            "save", 
            &Window::save, 
            "Save the window to become the background for the next frame. "  
            "This behavior is overriden if set_bg_color() is ever called "
            "in the same frame."
        )
        .def("clear", &Window::clear, "Clear the window.")
        .def_readonly("id", &Window::id, "The SDL ID of the window. Can be useful for debugging?")
        .def_readwrite(
            "update", 
            &Window::update, 
            "The update function for this window. If you're doing this: \"class Game(BaseGameWindow)\" "
            "then you don't need to worry about setting this to anything - BaseGameWindow does it for "
            "you in __init__()."
        );

    py::class_<KeyCombination>(m, "KeyCombination", "A combination of keys pressed together - like keyboard shortcuts")
        .def(
            py::init<int, int, func>(), 
            "Create a key combination with two keys, like Ctrl+C",
            py::arg("key1"), 
            py::arg("key2"), 
            py::arg("callback")
        )
        .def(
            py::init<int, int, int, func>(),
            "Create a key combination with three keys, like Ctrl+Alt+Delete",
            py::arg("key1"), 
            py::arg("key2"), 
            py::arg("key3"), 
            py::arg("callback")
        );

    py::class_<MouseKeyCombination>(m, "MouseKeyCombination", "A combination that fires when you hold a key and click")
        .def(
            py::init<int, mousecall>(),
            "Create a mouse-key combination",
            py::arg("key"), 
            py::arg("callback")
        );

    m.def("do_nothing", doNothing);

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

                try {
                    if (!callback.attr("__self__").is_none()) {
                        argCount--;
                        hasSelf = true;
                    }
                } catch (py::error_already_set&) {}

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
            "Adds a quit event for a certain key that destroys the window",
            py::arg("key"), 
            py::arg("callback") = py::cpp_function(doNothing)
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