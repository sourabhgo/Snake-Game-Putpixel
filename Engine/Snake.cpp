#include<assert.h>
#include "Box.h"
#include "Snake.h"
#include "Graphics.h"
Snake::Snake() {
	//Default constructor
	color defColor;
	defColor.r = 0;
	defColor.g = 255;
	defColor.b = 0;
	Box* box = new Box(200, 200, 600, 200, 6, HORZ, defColor, right);
	head = box;
	head->next = nullptr;
	SnakeColor = defColor;
}

Snake::Snake(Box box) {//Insert key for changing cursor:VS tips
	//Custom starting snake
	head = new Box(box);
	head->next = nullptr;
}

void Snake::SetMovDir(direction newDir) {
	movdir = newDir;
}

void Snake::IncreaseLen(int inc) {
	Box* it;
	it = head;
	while (it->next) {
		it = it->next;
	}
	//it is now the tail box
	if (it->orient == HORZ) {
		if (it->Boxdir == left) {
			it->posX2 = it->posX2 +inc;
		}
		if (it->Boxdir == right) {
			it->posX1 = it->posX1 -inc;
		}
	}

	if (it->orient == VER) {
		if (it->Boxdir == up) {
			it->posY2 = it->posY2 + inc;
		}
		if (it->Boxdir == down) {
			it->posY1 = it->posY1 -inc;
		}
	}

	//Check if the tail is finished and move tail to next box i.e; delete the tail box

	if (((it->posX2 - it->posX1) <= 0) && ((it->posY2 - it->posY1) <= 0)) {
		Box *temp;
		temp = head;
		if (temp->next)
			while (temp->next->next)
				temp = temp->next;
		temp->next = nullptr;
		delete it;
	}
}

void Snake::DecreaseLen(int dec) {
	Box* it;
	it = head;
	while (it->next) {
		it = it->next;
	}
	//it is now the tail box
	if (it->orient == HORZ) {
		if (it->Boxdir == left) {
			it->posX2 = it->posX2 - dec;
		}
		if (it->Boxdir == right) {
			it->posX1 = it->posX1 + dec;
		}
	}

	if (it->orient == VER) {
		if (it->Boxdir == up) {
			it->posY2 = it->posY2 - dec;
		}
		if (it->Boxdir == down) {
			it->posY1 = it->posY1 + dec;
		}
	}

	//Check if the tail is finished and move tail to next box i.e; delete the tail box

	if (((it->posX2 - it->posX1) <= 0) && ((it->posY2 - it->posY1) <= 0)) {
		Box *temp;
		temp = head;
		if (temp->next)
			while (temp->next->next)
				temp = temp->next;
		temp->next = nullptr;
		delete it;
	}
}
void Snake::IncreaseVel(int inc) {
	vel = vel + inc;
}
void Snake::DecreaseVel(int dec) {
	if((vel-dec)>0)
		vel = vel - dec;
}

void Snake::IncreaseWidth(int inc) {
	width = width + inc;
}

void Snake::DecreaseWidth(int dec) {
	if((width-dec)>0)
		width = width - dec;
}
bool Snake::Move() {// returns 0 on success, 1 on faliure
	if (head->orient == HORZ) {
		//Moving in Same Direction as previously
		if (movdir == left) {
			if (movdir != head->Boxdir) {
				//Player pressing left key when moving right
				head->posX2 = head->posX2 + vel;//KEEP MOVING IN RIGHT DIR
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
			else {
				head->posX1 = head->posX1 - vel;//move along left
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
		}
		if (movdir == right) {
			if (movdir != head->Boxdir) {
				//Player pressing right key when moving left
				head->posX1 = head->posX1 - vel;//KEEP MOVING IN LEFT DIR
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
			else {
				head->posX2 = head->posX2 + vel;//move along right
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
		}
		//Changing Direction
		if (movdir == up) {
			Box* temp;
			if (head->Boxdir == left) {
				temp = new Box(head->posX1, head->posY1 - vel/*remember this must be lower one*/, head->posX1, head->posY1, width, VER, SnakeColor, up);
				temp->next = head;
				head = temp;
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
			if (head->Boxdir == right) {
				temp = new Box(head->posX2, head->posY2 - vel/*remember this must be lower one*/, head->posX2, head->posY2, width, VER, SnakeColor, up);
				temp->next = head;
				head = temp;
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
		}
		if (movdir == down) {
			Box* temp;
			if (head->Boxdir == left) {
				temp = new Box(head->posX1, head->posY1/*remember this must be lower one*/, head->posX1, head->posY1 + vel, width, VER, SnakeColor, down);
				temp->next = head;
				head = temp;
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
			if (head->Boxdir == right) {
				temp = new Box(head->posX2, head->posY2/*remember this must be lower one*/, head->posX2, head->posY2 + vel, width, VER, SnakeColor, down);
				temp->next = head;
				head = temp;
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}

		}
	}


	if (head->orient == VER) {
		//Moving in Same Direction as previously
		if (movdir == up) {
			if (movdir != head->Boxdir) {
				//Player pressing up key when moving down
				head->posY2 = head->posY2 + vel;//KEEP MOVING DOWN
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
			else {
				head->posY1 = head->posY1 - vel;//move up
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
		}
		if (movdir == down) {
			if (movdir != head->Boxdir) {
				//Player pressing down key when moving up
				head->posY1 = head->posY1 - vel;//KEEP MOVING UP
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
			else {
				head->posY2 = head->posY2 + vel;//move down
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
		}
		//Changing Direction
		if (movdir == left) {
			Box* temp;
			if (head->Boxdir == up) {
				temp = new Box(head->posX1 - vel, head->posY1/*remember this must be lower one*/, head->posX1, head->posY1, width, HORZ, SnakeColor, left);
				temp->next = head;
				head = temp;
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
			if (head->Boxdir == down) {
				temp = new Box(head->posX2 - vel, head->posY2/*remember this must be lower one*/, head->posX2, head->posY2, width, HORZ, SnakeColor, left);
				temp->next = head;
				head = temp;
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
		}
		if (movdir == right) {
			Box* temp;
			if (head->Boxdir == up) {
				temp = new Box(head->posX1, head->posY1/*remember this must be lower one*/, head->posX1 + vel, head->posY1, width, HORZ, SnakeColor, right);
				temp->next = head;
				head = temp;
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
			if (head->Boxdir == down) {
				temp = new Box(head->posX2, head->posY2/*remember this must be lower one*/, head->posX2 + vel, head->posY2, width, HORZ, SnakeColor, right);
				temp->next = head;
				head = temp;
				if (CollisionCheck(head))
					return true;
				else
					return false;
			}
		}
	}

	return true;
}

bool Snake::CollisionCheck(Box* head) {
	//Also checks if head has hit boundary
	//Now before drawing on screen check for collision
	Box* it;
	Box* temphead = head;
	//Compare temphead with it
	//Keeping a gap of 10pix from Boundary
	bool a = (head->posX1 > 10);
	bool b = (head->posX2 < Graphics::ScreenWidth-10);
	bool c = (head->posY1 > 0);
	bool d = (head->posY2 < Graphics::ScreenHeight-10);
	if (!(a&b&c&d))
		return false;
	if ((head) && (head->next)) {
		it = head->next->next;
		while (it) {
			if (Collision(*temphead, *it)) {
				return false;//FALSE MOVE
			}
			it = it->next;//Missing this caused me a lot of problem
		}
	}

	return true;
}

bool Snake::Collision(Box box1, Box box2) {
	BoxCord boxCord1, boxCord2;
	boxCord1 = ReturnBoxCord(box1);
	boxCord2 = ReturnBoxCord(box2);
	if ((boxCord2.startX > boxCord1.endX) || (boxCord1.startX > boxCord2.endX) || (boxCord2.startY < boxCord1.endY) || (boxCord1.startY < boxCord2.endY))
		return false;
	else
		return true;
}
BoxCord Snake::ReturnBoxCord(Box box) {
	BoxCord result;
	if (box.orient == HORZ) {
		assert(box.posY1 == box.posY2);
		result.startX = box.posX1;
		result.endX = box.posX2;
		result.startY = box.posY1 + width / 2;
		result.endY = box.posY2 - width / 2;//Y1 == Y2
	}
	if (box.orient == VER) {
		assert(box.posX1 == box.posX2);
		result.startX = box.posX1 - width / 2;
		result.endX = box.posX2 + width / 2;//X1==X2
		result.startY = box.posY2;
		result.endY = box.posY1;
	}
	return result;
}

void Snake::Erasetail() {
	Box* it;
	it = head;
	while (it->next) {
		it = it->next;
	}
	//it is now the tail box
	if (it->orient == HORZ) {
		if (it->Boxdir == left) {
			it->posX2 = it->posX2 - vel;
		}
		if (it->Boxdir == right) {
			it->posX1 = it->posX1 + vel;
		}
	}

	if(it->orient == VER) {
		if (it->Boxdir == up) {
			it->posY2 = it->posY2 - vel;
		}
		if (it->Boxdir == down) {
			it->posY1 = it->posY1 + vel;
		}
	}

	//Check if the tail is finished and move tail to next box i.e; delete the tail box

	if (((it->posX2 - it->posX1) <= 0) && ((it->posY2 - it->posY1) <= 0)) {
		Box *temp;
		temp = head;
		if(temp->next)
			while (temp->next->next)
				temp = temp->next;
		temp->next = nullptr;
		delete it;
	}
}

void Snake::ResetColor(color newColor) {
	Box *it;
	it = head;
	while (it) {
		it->Boxcol = newColor;
		it = it->next;
	}
}


BoxCord Snake::Envelope() {
	BoxCord result;
	Box* it;
	it = head;
	int maxX=head->posX2, maxY=head->posY2, minX=head->posX1, minY=head->posY1;
	it = it->next;
	while (it) {
		if (it->posX2 > maxX)
			maxX = it->posX2;
		if (it->posX1 < minX)
			minX = it->posX1;
		if (it->posY2 > maxY)
			maxY = it->posY2;
		if (it->posY1 < minY)
			minY = it->posY1;
		it = it->next;
	}
	result.startX = minX;
	result.endX = maxX;
	result.startY = minY;
	result.endY = maxY;
	return result;
}

BoxCord Snake::ReturnHeadBoxCord() {
	return ReturnBoxCord(*head);
}