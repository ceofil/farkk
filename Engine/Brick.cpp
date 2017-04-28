#include "Brick.h"

void Brick::Init(Vec2 in_pos, float in_w, int type)
{
	pos = in_pos;
	w = in_w;
	if (type == 0) {
		klife = 1;
		effect.bomb = true;
		const Color cl(255, 0, 0);
		c = cl;
	}
	else if (type == 1) {
		effect.poop = true;
		klife = 1;
		const int r = arrOfColors[klife - 1][0];
		const int g = arrOfColors[klife - 1][1];
		const int b = arrOfColors[klife - 1][2];
		const Color cl(r, g, b);
		c = cl;
	}
	else if (type == 2) {
		effect.wlarge = true;
	}
	else if (type == 3) {
		effect.wsmall = true;
	}
	else if (type == 4) {
		effect.block = true;
	}
	else {
		
	}
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
	klife--;
	if(klife<1)
	{
		destroyed = true;
		c = { 5,5,5 };
	}
	else {
		const int r = arrOfColors[klife - 1][0];
		const int g = arrOfColors[klife - 1][1];
		const int b = arrOfColors[klife - 1][2];
		const Color cl(r, g, b);
		c = cl; 
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
