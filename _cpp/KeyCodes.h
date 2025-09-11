#pragma once
#include "SDL3/SDL.h"
#include "pybind11/typing.h"
using pybind11::str;
using pybind11::typing::Dict;

Dict<str, int> keys;

void initKeys();