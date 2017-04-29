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
	colonrange(0,nrbricks-1),
	typerange(0, 5),
	percent(1,100),
	txt(gfx, 1, 1, 2, 2, 50, 50),
	ball(Vec2(350.0f, 500.0f), Vec2(-.5f, -1.5f), speed),
	pad(400.0f,float(Graphics::ScreenHeight-75),speed,100.0f,10.0f)
{	
	pad.c = { 255,255,255 };
	for (int i = 0; i < nrraws; i++)
	{
		for (int j = 0; j < nrbricks; j++)
		{
			brickz[i][j].Init(Vec2(float(j*wbricks+space), float((i+1)*Brick::h+space)), float(wbricks), 1 );
		}
	}
	largerate += bombrate;
	narrowrate += largerate;
	blockrate += narrowrate;
	pooprate += blockrate;
	respawnrate += pooprate;
	for (int i = 0; i < nrbricks; i++)
	{
		path[i] = false;
	}

}

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
	
	if (!started)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			started = true;
		}
	}
	else {
		if (!gameover) {
			win = !(bricksleft);
			defeat = (ball.GetPos().y > Graphics::ScreenHeight - Brick::h) || pad.hit;
			/*
			if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
			{
				win = true;
			}
			*/
			gameover = win || defeat;
			bricksLeft();
			if (ispoopin)
			{
				for (int i = 0; i < kpoopz; i++)
				{
					if (poopz[i].spawned)
					{
						poopz[i].Update(pad, dt);
					}
				}
			}

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
				doEffect(targeti, targetj);
				pad.cooldown = false;
			}
			while (explosion)
			{
				for (int i = 0; i < nrraws; i++)
				{
					for (int j = 0; j < nrbricks; j++)
					{
						if (brickz[i][j].destroyed == true && brickz[i][j].effect.triggered == false)
						{
							explosion = false;
							doEffect(i, j);
						}
					}
				}
			}

			if (ball.wallBounce) {
				gfx.DrawCircle(400, 300, 10, Colors::Red); //replace with sound
				ball.wallBounce = false;
				pad.cooldown = false;

			}
			pad.Update(wnd.kbd, ball, dt, hitbyball);
			if (bricksLeftEmpty > 0)
			{
				if (hitbyball)
				{
					applied = false;
					while (applied == false)
					{
						spawnEffect(percent(rng));
					}

					hitbyball = false;
				}
			}
		}
		else
		{
			if (wnd.kbd.KeyIsPressed(VK_RETURN))
			{
				started = false;
				gameover = false;
				win = false;
				defeat = false;
				respawnBricks();
			}
		}
	}

	
}





void Game::ComposeFrame()
{
	if (started) {
		if (!gameover) {
			gfx.DrawRectPoints(1, 1, Graphics::ScreenWidth - 1, Graphics::ScreenHeight - 1, Color(30, 30, 30));
			const int xprogress = int(float(Graphics::ScreenWidth)*float(total - bricksleft) / float(total));
			gfx.DrawRectPoints(1, 1, xprogress, int(Brick::h), Colors::Green);
			txt.drawint(int(float(total - bricksleft) / float(total) * 100.0f), (xprogress - 5) / 4 - 2, 1, Colors::Black);

			for (int i = 0; i < nrraws; i++)
			{
				for (int j = 0; j < nrbricks; j++)
				{
					brickz[i][j].Draw(gfx);
				}
			}
			if (ispoopin)
			{
				for (int i = 0; i < kpoopz; i++)
				{
					if (poopz[i].spawned)
					{
						poopz[i].Draw(gfx);
					}
				}
			}

			pad.Draw(gfx);
			ball.Draw(gfx);
		}
		else
		{
			if (win) {
				txt.drawstring("are you happy now?", Graphics::ScreenWidth / 4 - 45, Graphics::ScreenHeight / 4, Colors::White);
			}
			else {
				txt.drawstring("game over", Graphics::ScreenWidth / 4 - 25, Graphics::ScreenHeight / 4 - 4, Colors::White);
				txt.drawstring("press enter", Graphics::ScreenWidth / 4 - 29, Graphics::ScreenHeight / 4 + 6, Colors::White);
			}
		}
	}
	else{
		txt.drawstring("press enter", Graphics::ScreenWidth / 4 - 29, Graphics::ScreenHeight / 4-4, Colors::White);
	}
}





void Game::doEffect(int i, int j)
{
		if (brickz[i][j].effect.bomb == true)
		{
			for (int li = 0; li < nrraws; li++)
			{
				for (int lj = 0; lj < nrbricks; lj++)
				{
					float dist = (brickz[li][lj].getCenter() - brickz[i][j].getCenter()).getLength();
					if (dist < float(2*wbricks) && dist > 1.0f) {
						brickz[li][lj].destroyed = true;
						if (brickz[li][lj].effect.block == true)
						{
							brickz[li][lj].effect.triggered = true;
						}
						explosion = true;
					}
				}
			}
		}
		
		if (brickz[i][j].effect.wlarge == true)
		{
			pad.SetLargeW();
		}
		
		if (brickz[i][j].effect.wsmall == true)
		{
			pad.SetNarrowW();
		}
		
		if (brickz[i][j].effect.poop == true)
		{
			for (int a = 0; a < kpoopz; a++)
			{
				if (poopz[a].spawned == false)
				{
					poopz[a].Spawn(brickz[i][j].getCenter().x, brickz[i][j].getCenter().y);
					ispoopin = true;
					break;
				}
			}
		}
		
		brickz[i][j].effect.triggered = true;
}

void Game::spawnEffect(int chance)
{
	int yEffect = colonrange(rng);
	int typeEffect = typerange(rng);
	if (chance <= int(100.0f*bombrate) )
	{
		for (int i = nrraws - 1; i >= 0; i--)
		{
			if (brickz[i][yEffect].destroyed == false && brickz[i][yEffect].effect.empty == true)
			{
				brickz[i][yEffect].SetEffects(0);
				applied = true;
				break;
			}
		}
	}
	else if (chance <= int(100.0f*largerate))
	{
		for (int i = nrraws - 1; i >= 0; i--)
		{
			if (brickz[i][yEffect].destroyed == false && brickz[i][yEffect].effect.empty == true)
			{
				brickz[i][yEffect].SetEffects(2);
				applied = true;
				break;
			}
		}
	}
	else if (chance <= int(100.0f*narrowrate))
	{
		for (int i = nrraws - 1; i >= 0; i--)
		{
			if (brickz[i][yEffect].destroyed == false && brickz[i][yEffect].effect.empty == true)
			{
				brickz[i][yEffect].SetEffects(3);
				applied = true;
				break;
			}
		}
	}
	else if (chance <= int(100.0f*blockrate))
	{

		if (path[yEffect] == false) {
			path[yEffect] = true;
			for (int i = nrraws - 1; i >= 0; i--)
			{
				if (brickz[i][yEffect].destroyed == false && brickz[i][yEffect].effect.empty == true)
				{
					brickz[i][yEffect].SetEffects(4);
					break;
				}
			}
		}
		applied = true;
	}
	else if (chance <= int(100.0f*pooprate))
	{
		for (int i = nrraws - 1; i >= 0; i--)
		{
			if (brickz[i][yEffect].destroyed == false && brickz[i][yEffect].effect.empty == true)
			{
				brickz[i][yEffect].SetEffects(5);
				applied = true;
				break;
			}
		}
	}
	else if(chance<= int(100*respawnrate)){
		if (total - bricksleft > 10) {
			for (int i = 0; i < nrraws; i++) {
				if (brickz[i][yEffect].destroyed == true)
				{
					respawnBrick(i, yEffect);
					applied = true;
				}
			}
		}
		else{
			applied = true;
		}
	}
	else{
		applied = true;
	}
	
}

void Game::bricksLeft()
{
	bricksleft = 0;
	bricksLeftEmpty = 0;
	for (int i = 0; i < nrraws; i++)
	{
		for (int j = 0; j < nrbricks; j++)
		{
			if (brickz[i][j].destroyed == false)
			{
				bricksleft++;
				if (brickz[i][j].effect.empty == true)
				{
					bricksLeftEmpty++;
				}
			}
		}
	}
}

void Game::respawnBrick(int i, int j)
{
	brickz[i][j].destroyed = false;
	brickz[i][j].effect.empty = true;
	brickz[i][j].effect.block = false;
	brickz[i][j].effect.bomb = false;
	brickz[i][j].effect.wlarge = false;
	brickz[i][j].effect.wsmall = false;
	brickz[i][j].effect.poop = false;
	brickz[i][j].Init(Vec2(float(j*wbricks + space), float((i + 1)*Brick::h + space)), float(wbricks), 1);
	brickz[i][j].effect.triggered = false;
}

void Game::respawnBricks()
{
	for (int i = 0; i < nrraws; i++) {
		for (int j = 0; j < nrbricks; j++) {
			respawnBrick(i, j);
		}
	}
	ball.SetInitialPos();
	ball.SetVel(Vec2(.5f, -1.0f));
	for (int i = 0; i < kpoopz; i++) {
		poopz[i].spawned = false;
	}
	pad.SetInitialX();
}



