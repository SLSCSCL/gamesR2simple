#pragma once
#include <SDL3/SDL.h>
#include <pybind11/typing.h>
#define INIT



extern pybind11::typing::Dict<pybind11::str, int> keys;
extern bool created;

void initKeys();