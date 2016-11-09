#include "Healkit.h"
#include "Knight.h"

Healkit::~Healkit()
{
}

void Healkit :: beUsed(Knight* knight)
{
	knight->heal(HP);
}

int Healkit :: getHP()
{
	return HP;
}
