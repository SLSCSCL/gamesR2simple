#pragma once
#include <map>
#include <string>
#include "SDL3/SDL_scancode.h"
#include "macro.h"
using std::map;
using std::string;

NAMESPACE

typedef map<string, int> keyMap;

inline int cast(SDL_Scancode code);

keyMap getKeys();

END