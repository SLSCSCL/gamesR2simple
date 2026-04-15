#pragma once
#include <functional>
#include <pybind11/pytypes.h>
#include "macro.h"
using std::function;

NAMESPACE

typedef function<void()> func;					   //regular function
typedef function<void(pybind11::tuple)> mousecall; //mouse event callback

class KeyCombination {
public:
	int key1, key2 = 0, key3 = 0;
	func callback;

	KeyCombination(int k1, int k2, func c);
	KeyCombination(int k1, int k2, int k3, func c);

	void operator()();
	bool operator==(KeyCombination combo);
};

class MouseKeyCombination {
public:
	int key;
	mousecall callback;

	MouseKeyCombination(int k, mousecall c);

	void operator()(pybind11::tuple coord);
	bool operator==(MouseKeyCombination combo);
};

END