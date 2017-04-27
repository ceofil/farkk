#pragma once
#include "Ball.h"
#include "Vec2.h"
#include "Rect.h"
#include "Graphics.h"
#include "Keyboard.h"

class Pad
{
public:
	Pad(float in_x, float in_y, float in_speed, float in_w, float in_h);
	void Draw(Graphics& gfx);
	void Update(Keyboard& kbd, Ball& ball, float dt);
	Rect GetRect();
public:
	Color c;
	float w;
	bool cooldown = false;
public:
	float x;
	float speed;
	float y;
	float h;
};