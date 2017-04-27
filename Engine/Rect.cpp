#include "Rect.h"

Rect::Rect(float in_left, float in_top, float in_right, float in_bot )
	:
	left(in_left),
	top(in_top),
	right(in_right),
	bot(in_bot)
{
}

Rect::Rect(Vec2 topleft, Vec2 downright)
	:
	top(topleft.y),
	bot(downright.y),
	left(topleft.x),
	right(downright.x)
{
}

Rect::Rect(Vec2 center, float w, float h)
	:
	Rect(center-Vec2(w,h)*0.5f, center + Vec2(w, h)*0.5f)
{
}

Rect Rect::TopLeftWH(Vec2 center, float w, float h)
{
	//return Rect(center.x-w/2,center.y-h/2,center.x+w/2,center.y+h/2);
	return Rect(center - Vec2(w, h)*0.5f, center + Vec2(w, h)*0.5f);
}



bool Rect::isColliding(const Rect & other)
{
	return	top<=other.bot &&
			bot>=other.top &&
			left<=other.right &&
			right>=other.left;
}

void Rect::Draw(Graphics & gfx, Color& c)
{
	gfx.DrawRectPoints(int(left), int(top), int(right), int(bot), c);
}

void Rect::DrawWithStroke(Graphics & gfx, Color& c)
{
	gfx.DrawRectPointsStroke(int(left), int(top), int(right), int(bot), 2, c);
}
