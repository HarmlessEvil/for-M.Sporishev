#pragma once
#include "Character.h"

class Actor : public Character
{
public:
	Actor(int _y, int _x, int _attack = Constants :: defaultAttack, int _HP = Constants :: defaultHP, char _pic = Constants :: defaultIcon) : Character(_y, _x, _attack, _HP, _pic) {};
	~Actor();
};

