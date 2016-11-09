#pragma once

#include "Monster.h"

class Zombie : public Monster
{
public:
	Zombie(int _y, int _x, int _attack = Constants::zombieAttack, int _HP = Constants::zombieHP, char _pic = (Constants :: zombieIcon), int _sightRadius = Constants::defaultSightRadius) : Monster(_y, _x, _attack, _HP, _pic, _sightRadius) {};
	~Zombie();

	void makeTurn(Character* character, Renderer* renderer) override;
};

