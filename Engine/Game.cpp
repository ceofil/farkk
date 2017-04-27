/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <cmath>
#include <random>
#include <chrono>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	txt(gfx, 1, 1, 2, 2, 50, 50),
	ball(Vec2(350.0f, 10.0f), Vec2(-1.0f, -0.5f), 350.0f),
	pad(400.0f,float(Graphics::ScreenHeight-75),350.0f,100.0f,40.0f)
{	
	pad.c = { 255,255,255 };
	for (int i = 0; i < nrraws; i++)
	{
		for (int j = 0; j < nrbricks; j++)
		{
			brickz[i][j].Init(Vec2(float(j*wbricks+space+wbricks/2), float(i*hbricks+hbricks+hbricks/2)), float(wbricks), float(hbricks));
			brickz[i][j].c = cls[i % 2];
		}
	}
}//make it so it spanws new layers of bricks over time

void Game::Go()
{
	gfx.BeginFrame();
	float timeperiod = ft.Mark();
	while (timeperiod > 0.0f)
	{
		const float dt = std::min(0.0025f,timeperiod);
		UpdateModel(dt);
		timeperiod -= dt;
	}
	
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{

	ball.Update(dt);

	float mini = Graphics::ScreenWidth;
	int targeti = -1;
	int targetj = -1;
	for (int i = 0; i < nrraws; i++)
	{
		for (int j = 0; j < nrbricks; j++)
		{
			if (brickz[i][j].destroyed == false)
			{
				if (brickz[i][j].isColliding(ball)) 
				{
					float dist = (ball.GetPos() - brickz[i][j].getCenter()).getLengthSq();
					if (dist < mini)
					{
						mini = dist;
						targeti = i;
						targetj = j;
					}
				}
			}
		}
	}
	if (targeti >= 0) {
		brickz[targeti][targetj].Update(ball);
		pad.cooldown = false;
	}
	if (ball.wallBounce) {
		gfx.DrawCircle(400, 300, 10, Colors::Red); //replace with sound
		ball.wallBounce = false;
		pad.cooldown = false;

	}
	pad.Update(wnd.kbd, ball, dt);
}



void Game::ComposeFrame()
{
	
	
	for (int i = 0; i < nrraws; i++)
	{
		for (int j = 0; j < nrbricks; j++)
		{
			brickz[i][j].Draw(gfx);
		}
	}
	pad.Draw(gfx);
	ball.Draw(gfx);
	txt.drawint(int(pad.x), 50, 50, Colors::Green);
	txt.drawint(int(pad.y), 50, 70, Colors::Green);
}




