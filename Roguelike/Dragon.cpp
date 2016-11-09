#include "Dragon.h"

#include <math.h>

Dragon :: ~Dragon()
{
}

void Dragon :: makeTurn(Character* character, Renderer* renderer)
{
	char dir;

	GameField* pField = field;
	if (pField->dist(character, this) > sightRadius) {
		return;
	}

	if (pField->isOnFireLine(character, this, dir)) {
		shoot(dir);
		return;
	}

	int dx = pField->dx(character, this);
	int dy = pField->dy(character, this);

	if (abs(dx) <= abs(dy)) {
		if (dx < 0) {
			if (pField->isCellOpen(y, x - 1)) {
				move(y, x - 1);
				pField->updateCell(y, x + 1, Constants :: floor);
				pField->updateCell(y, x, pic);
			}
			else {
				if (dy < 0) {
					if (pField->isCellOpen(y - 1, x)) {
						move(y - 1, x);
						pField->updateCell(y + 1, x, Constants :: floor);
						pField->updateCell(y, x, pic);
					}
				}
				else {
					if (pField->isCellOpen(y + 1, x)) {
						move(y + 1, x);
						pField->updateCell(y - 1, x, Constants :: floor);
						pField->updateCell(y, x, pic);
					}
				}
			}
		}
		else {
			if (pField->isCellOpen(y, x + 1)) {
				move(y, x + 1);
				pField->updateCell(y, x - 1, Constants :: floor);
				pField->updateCell(y, x, pic);
			}
			else {
				if (dy < 0) {
					if (pField->isCellOpen(y - 1, x)) {
						move(y - 1, x);
						pField->updateCell(y + 1, x, Constants :: floor);
						pField->updateCell(y, x, pic);
					}
				}
				else {
					if (pField->isCellOpen(y + 1, x)) {
						move(y + 1, x);
						pField->updateCell(y - 1, x, Constants :: floor);
						pField->updateCell(y, x, pic);
					}
				}
			}
		}
	}
	else {
		if (dy < 0) {
			if (pField->isCellOpen(y - 1, x)) {
				move(y - 1, x);
				pField->updateCell(y + 1, x, Constants :: floor);
				pField->updateCell(y, x, pic);
			}
			else if (dx < 0) {
				if (pField->isCellOpen(y, x - 1)) {
					move(y, x - 1);
					pField->updateCell(y, x + 1, Constants :: floor);
					pField->updateCell(y, x, pic);
				}
			}
			else {
				if (pField->isCellOpen(y, x + 1)) {
					move(y, x + 1);
					pField->updateCell(y, x + 1, Constants :: floor);
					pField->updateCell(y, x, pic);
				}
			}
		}
		else {
			if (pField->isCellOpen(y + 1, x)) {
				move(y + 1, x);
				pField->updateCell(y - 1, x, Constants :: floor);
				pField->updateCell(y, x, pic);
			}
			else if (dx < 0) {
				if (pField->isCellOpen(y, x - 1)) {
					move(y, x - 1);
					pField->updateCell(y, x + 1, Constants :: floor);
					pField->updateCell(y, x, pic);
				}
			}
			else {
				if (pField->isCellOpen(y, x + 1)) {
					move(y, x + 1);
					pField->updateCell(y, x - 1, Constants :: floor);
					pField->updateCell(y, x, pic);
				}
			}
		}
	}

	if (pField->isOnFireLine(character, this, dir)) {
		shoot(dir);
	}

	if (isDead()) {
		pField->updateCell(y, x, Constants :: floor);
	}
}
