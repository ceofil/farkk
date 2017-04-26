#pragma once
#include "Vec2.h"
#include "SpriteCodex.h"
#include "Rect.h"
#include "Graphics.h"

class Ball
{
public:
	Ball(Vec2 in_pos, Vec2 vel);
	void toggleX();
	void toggleY();
	void wallbounce(const Rect& walls);
	void Draw(Graphics& gfx);
	void Update();
	Rect GetRect();
public:
	bool wallBounce;
private:
	Vec2 pos = { 100.0f,100.0f };
	Vec2 vel = { 10.0f,15.0f };
	static constexpr float r = 14.0f/2.0f; 
	Graphics& gfx;

};