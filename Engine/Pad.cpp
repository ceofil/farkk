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

void Pad::Update(Keyboard& kbd,Ball& ball)
{
	if (kbd.KeyIsPressed(VK_LEFT)) {
		x -= speed;
	}
	if(kbd.KeyIsPressed(VK_RIGHT)){
		x += speed;
	}
	if (GetRect().isColliding(ball.GetRect())) {
		ball.toggleY();
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
