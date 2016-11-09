#include "Application.h"

#include "GameManager.h"
#include "Renderer.h"

Application :: Application()
{
	pRenderer = new Renderer;
	gManager = new GameManager(pRenderer);
}

Application :: ~Application()
{
	delete pRenderer;
	delete gManager;
}

#define END_STATE 3

void Application :: go()
{
	int currState;

	do {
		currState = gManager->getState();

		switch (currState)
		{
		case 0: {
			gManager->loadAndGo();
			break;
		}
		case 1: {
 			int move = wgetch(pRenderer->getWindow());
			gManager->playerMove(move);
			break;
		}
		case 2: {
			gManager->monstersTurn();
			break;
		}
		case END_STATE: {
			gManager->clear();
			break;
		}
		case 4: {
			gManager->clear(); 
			gManager->loadAndGo();
			break;
		}
		default:
			break;
		}

		pRenderer->createField(Character :: getGameField());

		if (currState != END_STATE) {
			gManager->isVictory();
			gManager->isDefeat();
		}

	} while (currState != END_STATE);
}
