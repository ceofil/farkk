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
	void Update(Keyboard& kbd, Ball& ball, float dt, bool& hitByBall);
	Rect GetRect();
	void SetLargeW();
	void SetNarrowW();
	void SetInitialX();
public:
	Color c;
	float w;
	bool cooldown = false;
	bool hit = false;
public:
	float x;
	float speed;
	float y;
	float h;
	float InitialWidth;
	static constexpr float centerPortion = 0.5f;
	static constexpr float exitRatio = 0.05f;
};