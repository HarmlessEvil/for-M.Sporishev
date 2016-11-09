#pragma once
#include "Item.h"

class Healkit :	public Item
{
public:
	Healkit(int _y, int _x, int _HP = Constants :: healkitHP, char _pic = Constants::healkitIcon) : Item(_y, _x, _pic), HP(_HP) {};
	~Healkit();

	void beUsed(Knight* knight);
	int getHP();
private:
	int HP;
};

