#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"

class Rect
{
public:
	Rect() = default;
	Rect(float in_top, float in_left, float in_bot, float in_right);
	Rect(Vec2 topleft, Vec2 downright);
	Rect(Vec2 center, float w, float h);
	static Rect TopLeftWH(Vec2 topleft, float w, float h);
	bool isColliding(const Rect& other);
	void Draw(Graphics& gfx);
public:
	float top;
	float bot;
	float left;
	float right;
	Color c = Color( 255,0,0 );
};