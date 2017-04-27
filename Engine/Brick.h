#pragma once
#include "Rect.h"
#include "Graphics.h"
#include "Vec2.h"
#include "Ball.h"

class Brick 
{
public:
	void Init(Vec2 in_pos, float in_w, float in_h);
	void Draw(Graphics& gfx);
	bool isColliding(Ball& ball);
	void Update(Ball & ball);
	Rect getRect();
	Vec2 getCenter();
public:
	bool destroyed = false;
	Color c;
private:
	Vec2 pos; //topleft
	float w;
	float h;
};