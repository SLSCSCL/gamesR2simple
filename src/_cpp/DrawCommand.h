#pragma once
#ifndef SHAPES_H
#define SHAPES_H
#include <cstdint>

#include "macro.h"
#include "TextArea.h"

NAMESPACE

enum class ShapeType {
	POINT,
	LINE,
	FILL_RECT,
	STROKE_RECT,
	//Not supported yet
	FILL_TRI,
	STROKE_TRI,
	TEXT,
};

struct DrawCommand {
	ShapeType type;
	uint8_t r, g, b, a;

	DrawCommand(ShapeType _type, int _r, int _g, int _b, int _a) : type(_type), r(_r), g(_g), b(_b), a(_a) {}

	union {
		struct {
			int x, y;
		} point;
		struct {
			int x1, y1, x2, y2;
		} line;
		struct {
			int x, y, w, h;
		} rect;
		struct {
			int x1, y1, x2, y2, x3, y3;
		} tri;
		TextArea* text;
	};
};

END
#endif