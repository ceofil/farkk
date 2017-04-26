#include "Ball.h"

Ball::Ball(Vec2 in_pos, Vec2 in_vel)
	:
	pos(in_pos),
	vel(in_vel),
	gfx(gfx)
{
}

void Ball::toggleX()
{
	vel.x = -vel.x;
}

void Ball::toggleY()
{
	vel.y = -vel.y;
}

void Ball::wallbounce(const Rect& walls)
{
	bool bounce = false;
	const Rect rect = GetRect();
	if (rect.top <= walls.top) {
		wallBounce = true;
		toggleY();
		pos.y = walls.top + r;
	}
	else if (rect.bot >= walls.bot) {
		wallBounce = true;
		toggleY();
		pos.y = walls.bot - r;

	}

	if (rect.left <= walls.left) {
		wallBounce = true;
		toggleX();
		pos.x = walls.left + r;
	}
	else if (rect.right >= walls.right) {
		wallBounce = true;
		toggleX();
		pos.x = walls.right - r;
	}
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(pos,gfx);
}

void Ball::Update()
{
	pos += vel;
	wallbounce(Rect(Vec2(1.0f, 1.0f), Vec2(float(Graphics::ScreenWidth - 1), float(Graphics::ScreenHeight-1))));
}

Rect Ball::GetRect()
{
	return Rect(pos, r * 2.0f, r * 2.0f);
}
