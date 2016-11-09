#include "GameManager.h"

#include "GameField.h"

#include "Dragon.h"
#include "Knight.h"
#include "Princess.h"
#include "Zombie.h"

#include "Healkit.h"
#include "Projectile.h"

GameManager :: ~GameManager()
{
}

void GameManager :: loadAndGo()
{
	GameField* field = new GameField;
	Character :: setGameField(field);

	coordinates = (Character***)calloc(sizeof(Character**), field->x);
	coordinatesItems = (Item***)calloc(sizeof(Item**), field->x);

	for (int i = 0; i < field->x; i++) {
		coordinates[i] = (Character**)calloc(sizeof(Character*), field->y);
		coordinatesItems[i] = (Item**)calloc(sizeof(Item*), field->y);
	}

	int y, x;
	field->find(Constants :: knightIcon, x, y);
	knight = new Knight(y, x);
	coordinates[x][y] = knight;

	y = -1, x = 0;
	while (field->find(Constants :: zombieIcon, x, y, x, y + 1)) {
		Zombie* pZombie = new Zombie(y, x);
		monsters.push_back(pZombie);
		coordinates[x][y] = pZombie;
	}

	y = -1, x = 0;
	while (field->find(Constants :: dragonIcon, x, y, x, y + 1)) {
		Dragon* pDragon = new Dragon(y, x);
		monsters.push_back(pDragon);
		coordinates[x][y] = pDragon;
	}

	y = -1, x = 0;
	while (field->find(Constants :: healkitIcon, x, y, x, y + 1)) {
		Healkit* pHealKit = new Healkit(y, x);
		coordinatesItems[x][y] = pHealKit;
	}

	y = -1, x = 0;
	field->find(Constants :: princessIcon, x, y);
	princess = new Princess(y, x);
	coordinates[x][y] = princess;

	state = 1;
	return;
}

#define MELEE_ATTACK ' '
#define RESTART 'r'
#define SHOOT_UP 450
#define SHOOT_DOWN 456
#define SHOOT_LEFT 452
#define SHOOT_RIGHT 454
#define USE_ITEM_1 1
#define USE_ITEM_2 2
#define USE_ITEM_3 3
#define USE_LAST 'e'

void GameManager :: playerMove(int move)
{
	GameField* field = knight->getGameField();

	int y, x;

	knight->getPosition(y, x);

	move = move == Constants :: moveUp ? KEY_UP : move == Constants :: moveDown ? KEY_DOWN : move == Constants :: moveLeft ? KEY_LEFT : move == Constants :: moveRight ? KEY_RIGHT : move == Constants :: meleeAttack ? MELEE_ATTACK : move == Constants :: shootUp ? SHOOT_UP : move == Constants :: shootDown ? SHOOT_DOWN : move == Constants :: shootLeft ? SHOOT_LEFT : move == Constants :: shootRight ? SHOOT_RIGHT : move == Constants :: useItem1 ? USE_ITEM_1 : move == Constants :: useItem2 ? USE_ITEM_2 : move == Constants :: useItem3 ? USE_ITEM_3 : move == Constants :: useLastItem ? USE_LAST : move == Constants :: useLastItem ? RESTART : move;
	state = 2;

	switch (move) {
	case KEY_UP: {
		if (field->isCellOpen(y, x - 1)) {
			knight->move(y, x - 1);

			field->updateCell(y, x, Constants::floor);
			field->updateCell(y, x - 1, Constants :: knightIcon);

			coordinates[x - 1][y] = coordinates[x][y];
			coordinates[x][y] = 0;
		}
		else if (coordinatesItems[x - 1][y]) {
			playerPickUpItem(coordinatesItems[x - 1][y]);
			knight->move(y, x - 1);

			field->updateCell(y, x, Constants::floor);
			field->updateCell(y, x - 1, Constants::knightIcon);

			coordinates[x - 1][y] = coordinates[x][y];
			coordinates[x][y] = 0;
		}
		break;
	}
	case KEY_DOWN: {
		if (field->isCellOpen(y, x + 1)) {
			knight->move(y, x + 1);

			field->updateCell(y, x, Constants::floor);
			field->updateCell(y, x + 1, Constants::knightIcon);

			coordinates[x + 1][y] = coordinates[x][y];
			coordinates[x][y] = 0;
		}
		else if (coordinatesItems[x + 1][y]) {
			playerPickUpItem(coordinatesItems[x + 1][y]);
			knight->move(y, x + 1);

			field->updateCell(y, x, Constants::floor);
			field->updateCell(y, x + 1, Constants::knightIcon);

			coordinates[x + 1][y] = coordinates[x][y];
			coordinates[x][y] = 0;
		}
		break;
	}
	case KEY_LEFT: {
		if (field->isCellOpen(y - 1, x)) {
			knight->move(y - 1, x);

			field->updateCell(y, x, Constants::floor);
			field->updateCell(y - 1, x, Constants::knightIcon);

			coordinates[x][y - 1] = coordinates[x][y];
			coordinates[x][y] = 0;
		}
		else if (coordinatesItems[x][y - 1]) {
			playerPickUpItem(coordinatesItems[x][y - 1]);
			knight->move(y - 1, x);

			field->updateCell(y, x, Constants::floor);
			field->updateCell(y - 1, x, Constants::knightIcon);

			coordinates[x][y - 1] = coordinates[x][y];
			coordinates[x][y] = 0;
		}
		break;
	}
	case KEY_RIGHT: {
		if (field->isCellOpen(y + 1, x)) {
			knight->move(y + 1, x);

			field->updateCell(y, x, Constants::floor);
			field->updateCell(y + 1, x, Constants::knightIcon);

			coordinates[x][y + 1] = coordinates[x][y];
			coordinates[x][y] = 0;
		}
		else if (coordinatesItems[x][y + 1]) {
			playerPickUpItem(coordinatesItems[x][y + 1]);
			knight->move(y + 1, x);

			field->updateCell(y - 1, x, Constants::floor);
			field->updateCell(y, x, Constants::knightIcon);

			coordinates[x][y + 1] = coordinates[x][y];
			coordinates[x][y] = 0;
		}
		break;
	}
	case MELEE_ATTACK: {
		for (int i = x - Constants :: knightHitRadius; i <= x + Constants :: knightHitRadius; i++) {
			if (i < 0) continue;
			if (i >= field->x) break;
			for (int j = y - Constants :: knightHitRadius; j <= y + Constants :: knightHitRadius; j++) {
				if (j < 0) continue;
				if (j >= field->y) break;
				if (((i != x) || (j != y)) && (coordinates[i][j])) {
					coordinates[i][j]->hit(knight->getAttack());
					pRenderer->damaged(j, i, field);
					if (coordinates[i][j]->isDead()) {
						field->updateCell(j, i, Constants :: floor);
						delete coordinates[i][j];
						coordinates[i][j] = 0;
					}
				}
			}
		}
		break;
	}
	case RESTART: {
		state = 4;
		break;
	}
	case SHOOT_UP: {
		knight->shoot('u');
		break;
	}
	case SHOOT_DOWN: {
		knight->shoot('d');
		break;
	}
	case SHOOT_LEFT: {
		knight->shoot('l');
		break;
	}
	case SHOOT_RIGHT: {
		knight->shoot('r');
		break;
	}
	case USE_ITEM_1: {
		Item* pItem = knight->getItem(0);
		knight->useItem(0);
		pRenderer->highlight(y, x, COLOR_PAIR(3), field);

		int x, y;
		pItem->getPosition(y, x);
		coordinatesItems[x][y] = 0;
		delete pItem;
	}
	case USE_ITEM_2: {
		Item* pItem = knight->getItem(1);
		knight->useItem(1);
		pRenderer->highlight(y, x, COLOR_PAIR(3), field);

		int x, y;
		pItem->getPosition(y, x);
		coordinatesItems[x][y] = 0;
		delete pItem;
	}
	case USE_ITEM_3: {
		Item* pItem = knight->getItem(2);
		knight->useItem(2);
		pRenderer->highlight(y, x, COLOR_PAIR(3), field);

		int x, y;
		pItem->getPosition(y, x);
		coordinatesItems[x][y] = 0;
		delete pItem;
	}
	case USE_LAST: {
		Item* pItem = knight->useItem();
		if (!pItem) { break; }
		pRenderer->highlight(y, x, COLOR_PAIR(3), field);

		int x, y;
		pItem->getPosition(y, x);
		coordinatesItems[x][y] = 0;
		delete pItem;

		break;
	}
	}

	return;
}

void GameManager :: clear()
{
	if ((state != 3) || (state != 4)) {
		return;
	}

	Character :: destroyProjectilesContainer();
	GameField* field =  Character :: getGameField();
	Character :: setGameField(0);
	int x = field->x;
	int y = field->y;

	delete field;

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			delete coordinates[i][j];
			delete coordinatesItems[i][j];
		}
		delete coordinates[i];
		delete coordinatesItems[i];
	}
	delete coordinates;
	delete coordinatesItems;

	monsters.clear();

	knight = 0;
	princess = 0;
	pRenderer = 0;
}

int GameManager :: getState()
{
	return state;
}

void GameManager :: playerPickUpItem(Item* item)
{
	knight->pickUpItem(item);
}

void GameManager :: showVictory()
{
}

void GameManager :: showDefeat()
{
}

bool GameManager :: isDefeat()
{
	if (knight->isDead()) {
		state = 3;
		return true;
	}

	return false;
}

bool GameManager :: isVictory()
{
	GameField* field = knight->getGameField();

	if (field->dist(knight, princess) <= 1) {
		state = 3;
		return true;
	}

	return false;
}

#define EPSILON 3

void GameManager :: monstersTurn()
{
	for (auto it = monsters.begin(); it != monsters.end(); it++) {
		if (!(*it)->isDead()) {
			int x1, y1, x2, y2;
			(*it)->getPosition(y1, x1);
			(*it)->makeTurn(knight, pRenderer);
			(*it)->getPosition(y2, x2);
			if ((y1 != y2) || (x1 != x2)) {
				coordinates[x2][y2] = coordinates[x1][y1];
				coordinates[x1][y1] = 0;
			}
		}
		if (Character :: getProjectilesAmount() + EPSILON >= Character :: getProjectilesMaxCount()) {
			Character :: increaseProjectileCapacity();
		}
	}

	Projectile** projectiles = Character :: getProjectileContainer();
	for (unsigned int i = 0; i < Character :: getProjectilesAmount(); i++) {
		if (projectiles[i]->isDead()) continue;
		
		int dx = 0;
		int dy = 0;

		switch (projectiles[i]->getDir()) {
		case 'l': {dy--; break; }
		case 'r': {dy++; break; }
		case 'u': {dx--; break; }
		case 'd': {dx++; break; }
		}

		int x, y;
		projectiles[i]->getPosition(y, x);
		int j;

		for (j = 1; j <= projectiles[i]->getSpeed(); j++) {
			if (coordinates[x + dx * j][y + dy * j]) {
				projectiles[i]->makeTurn(coordinates[x + dx * j][y + dy * j], pRenderer);
				break;
			}
		}
		if (j == projectiles[i]->getSpeed() + 1) {
			projectiles[i]->makeTurn(coordinates[x + dx * j][y + dy * j], pRenderer);
		}
	}

	state = 1;
	return;
}
