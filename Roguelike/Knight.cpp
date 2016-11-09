#include "Item.h"
#include "Knight.h"

Knight :: ~Knight()
{
	for (int i = 0; i < weight; delete inventory[i++]);
	delete inventory;
}

Item* Knight :: getItem(int i)
{
	return inventory[i];
}

void Knight :: pickUpItem(Item* item)
{
	if (weight < inventorySize) {
		inventory[weight++] = item->bePicked(field);
	}
}

void Knight :: useItem(Item* item)
{
	item->beUsed(this);
}

Item* Knight :: useItem(int i)
{
	if (!inventory[i]) return 0;
	Item* pItem = inventory[i];

	useItem(inventory[i]);
	inventory[i] = 0;

	while ((!inventory[weight]) && (weight > 0)) {
		weight--;
	}

	return pItem;
}

Item* Knight :: useItem()
{
	return weight == 0 ? 0 : useItem(weight - 1);
}
