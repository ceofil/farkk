#include "Poop.h"

void Poop::Spawn(float x, float y)
{
	pos.x = x;
	pos.y = y;
	spawned = true;
}

void Poop::Update(Pad& pad, float dt)
{
	Rect rect = GetRect();
	Rect padrect = pad.GetRect();
	if (rect.top < padrect.bot)
	{
		pos += vel.GetNormalized() * speed * dt;
		if (rect.isColliding(padrect))
		{
			pad.hit = true;
		}
	}
	else
	{
		spawned = false;
	}
}

void Poop::Draw(Graphics & gfx)
{
	SpriteCodex::DrawPoo(pos, gfx);
}

Rect Poop::GetRect()
{
	return Rect(pos.x - w / 2.0f, pos.y - h / 2.0f, pos.x + w / 2.0f, pos.y + h / 2.0f);
}
