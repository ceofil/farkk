#include "Rect.h"

Rect::Rect(float in_top, float in_bot, float in_left, float in_right)
	:
	top(in_top),
	bot(in_bot),
	left(in_left),
	right(in_right)
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
	Rect(center.x - w / 2, center.y - h / 2, center.x + w / 2, center.x + h / 2)
{
}

void Rect::RectInit(Vec2 topleft, float w, float h, Color in_c)
	
{
	Rect(topleft.x, topleft.y, topleft.x + w, topleft.y + h);
	c = in_c;
}

bool Rect::isColliding(const Rect & other)
{
	return	top<other.bot &&
			bot>other.top &&
			left<other.right &&
			right>other.left;
}

void Rect::Draw(Graphics & gfx)
{
	gfx.DrawRectPoints(right, top, left, bot, c);
}
