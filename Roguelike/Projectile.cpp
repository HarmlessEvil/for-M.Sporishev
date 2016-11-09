#include "Projectile.h"
#include "Knight.h"

Projectile::~Projectile()
{
}

void Projectile :: makeTurn(Character* character, Renderer* renderer)
{
	int dx = 0, dy = 0;
	switch (dir) {
	case 'l': { dy--; break; }
	case 'r': { dy++; break; }
	case 'u': { dx--; break; }
	case 'd': { dx++; break; }
	}

	int x1, y1;
	if (character) {
		character->getPosition(y1, x1);
	}
	else {
		x1 = y1 = -1;
	}

	for (int i = 0; i < speed; i++) {
		if (!Character :: field->isCellOpen(y + dy, x + dx)) {
			hit(HP);
			if ((x + dx == x1) && (y + dy == y1)) {
				character->hit(attack);
				renderer->damaged(y1, x1, field);
				if (character->isDead()) {
					field->updateCell(y1, x1, Constants::floor);
				}
			}
			break;
		}
		move(y + dy, x + dx);
		field->updateCell(y - dy, x - dx, ((x - dx == parentx) && (y - dy == parenty)) ? parent : Constants :: floor);
		field->updateCell(y, x, pic);
		renderer->step(y - dy, x - dx, y, x, COLOR_PAIR(2), field);
	}

	if (isDead()) {
		field->updateCell(y, x, field->cell(y, x) == parent ? parent : Constants :: floor);
	}
}

char Projectile :: getDir()
{
	return dir;
}

int Projectile :: getSpeed()
{
	return speed;
}
