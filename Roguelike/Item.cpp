#include "Item.h"

#include "GameField.h"

Item :: ~Item()
{
}

Item* Item :: bePicked(GameField* field)
{
	picked = true;
	field->updateCell(y, x, Constants :: floor);
	return this;
}

bool Item :: isPicked()
{
	return picked;
}


