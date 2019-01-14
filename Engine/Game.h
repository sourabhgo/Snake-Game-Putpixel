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
#include "Snake.h"
#include "Box.h"

struct Ruby {
	int x;
	int y;
	//x,y contains coordinates of top left corner of ruby
	int radius;
	color col;
	float age = 0;
	float duration;
	bool isActive = false;
};

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
	void DrawRhombus(int centreX, int centreY, int radius, color col);
	int randomNoGenerator(int start, int end);
	void DrawBox(Box box);
	void DrawSnake(Box * head);
	void DrawRubies(Ruby r);
	bool GenerateRubies();
	bool Collision(BoxCord boxCord1, Ruby r);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	Snake python;
	void DrawBox(BoxCord box, color col);
	float age = 0;//time in sec since last ruby was formed
	bool Istimeinit = false;
	float duration = 0;//Duration for next Ruby
	const int max  = 10; //Maximum no. of rubies on screen at a time
	Ruby *rubyarr;
	int rubycount = 0;//No. of rubies on screen
	color *palette;
	int GamePoints = 0;
	bool LOSE = false;
	bool WIN = false;

	/********************************/
	/*  User Variables              */
	/********************************/
};