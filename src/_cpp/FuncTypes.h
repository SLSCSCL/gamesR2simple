#pragma once
#include <functional>

#include "macro.h"

NAMESPACE

//function types
typedef std::function<void()> func;                    //regular std::function
typedef std::function<void(int, int)> mousecall;       //mouse event callback
typedef std::function<void(int)> scrollcall, keyhcall; //scroll event callback
typedef std::function<void()> keycall;                 //key event callback

END