#pragma once
#include <SDL3/SDL_keycode.h>
#include <pybind11/pybind11.h>
using namespace pybind11::literals;

//extern int* keyCodes;

pybind11::dict getKeys();