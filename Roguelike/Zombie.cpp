#include "Zombie.h"

Zombie :: ~Zombie()
{
}

void Zombie :: makeTurn(Character* character, Renderer* renderer)
{
	GameField* pField = field;
	if (pField->dist(character, this) > sightRadius) {
		return;
	}

	double u = pField->dist(character, y, x - 1);
	double d = pField->dist(character, y, x + 1);
	double l = pField->dist(character, y - 1, x);
	double r = pField->dist(character, y + 1, x);

	if ((u <= d) && (u <= l) && (u <= d)) {
		if (u == 0) {
			character->hit(attack);
			renderer->damaged(y, x - 1, field);
			return;
		}
		else if (pField->isCellOpen(y, x - 1)) {
			move(y, x - 1);
			pField->updateCell(y, x + 1, Constants :: floor);
			pField->updateCell(y, x, pic);
			return;
		}
	}
	else if ((d <= u) && (d <= l) && (d <= r)) {
		if (d == 0) {
			character->hit(attack);
			renderer->damaged(y, x + 1, field);
			return;
		}
		else if (pField->isCellOpen(y, x + 1)) {
			move(y, x + 1);
			pField->updateCell(y, x - 1, Constants :: floor);
			pField->updateCell(y, x, pic);
			return;
		}
	}
	else if ((l <= u) && (l <= d) && (l <= r)) {
		if (l == 0) {
			character->hit(attack);
			renderer->damaged(y - 1, x, field);
			return;
		}
		else if (pField->isCellOpen(y - 1, x)) {
			move(y - 1, x);
			pField->updateCell(y + 1, x, Constants :: floor);
			pField->updateCell(y, x, pic);
			return;
		}
	}
	else {
		if (r == 0) {
			character->hit(attack);
			renderer->damaged(y + 1, x, field);
			return;
		}
		else if (pField->isCellOpen(y + 1, x)) {
			move(y + 1, x);
			pField->updateCell(y - 1, x, Constants :: floor);
			pField->updateCell(y, x, pic);
			return;
		}
	}

	if (pField->dist(character, this) == 1) {
		character->hit(attack);
		int x1, y1;
		character->getPosition(y1, x1);
		renderer->damaged(y1, x1, field);
	}

	if (isDead()) {
		pField->updateCell(y, x, Constants :: floor);
	}
}
