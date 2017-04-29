#include "Brick.h"

void Brick::Init(Vec2 in_pos, float in_w, int in_type)
{
	pos = in_pos;
	w = in_w;
	SetEffects(in_type);
}

void Brick::Draw(Graphics & gfx)
{
	if (!destroyed) {
		getRect().DrawWithStroke(gfx, c);
	}
}

bool Brick::isColliding(Ball & ball)
{
	return getRect().isColliding(ball.GetRect());
}

void Brick::Update(Ball & ball)
{
	const Vec2 ballpoz = ball.GetPos();
	const Rect brickrec = getRect();
	if (std::signbit(ball.GetVel().x) == std::signbit (   (ballpoz-getCenter()  )  .x)      )
	{
		ball.toggleY();
	}
	else 
	{
		if (ballpoz.x > brickrec.left && ballpoz.x < brickrec.right) {
			ball.toggleY();
		}
		else {
			ball.toggleX();
		}
	}
	if (!effect.block) {
		klife--;
		if (klife < 1)
		{
			destroyed = true;
		}
	}
	
}

Rect Brick::getRect()
{
	return Rect(pos,pos+Vec2(w,h));
}

Vec2 Brick::getCenter()
{
	return Vec2(pos.x + w / 2.0f, pos.y + h / 2.0f);
}

void Brick::SetEffects(int in_type)
{
	type = in_type;
	if (type == 0) {
		klife = 1;
		effect.bomb = true;
		SetRGB(255, 0, 0);
	}
	else if (type == 1) {
		klife = 1;
		SetRGB(255, 255, 255);
	}
	else if (type == 2) {
		effect.wlarge = true;
		SetRGB(0, 255, 0);
	}
	else if (type == 3) {
		effect.wsmall = true;
		SetRGB(255, 255, 0);
	}
	else if (type == 4) {
		effect.block = true;
		SetRGB(100, 100, 100);
	}
	else if (type == 5) {
		effect.poop = true;
		SetRGB(138, 77, 0);
	}
	effect.empty = false;
}

void Brick::SetRGB(int ir, int ig, int ib)
{
	r = ir;
	g = ig;
	b = ib;
	Color cl(r, g, b);
	c = cl;
}
