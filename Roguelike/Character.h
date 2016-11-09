#pragma once

#include "Drawable.h"
#include "GameField.h"
#include "Constants.h"
#include "Renderer.h"

class Knight;
class Renderer;

class Projectile;

class Character : public Drawable
{
public:
	Character(int _y, int _x, int _attack = Constants :: defaultAttack, int _HP = Constants :: defaultHP, char _pic = Constants :: defaultIcon) : Drawable(_y, _x, _pic), attack(_attack), HP(_HP) {};
	~Character();

	static Projectile** getProjectileContainer();
	static GameField*& getGameField();
	static void destroyProjectilesContainer();
	static void increaseProjectileCapacity();
	static void setGameField(GameField* _field);
	static size_t getProjectilesMaxCount();
	static unsigned int getProjectilesAmount();

	virtual void makeTurn(Character* character, Renderer *renderer);

	void heal(int _HP);
	void hit(int enemyAttack);
	void move(const int _y, const int _x);
	void shoot(char dir);
	bool isDead();
	int getAttack() const;
protected:
	int attack;
	int HP;

	static Projectile** projectiles;
	static GameField* field;
	static unsigned amount;
	static size_t maxCount;
};

