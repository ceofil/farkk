#pragma once
#include "Rect.h"
#include "Graphics.h"
#include "Vec2.h"
#include "Ball.h"

class Brick 
{
public:
	void Init(Vec2 in_pos, float in_w, int in_type);
	void Draw(Graphics& gfx);
	bool isColliding(Ball& ball);
	void Update(Ball & ball);
	Rect getRect();
	Vec2 getCenter();
	void SetEffects(int in_type);
	void SetRGB(int ir, int ig, int ib);
public:
	bool destroyed = false;
	int type;
	Color c;
	int klife = 1;
	int totallife = 1;
	static constexpr float h = 20.0f;
	struct Effect
	{
		bool empty = true;
		bool triggered = false;
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
	int r=0;
	int g=255;
	int b=255;
	
	
};