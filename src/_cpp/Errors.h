#pragma once
#include <exception>
#include <string>
#include "macro.h"
using namespace std;

NAMESPACE

#ifdef USING_PYBIND11
#include <pybind11/pybind11.h>
namespace py = pybind11;

typedef py::object obj;
struct Errs {
    inline static obj Type = py::reinterpret_borrow<obj>(PyExc_TypeError);
    inline static obj Runtime = py::reinterpret_borrow<obj>(PyExc_RuntimeError);
    inline static obj Quit;
    inline static obj WinOpen;
    inline static obj Arg;
    inline static obj KHandle;
};
#endif

#define inherit : public Error {using Error::Error;}

class Error : public exception {using std::exception::exception;};
class WindowOpeningError inherit;
class ArgumentMismatchError inherit;
class KeyHandlerExistsError inherit;
class TypeError inherit;

class ProgramExit inherit;

template<class Err>
[[noreturn]] void raise(const char* msg) {
#ifdef USING_PYBIND11
    obj errTy;

    if constexpr (is_same_v<Err, TypeError>) {
        errTy = Errs::Type;
    }
    else if constexpr (is_same_v<Err, WindowOpeningError>) {
        errTy = Errs::WinOpen;
    }
    else if constexpr (is_same_v<Err, ArgumentMismatchError>) {
        errTy = Errs::Arg;
    }
    else if constexpr (is_same_v<Err, KeyHandlerExistsError>) {
        errTy = Errs::KHandle;
    }
    else {
        errTy = Errs::Runtime;
    }

    obj err = errTy(msg);
    err.attr("__cause__") = py::none();

    PyErr_SetObject(errTy.ptr(), err.ptr());
    throw py::error_already_set();
#else
    throw Err(msg);
#endif
}

END