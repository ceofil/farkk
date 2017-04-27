#include "Pad.h"

Pad::Pad(float in_x, float in_y, float in_speed, float in_w, float in_h)
	:
	x(in_x),
	y(in_y),
	speed(in_speed),
	w(in_w),
	h(in_h)
{
}

void Pad::Draw(Graphics & gfx)
{
	GetRect().Draw(gfx, c);
}

void Pad::Update(Keyboard& kbd,Ball& ball, float dt)
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
			ball.toggleY();
		}
		else
		{
			if (ballpoz.x > rec.left && ballpoz.x < rec.right) {
				ball.toggleY();
			}
			else {
				ball.toggleX();
			}
		}
		cooldown = true;
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
