#pragma once
#include "Character.h"

class Princess : public Character
{
public:
	Princess(int _y, int _x, int _attack = Constants :: princessAttack, int _HP = Constants :: princessHP, char _pic = Constants::princessIcon) : Character(_y, _x, _attack, _HP, _pic) {};
	~Princess();
};

