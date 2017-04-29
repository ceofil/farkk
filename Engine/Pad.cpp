#include "Pad.h"

Pad::Pad(float in_x, float in_y, float in_speed, float in_w, float in_h)
	:
	x(in_x),
	y(in_y),
	speed(in_speed),
	w(in_w),
	h(in_h),
	InitialWidth(in_w)
{
}

void Pad::Draw(Graphics & gfx)
{
	GetRect().Draw(gfx, c);
	gfx.DrawRect(int(x), int(y), int(w / 2.0f), int(h), Colors::Green);
}

void Pad::Update(Keyboard& kbd,Ball& ball, float dt, bool& hitByBall)
{
	if (kbd.KeyIsPressed(VK_LEFT)) {
		x -= speed*dt;
	}
	if(kbd.KeyIsPressed(VK_RIGHT)){
		x += speed*dt;
	}
	if (!cooldown && GetRect().isColliding(ball.GetRect())) {
		const Vec2 ballpoz = ball.GetPos();
		const Rect rec = GetRect();
		if (std::signbit(ball.GetVel().x) == std::signbit(ballpoz.x - x) )
		{
			ball.SetVel(Vec2((ball.GetPos().x - x)/w*2.0f, (ball.GetVel().y)*-1.0f).GetNormalized());
		}
		else
		{
			if (ballpoz.x > rec.left && ballpoz.x < rec.right) {
				ball.SetVel(Vec2((ball.GetPos().x - x) / w*2.0f, (ball.GetVel().y)*-1.0f).GetNormalized());
			}
			else {
				ball.toggleX();
			}
		}
		cooldown = true;
		hitByBall = true;
	}
	


	if(x-w/2.0f<=0.0f){
		x = w/2.0f;
	}
	if(x+w/2.0f>=Graphics::ScreenWidth){
		x = Graphics::ScreenWidth - w/2.0f - 1;
	}
}

Rect Pad::GetRect()
{
	return Rect(Vec2(x, y), w, h);
}

void Pad::SetLargeW()
{
	w = 1.5f * InitialWidth;
}

void Pad::SetNarrowW()
{
	w = 0.7f * InitialWidth;
}
