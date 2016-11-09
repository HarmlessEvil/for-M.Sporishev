#pragma once

#include "Constants.h"
#include "Character.h"
#include "Renderer.h"
#include <vector>

class Character;
class Knight;
class Princess;
class Monster;

class Item;

class Renderer;

class GameManager
{
public:
	GameManager(Renderer* renderer) : pRenderer(renderer), state(0) { Constants a; };
	~GameManager();

	void loadAndGo();
	void monstersTurn();
	void playerMove(int move);
	void playerPickUpItem(Item* item);
	void showVictory();
	void showDefeat();
	bool isDefeat();
	bool isVictory();

	void clear();
	int getState();
private:
	std :: vector<Monster*> monsters;

	Character*** coordinates;
	Item*** coordinatesItems;

	Knight* knight;
	Princess* princess;
	Renderer* pRenderer;

	int state;
};

