#pragma once
#include "Constants.h"
#include "Drawable.h"

class GameField;

class Knight;


class Item : public Drawable
{
public:
	Item(int _y, int _x, char _pic = Constants :: defaultIcon) : Drawable(_y, _x, _pic), picked(false) {};
	~Item();

	virtual void beUsed(Knight* knight) = 0;

	Item* bePicked(GameField* field);
	bool isPicked();
protected:
	bool picked;
	char pic;
};

