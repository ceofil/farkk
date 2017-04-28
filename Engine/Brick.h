#pragma once
#include "Rect.h"
#include "Graphics.h"
#include "Vec2.h"
#include "Ball.h"

class Brick 
{
public:
	void Init(Vec2 in_pos, float in_w, int type);
	void Draw(Graphics& gfx);
	bool isColliding(Ball& ball);
	void Update(Ball & ball);
	Rect getRect();
	Vec2 getCenter();
public:
	bool destroyed = false;
	Color c;
	int klife = 1;
	int totallife = 1;
	static constexpr float h = 20.0f;
	static constexpr int arrOfColors[5][3] = 
	{
		{75,75,75},
		{125,125,125},
		{175,175,175},
		{200,200,200},
		{255,255,255}
	}; 
	struct Effect
	{
		bool bomb = false;
		bool poop = false;
		bool wlarge = false;
		bool wsmall = false;
		bool block = false;
	};
	Effect effect;
	
private:
	Vec2 pos; //topleft
	float w;
	
	
};