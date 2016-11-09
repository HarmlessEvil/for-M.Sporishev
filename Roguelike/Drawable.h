#pragma once
#include "Constants.h"

class Drawable
{
public:
	Drawable(int _y, int _x, int _pic = Constants::defaultIcon) : y(_y), x(_x), pic(_pic) {};
	~Drawable();

	void getPosition(int& _y, int& _x) const;
protected:
	const char pic;
	int y, x;
};
