#include "Box.h"


Box::Box(int posX1, int posY1, int posX2, int posY2, int width, orientation orient, color Boxcolor, direction Boxdir) {
	this->Boxcol = Boxcol;
	this->next = nullptr;
	this->orient = orient;
	this->posX1 = posX1;
	this->posY1 = posY1;
	this->posX2 = posX2;
	this->posY2 = posY2;
	this->Boxdir = Boxdir;
	this->width = width;
}
Box::Box(const Box &box) {
	this->Boxcol = box.Boxcol;
	this->next = nullptr;
	this->orient = box.orient;
	this->posX1 = box.posX1;
	this->posY1 = box.posY1;
	this->posX2 = box.posX2;
	this->posY2 = box.posY2;
	this->Boxdir = box.Boxdir;
	this->width = box.width;
}
