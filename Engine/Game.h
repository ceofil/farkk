/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <cmath>
#include <random>
#include "Text.h"
#include <chrono>
#include "Rect.h"
#include "SpriteCodex.h"
#include "Ball.h"
#include "Brick.h"
#include "Pad.h"
#include "FrameTimer.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	FrameTimer ft;
	static constexpr int nrbricks = 16;
	static constexpr int wbricks = 40;
	static constexpr int hbricks = 20;
	static constexpr int space = (Graphics::ScreenWidth - nrbricks*wbricks)/2;
	static constexpr int nrraws = 10;
	Color cls[2] = {
		{255,255,0},
		//{255,0,0},
		//{0,255,0},
		//{0,0,255},
		{255,0,255}
	};

	std::random_device rd;
	std::mt19937 rng;
	Text txt;
	Ball ball;
	Pad pad;
	Brick brickz[nrraws][nrbricks];
	/********************************/
};


