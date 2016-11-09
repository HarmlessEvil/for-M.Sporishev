#pragma once
#include "Monster.h"

class Dragon : public Monster
{
public:
	Dragon(int _y, int _x, int _attack = Constants::dragonAttack, int _HP = Constants::dragonHP, char _pic = (Constants :: dragonIcon), int _sightRadius = Constants::defaultSightRadius) : Monster(_y, _x, _attack, _HP, _pic, _sightRadius) {};
	~Dragon();

	void makeTurn(Character* character, Renderer* renderer) override;
};

