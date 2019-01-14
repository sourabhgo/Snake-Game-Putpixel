#pragma once
#include"Box.h"
class Snake {
public:
	//Snake is implemented as a doublylinked list of Boxes
	Box* head;
	int vel = 2;
	direction movdir = right;//direction in which snake is moving
	int width=6;
	color SnakeColor;
	Snake();
	Snake(Box box);
	void SetMovDir(direction newDir);
	void IncreaseLen(int inc);
	void DecreaseLen(int dec);
	void IncreaseVel(int inc);
	void DecreaseVel(int dec);
	void IncreaseWidth(int inc);
	void DecreaseWidth(int dec);
	bool Move();
	bool CollisionCheck(Box * head);
	bool Collision(Box box1, Box box2);
	BoxCord ReturnBoxCord(Box box);
	void Erasetail();
	void ResetColor(color newColor);
	BoxCord Envelope();
	BoxCord ReturnHeadBoxCord();
	//True as long as the game is running
};