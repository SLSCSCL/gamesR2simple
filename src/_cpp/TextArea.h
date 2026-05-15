#pragma once
#ifndef TEXT_AREA
#define TEXT_AREA
#include <string>

#include <SDL3_ttf/SDL_ttf.h>

#include "Font.h"
#include "macro.h"

NAMESPACE

class TextArea {
private:
	SDL_Texture* tex;
	SDL_Surface* surf;

	Font* font;
	std::string text;

	bool changed = true;
public:
	TextArea(Font* f, std::string str);

	void draw(SDL_Renderer* ren, int x, int y, int width, int height);
};

END
#endif