#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"

class Rect
{
public:
	Rect() = default;
	Rect(float in_top, float in_bot, float in_left, float in_right);
	Rect(Vec2 topleft, Vec2 downright);
	Rect(Vec2 center, float w, float h);
	void RectInit(Vec2 topleft, float w, float h, Color in_c);
	bool isColliding(const Rect& other);
	void Draw(Graphics& gfx);
public:
	float top;
	float bot;
	float left;
	float right;
	Color c;
};