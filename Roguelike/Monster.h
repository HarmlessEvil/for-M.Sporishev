#pragma once
#include "Character.h"
#include "Knight.h"

class Monster :	public Character
{
public:
	Monster(int _y, int _x, int _attack = Constants::defaultAttack, int _HP = Constants::defaultHP, char _pic = Constants :: defaultIcon, int _sightRadius = Constants :: defaultSightRadius) : Character(_y, _x, _attack, _HP, _pic), sightRadius(_sightRadius) {};
	~Monster();
protected:
	int sightRadius;
};

