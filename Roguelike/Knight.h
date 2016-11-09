#pragma once
#include "Character.h"

class Item;

class Knight : public Character
{
public:
	Knight(int _y, int _x, int _attack = Constants :: knightAttack, int _HP = Constants :: knightHP, char _pic = Constants :: knightIcon, int _inventorySize = Constants :: InventorySize) : Character(_y, _x, _attack, _HP, _pic), weight(0), inventorySize(_inventorySize) {
		inventory = new Item*[_inventorySize];

		for (int i = 0; i < _inventorySize; i++) {
			inventory[i] = 0;
		}
	};
	~Knight();

	Item* getItem(int i);
	void pickUpItem(Item* item);
	void useItem(Item* item);
	Item* useItem(int i);
	Item* useItem();
private:
	Item** inventory;

	int inventorySize;
	int weight;
};

