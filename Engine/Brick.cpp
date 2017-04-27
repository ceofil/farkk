#include "Brick.h"

void Brick::Init(Vec2 in_pos, float in_w, float in_h)
{
	pos = in_pos;
	w = in_w;
	h = in_h;
}

void Brick::Draw(Graphics & gfx)
{
	//if (!destroyed) {
		getRect().DrawWithStroke(gfx, c);
	//}
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
	c = { 30,30,30 };
	destroyed = true;
}

Rect Brick::getRect()
{
	return Rect(pos,pos+Vec2(w,h));
}

Vec2 Brick::getCenter()
{
	return Vec2(pos.x + w / 2.0f, pos.y + h / 2.0f);
}
