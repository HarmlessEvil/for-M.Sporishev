#include "Character.h"

#include "Projectile.h"

GameField* Character :: field = 0;
size_t Character :: maxCount = 10;
Projectile** Character :: projectiles = (Projectile**)calloc(sizeof(Projectile*), Character :: maxCount);
unsigned int Character :: amount = 0;

Character :: ~Character()
{
}

void Character :: setGameField(GameField * _field)
{
	field = _field;
}

void Character :: increaseProjectileCapacity()
{
	maxCount *= 2;

	Projectile** old = projectiles;

	projectiles = (Projectile**)calloc(sizeof(Projectile), maxCount);

	for (unsigned int i = 0; i < amount; i++) {
		projectiles[i] = old[i];
	}

	free(old);
}

size_t Character :: getProjectilesMaxCount()
{
	return maxCount;
}

unsigned int Character :: getProjectilesAmount()
{
	return amount;
}

Projectile** Character :: getProjectileContainer()
{
	return projectiles;
}

void Character :: makeTurn(Character* character, Renderer* renderer)
{
	//Сообщение об ошибке? Exit? Exception?
}

int Character :: getAttack() const
{
	return attack;
}

void Character :: heal(int _HP)
{
	HP += _HP;
}

void Character :: hit(int enemyAttack)
{
	HP -= enemyAttack;
}

void Character :: move(const int _y, const int _x)
{
	if (((*((GameField *)field)).isCellOpen(_y, _x))) {
		y = _y;
		x = _x;
	}
}

void Character :: shoot(char dir)
{
	Projectile* pjt = new Projectile(y, x, dir, y, x, attack, pic);
	projectiles[amount++] = pjt;
}

GameField*& Character :: getGameField()
{
	return field;
}

void Character :: destroyProjectilesContainer()
{
	for (int i = 0; i < (int)amount; i++) {
		delete projectiles[i];
	}
	delete projectiles;

	amount = maxCount = 0;
}

bool Character :: isDead()
{
	return HP <= 0;
}
