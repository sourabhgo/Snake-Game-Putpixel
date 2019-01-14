#pragma once

enum orientation { HORZ, VER };
enum direction { left, right, up, down };
struct color {
	int r;
	int g;
	int b;
	color() {
		r = 0;
		g = 255;
		b = 0;
	}
	color(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	color(const color &other) {
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
	}
	bool operator==(const color &a) {
		bool x = this->r == a.r;
		bool y = this->g == a.g;
		bool z = this->b == a.b;
		if (x&y&z)
			return true;
		else
			return false;
	}
	bool operator!=(const color &a) {
		bool x = this->r == a.r;
		bool y = this->g == a.g;
		bool z = this->b == a.b;
		if (x&y&z)
			return false;
		else
			return true;
	}
};
struct BoxCord {
	int startX, endX, startY, endY;
};

class Box {
public:
	int posX1;
	int posY1/*Lower X or Y first*/;
	int posX2;
	int posY2;
	int width;
	orientation orient;
	color Boxcol;//
	Box* next;
	direction Boxdir;

	Box(int posX1, int posY1, int posX2, int posY2, int width, orientation orient, color Boxcolor, direction Boxdir);

	Box(const Box & box);

};