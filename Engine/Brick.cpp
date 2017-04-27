#include "Brick.h"

void Brick::Init(Vec2 in_pos, float in_w, float in_h)
{
	pos = in_pos;
	w = in_w;
	h = in_h;
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
	if (isColliding(ball))
	{
		
		bool xsens = false;
		bool ysens = false;
		const Vec2 ballpoz = ball.GetPos();
		const Rect brickrec = getRect();

		
		if (ballpoz.y < brickrec.top || ballpoz.y > brickrec.bot) {
			ball.toggleY();
		}
		else {
			ball.toggleX();
		}
		destroyed = true;
	}
}

Rect Brick::getRect()
{
	return Rect::TopLeftWH(pos, w, h);
}
