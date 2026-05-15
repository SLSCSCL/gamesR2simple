#pragma once
#include <exception>
#include <string>
#include "macro.h"

NAMESPACE

#ifdef USING_PYTHON
#include <pybind11/pybind11.h>
#define PYERR(err) py::reinterpret_borrow<obj>(err)

namespace py = pybind11;

typedef py::object obj;
struct Errs {
    inline static obj Type = PYERR(PyExc_TypeError);
    inline static obj Runtime = PYERR(PyExc_RuntimeError);
    inline static obj Quit = PYERR(PyExc_Exception);
    inline static obj SDLInit;
    inline static obj Arg;
};

#endif

#define inherit : public Error {using Error::Error;}

class Error : public std::exception {using std::exception::exception;};
class SDLInitError inherit;
class ArgumentMismatchError inherit;
class TypeError inherit;

class ProgramExit inherit;

template<class Err>
[[noreturn]] void raise(const char* msg) {
#ifdef USING_PYTHON
    obj errTy;

    if constexpr (is_same_v<Err, TypeError>) {
        errTy = Errs::Type;
    }
    else if constexpr (is_same_v<Err, SDLInitError>) {
        errTy = Errs::SDLInit;
    }
    else if constexpr (is_same_v<Err, ArgumentMismatchError>) {
        errTy = Errs::Arg;
    }
    else if constexpr (is_same_v < Err, ProgramExit) {
        errTy = Errs::Quit;
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