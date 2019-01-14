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
#include <random>
#include "MainWindow.h"
#include "Game.h"
#include "Box.h"

const color LBLUE(66, 194, 244);
const color DBLUE(0, 0, 255);
const color PINK(255, 20, 147);
const color YELLOW(255, 255, 0);
const color ORANGE(255, 165, 0);
const color WHITE(255, 255, 255);
const color GREEN(0, 255, 0);
Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	palette = new color[7];
	palette[0] = LBLUE;
	palette[1] = DBLUE;
	palette[2] = PINK;
	palette[3] = YELLOW;
	palette[4] = ORANGE;
	palette[5] = WHITE;
	palette[6] = GREEN;
	rubyarr = new Ruby[max];
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	//TASKS TO DO
	//IF SNAKE GOES OUT OF BOUNDARY YOU LOSE:DONE
	//IF SNAKE CROSSES HIMSELF YOU LOSE:DONE
	//IF GAMEPOINTS = 50 YOU WIM:DONE
	//BRICK GENERATION
	//if SNAKE HITS BRICK YOU LOSE
	//DISPLAY GAMESCORE ON SCREEN AT TOP RIGHT CORNER
	python.Erasetail();
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		python.movdir = up;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		python.movdir = down;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		python.movdir = left;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		python.movdir = right;
	}
	bool valid = python.Move();
	color newcol(255, 0, 0);
	if ((!valid)&&(python.SnakeColor!=newcol)) {
		python.ResetColor(newcol);
		LOSE = true;
	}
	for (int i = 0; i < max; i++) {
		if (rubyarr[i].isActive) {
			if (Collision(python.ReturnHeadBoxCord(), rubyarr[i])) {
				//NOW HANDLE CASES
				if (rubyarr[i].col == LBLUE) {
					//Increase Width
					python.IncreaseWidth(4);
					rubyarr[i].isActive = false;
				}
				if (rubyarr[i].col == DBLUE) {
					//Decrease Width
					python.DecreaseWidth(2);
					rubyarr[i].isActive = false;
				}
				if (rubyarr[i].col == PINK) {
					//Increase VELOCITY
					python.IncreaseVel(1);
					rubyarr[i].isActive = false;
				}
				if (rubyarr[i].col == YELLOW) {
					//Increase Width
					python.DecreaseVel(1);
					rubyarr[i].isActive = false;
				}
				if (rubyarr[i].col == ORANGE) {
					//Increase Width
					GamePoints += 1;
					rubyarr[i].isActive = false;
					if (GamePoints >= 50)
						WIN = true;
				}
				if (rubyarr[i].col == WHITE) {
					//Increase Length
					python.IncreaseLen(5);
					rubyarr[i].isActive = false;
				}
				if (rubyarr[i].col == GREEN) {
					//Decrease Length
					python.DecreaseLen(5);
					rubyarr[i].isActive = false;
				}
			}
		}
	}
	
	GenerateRubies();

}

void Game::ComposeFrame()
{
	if ((!LOSE)&(!WIN)) {
		DrawSnake(python.head);
		for (int i = 0; i < max; i++) {
			if (rubyarr[i].isActive) {
				DrawRubies(rubyarr[i]);
			}
		}
	}
	if (LOSE) {
		//ShowLoseMessage();
	}
	if (WIN) {
		//ShowWinMessage();
	}
	//ShowGameScore();
}

void Game::DrawRhombus(int topleftX, int topleftY,int radius, color col) {

	topleftX += radius;
	topleftY += radius;
	int y1 = topleftY, y2 = topleftY;
	while (radius > 0) {
		for (int i = -radius; i < radius; i++) {
			gfx.PutPixel(topleftX + i, y1, col.r, col.g, col.b);
			gfx.PutPixel(topleftX + i, y2, col.r, col.g, col.b);
		}
		y1++;
		y2--;
		radius--;
	}
}

int Game::randomNoGenerator(int start, int end)
{
	using namespace std;
	// uniformly-distributed integer random number 
	// generator that produces non-deterministic 
	// random numbers. 
	random_device rd;

	// A Mersenne Twister pseudo-random generator 
	// of 32-bit numbers with a state size of 
	// 19937 bits. 
	mt19937 gen(rd());

	// Uniform distribution 
	uniform_int_distribution<> dis(start, end);
	return dis(gen);
}
void Game::DrawBox(Box box) {
	if (box.orient == HORZ) {
		_ASSERT(box.posY1 == box.posY2);//Check wether lines are Horizontal
		for(int j=0; j<box.width;j++)//with top left corner as refrence drawing box
			for (int i = 0; i < (box.posX2 - box.posX1); i++) {
				gfx.PutPixel(box.posX1 + i, box.posY1 - (box.width / 2) + j,box.Boxcol.r,box.Boxcol.g,box.Boxcol.b);
			}
	}
	if (box.orient == VER) {
		_ASSERT(box.posX1 == box.posX2);//Check wether lines are Vertical
		for (int j = 0; j<box.width; j++)//with top left corner as refrence drawing box
			for (int i = 0; i < (box.posY2 - box.posY1); i++) {
				gfx.PutPixel(box.posX1 - (box.width / 2) + j,box.posY1 + i, box.Boxcol.r, box.Boxcol.g, box.Boxcol.b);
			}
	}
}

void Game::DrawSnake(Box *head) {
	Box* it = head;
	while (it) {
		DrawBox(*it);
		it = it->next;
	}
}

struct point {
	int x, y;
	point() {
		this->x = 0;
		this->y = 0;
	}
	point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	point(const point &a) {
		this->x = a.x;
		this->y = a.y;
	}
};
void Game::DrawRubies(Ruby r) {
	DrawRhombus(r.x, r.y, r.radius, r.col);
}

bool Game::GenerateRubies() {
	const  float SECS_PER_FRAME = float(1) / float(60);
	if (!Istimeinit) {
		age = 0;
		Istimeinit = true;
	}
	int i = 0;
	while (rubyarr[i].isActive) {
		i++;//Till you find unactive ruby
	}
	if (i == max)
		return false;//No space for ruby
	age += SECS_PER_FRAME;
	if ((i < max)&&(duration<=age)){
		rubyarr[i].col = palette[randomNoGenerator(0, 6)];
		rubyarr[i].duration = (float)randomNoGenerator(15, 25);
		rubycount++;
		rubyarr[i].age = 0;//age of ruby in secs
		rubyarr[i].isActive = true;
		rubyarr[i].radius = 5;
		BoxCord Block;
		Block = python.Envelope();
		point pointarr[4];
		const int gap = 30;//gap soo that ruby does not draw too close to boundary
		pointarr[0] = point(randomNoGenerator(gap, Graphics::ScreenWidth - gap), randomNoGenerator(gap, Block.startY));
		pointarr[1] = point(randomNoGenerator(gap, Graphics::ScreenWidth - gap), randomNoGenerator(Block.endY, Graphics::ScreenHeight - gap));
		pointarr[2] = point(randomNoGenerator(gap, Block.startX), randomNoGenerator(gap, Graphics::ScreenHeight - gap));
		pointarr[3] = point(randomNoGenerator(Block.endX, Graphics::ScreenWidth - gap), randomNoGenerator(gap, Graphics::ScreenHeight - gap));
		int rand = randomNoGenerator(0, 3);
		rubyarr[i].x = pointarr[rand].x;
		rubyarr[i].y = pointarr[rand].y;
		//We'll draw ruby in Compose frame;
		//Now we'll reset the duration for next ruby generation for game
		//condition for time duration till next ruby for game
		duration = (float)randomNoGenerator(rubycount * 5, (rubycount + 1) * 5);
		age = 0;
	}

}

//For drawing Blocks
void::Game::DrawBox(BoxCord box, color col) {
	for (int i = box.startX; i <= box.endX; i++)
		for (int j = box.startY; j <= box.endY; j++)
			gfx.PutPixel(i, j, col.r, col.g, col.b);
}

bool Game::Collision(BoxCord boxCord1, Ruby r) {
	BoxCord boxCord2;
	boxCord2.endY = r.y;
	boxCord2.startX = r.x;
	boxCord2.startY = r.y + 2 * r.radius;
	boxCord2.endX = r.x + 2 * r.radius;
	if ((boxCord2.startX > boxCord1.endX) || (boxCord1.startX > boxCord2.endX) || (boxCord2.startY < boxCord1.endY) || (boxCord1.startY < boxCord2.endY))
		return false;
	else
		return true;
}