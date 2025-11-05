#pragma once
#include <SDL3/SDL_keycode.h>
#include <pybind11/pybind11.h>
using func = pybind11::function;
using Key = SDL_Keycode;

class Combination {
public:
	Key key1, key2, key3 = SDLK_UNKNOWN;
	func callback;

	Combination(Key k1, func c);
	Combination(Key k1, Key k2, func c);
	Combination(Key k1, Key k2, Key k3, func c);

	void operator()();
};