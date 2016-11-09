#pragma once
#include "Actor.h"

class Projectile :	public Actor
{
public:
	Projectile(int _y, int _x, char _dir, int y0, int x0, int _attack = Constants :: projectileAttack, char _parent = Constants::defaultIcon, int _HP = Constants :: projectileHP, char _pic = Constants :: projectileIcon, int _speed = Constants :: projectileSpeed) : Actor(_y, _x, _attack, _HP, _pic), parentx(x0), parenty(y0) ,speed(_speed), dir(_dir), parent(_parent) {};
	~Projectile();

	void makeTurn(Character* character, Renderer* renderer) override;

	char getDir();
	int getSpeed();
private:
	char dir;
	char parent;
	int parenty, parentx;
	int speed;
};
