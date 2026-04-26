#pragma once
#ifndef SHAPES_H
#define SHAPES_H
#include <cstdint>

enum class ShapeType {
	POINT,
	LINE,
	FILL_RECT,
	STROKE_RECT,
	//Not supported yet
	FILL_TRI,
	STROKE_TRI,
};

struct DrawCommand {
	ShapeType type;
	uint8_t r, g, b, a;

	DrawCommand(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a) {}

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
	};
};

#endif