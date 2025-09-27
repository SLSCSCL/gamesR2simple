#include "KeyCodes.h"

pybind11::typing::Dict<pybind11::str, int> keys{};
bool created = false;

void initKeys() {
	created = true;
	keys["Escape"] = 0; //This is how to init values
}