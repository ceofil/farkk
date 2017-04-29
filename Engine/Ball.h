#pragma once
#include "Vec2.h"
#include "SpriteCodex.h"
#include "Rect.h"
#include "Graphics.h"

class Ball
{
public:
	Ball(Vec2 in_pos, Vec2 vel, float in_speed);
	void toggleX();
	void toggleY();
	void wallbounce(const Rect& walls);
	void Draw(Graphics& gfx);
	void Update(float dt);
	Rect GetRect();
	Vec2 GetPos();
	Vec2 GetVel();
public:
	bool wallBounce;
	bool padBounce;
private:
	Vec2 pos;
	Vec2 vel;
	float speed;
	static constexpr float r = 14.0f/2.0f; 
	Graphics& gfx;

};