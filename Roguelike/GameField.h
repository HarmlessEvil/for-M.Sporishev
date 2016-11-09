#pragma once

#include <string>
#include <vector>

class Character;
class Knight;
class Monster;

class GameField
{
public:
	GameField();
	~GameField();

	const std :: string operator[](const int i);

	void updateCell(int y, int x, char what);
	bool find(const char what, int& x, int& y, const int x0 = 0, const int y0 = 0);
	bool isCellOpen(int y, int x);
	bool isOnFireLine(Character* character, Monster* monster, char& dir);
	bool isOnFireLine(Character* character, int y2, int x2, char& dir);
	const char cell(const int y, const int x);
	double dist(Character* character1, Character* character2);
	double dist(Character* character, int y2, int x2);
	int dx(Character* character, Monster* monster);
	int dy(Character* character, Monster* monster);

	int x, y;
private:
	std :: vector<std :: string> map;
};