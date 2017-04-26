#include "Rect.h"

Rect::Rect(float in_top, float in_left, float in_bot, float in_right)
	:
	top(in_top),
	left(in_left),
	bot(in_bot),
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
	Rect(center-Vec2(w,h)*0.5f, center + Vec2(w, h)*0.5f)
{
}



bool Rect::isColliding(const Rect & other)
{
	return	top<=other.bot &&
			bot>=other.top &&
			left<=other.right &&
			right>=other.left;
}

void Rect::Draw(Graphics & gfx)
{
	gfx.DrawRectPoints(int(left), int(top), int(right), int(bot), c);
}
