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


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	
	/********************************/
	/*  User Functions              */

	
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	

	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xrange;
	std::uniform_int_distribution<int> yrange;
	std::uniform_int_distribution<int> vrange;
	std::uniform_int_distribution<int> rgbrange;

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	float durationSecond=0.0f;

	Text nr,text;

	int test = 0;
	int x = 1, y = 1;
	int kframe = 0;
	int k = 0;

	Color white = { 255,255,255 };
	/********************************/
};

