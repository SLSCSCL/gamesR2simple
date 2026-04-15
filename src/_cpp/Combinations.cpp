#include "Combinations.h"

NAMESPACE

KeyCombination::KeyCombination(int k1, int k2, func c) {
	key1 = k1;
	key2 = k2;
	callback = c;
}

KeyCombination::KeyCombination(int k1, int k2, int k3, func c) {
	key1 = k1;
	key2 = k2;
	key3 = k3;
	callback = c;
}

void KeyCombination::operator()() {
	callback();
}

bool KeyCombination::operator==(KeyCombination combo) {
	return key1 == combo.key1 && key2 == combo.key2 && key3 == combo.key3;
}

MouseKeyCombination::MouseKeyCombination(int k, mousecall c) {
	key = k;
	callback = c;
}

void MouseKeyCombination::operator()(pybind11::tuple coord) {
	callback(coord);
}

bool MouseKeyCombination::operator==(MouseKeyCombination other) {
	return key == other.key;
}

END