#include "Drawable.h"

Drawable::~Drawable()
{
}

void Drawable :: getPosition(int& _y, int& _x) const
{
	_y = y;
	_x = x;
}