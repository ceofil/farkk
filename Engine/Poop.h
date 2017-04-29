#pragma once
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Vec2.h"
#include "Pad.h"
#include "Rect.h"
class Poop
{
public:
	void Spawn(float x, float y);
	void Update(Pad& pad, float dt);
	void Draw(Graphics& gfx);
	Rect GetRect();
public:
	bool spawned = false;
	static constexpr float w = 14.0f;
	static constexpr float h = 14.0f;
	static constexpr float speed = 300.0f;
private:
	Vec2 pos; //center
	Vec2 vel = { 0.0f, 1.0f };
};