#pragma once

#include <Windows.h>
#include "curses.h"

class GameField;

class Renderer
{
public:
	Renderer();
	~Renderer();

	WINDOW* getWindow();

	void createField(GameField* field);
	void damaged(int y, int x, GameField* field);
	void highlight(int y, int x, unsigned long color, GameField* field);
	void step(int y1, int x1, int y2, int x2, unsigned long color2, GameField* field);
private:
	WINDOW* window;
};