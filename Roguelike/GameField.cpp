#include "GameField.h"
#include "Knight.h"
#include "Monster.h"

#include <fstream>
#include <math.h>
#include <windows.h>

GameField :: GameField()
{
	std :: ifstream resMap("map");

	while (resMap) {
		std :: string str;
		std :: getline(resMap, str);

		if (!str.empty()) {
			map.push_back(str);
		}
	}

	x = map.size() - 1;
	y = map[0].size() - 1;
}

GameField :: ~GameField()
{
	map.clear();
}

const std :: string GameField :: operator[](int i)
{
	return map[i];
}

void GameField :: updateCell(int y, int x, char what)
{
	map[x][y] = what;
}

bool GameField :: find(const char what, int& x, int& y, const int x0, int y0)
{
	if (!map.empty()) {
		int rows = map.size();
		for (x = x0; x < rows; x++) {
			int cols = map[x].size();
			for (y = y0; y < cols; y++) {
				if (map[x][y] == what) {
					return true;
				}
			}
			y0 = 0;
		}
	}

	return false;
}

bool GameField :: isCellOpen(int y, int x)
{
	if ((x < 0) || (y < 0) || (x >= (int)map.size()) || (y >= (int)map[x].size())) {
		return false;
	}

	return map[x][y] == Constants :: floor;
}

bool GameField :: isOnFireLine(Character* character, Monster* monster, char& dir)
{
	int y2, x2;
	monster->getPosition(y2, x2);

	return isOnFireLine(character, y2, x2, dir);
}

bool GameField :: isOnFireLine(Character* character, int y2, int x2, char& dir)
{
	int x1, y1;

	character->getPosition(y1, x1);

	if ((y1 != y2) && (x1 != x2)) {
		return false;
	}
	else {
		int max, min, i;

		if (y1 == y2) {
			if (x1 > x2) {
				max = x1, min = x2;
			}
			else {
				max = x2; min = x1;
			}

			for (i = min + 1; i <= max - 1; i++) {
				if (isCellOpen(y1, i)) {
					continue;
				}
				else {
					break;
				}
			}

			if (i == max) {
				dir = y1 > y2 ? 'u' : 'd';
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (y1 > y2) {
				max = y1, min = y2;
			}
			else {
				max = y2; min = y1;
			}

			for (i = min + 1; i <= max - 1; i++) {
				if (isCellOpen(i, x1)) {
					continue;
				}
				else {
					break;
				}
			}

			if (i == max) {
				dir = x1 > x2 ? 'r' : 'l';
				return true;
			}
			else {
				return false;
			}
		}
	}
}

const char GameField :: cell(const int y, const int x)
{
	return map[x][y];
}

double distnc(int x1, int y1, int x2, int y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double GameField :: dist(Character* character1, Character* character2)
{
	int x1, x2, y1, y2;

	character1->getPosition(y1, x1);
	character2->getPosition(y2, x2);

	return distnc(x1, y1, x2, y2);
}

double GameField :: dist(Character* character, int y2, int x2)
{
	int x1, y1;
	character->getPosition(y1, x1);

	return distnc(x1, y1, x2, y2);
}

int GameField :: dx(Character* character, Monster* monster)
{
	int x1, x2, y1, y2;
	character->getPosition(y1, x1);
	monster->getPosition(y2, x2);

	return x1 - x2;
}

int GameField :: dy(Character* character, Monster* monster)
{
	int x1, x2, y1, y2;
	character->getPosition(y1, x1);
	monster->getPosition(y2, x2);

	return y1 - y2;
}

