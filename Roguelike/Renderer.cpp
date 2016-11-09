#include "Renderer.h"

#include "GameField.h"

Renderer :: Renderer()
{
	window = initscr();
	keypad(window, true);
	cbreak();
	noecho();
	curs_set(0);
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_RED, COLOR_YELLOW);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
}

Renderer :: ~Renderer()
{
	endwin();
}

WINDOW * Renderer :: getWindow()
{
	return window;
}

void Renderer :: createField(GameField* field)
{

	for (int i = 0; i < field->x; i++) {
		wmove(window, i, 0);
		for (int j = 0; j < field->y; j++) {
			waddch(window, field->cell(j, i));
		}
	}
	refresh();
}

void Renderer :: damaged(int y, int x, GameField* field)
{
	highlight(y, x, COLOR_PAIR(1), field);
}

void Renderer :: highlight(int y, int x, unsigned long color, GameField * field)
{
	chtype cell = field->cell(y, x);
	cell |= color | A_BLINK;
	mvwaddch(window, x, y, cell);
	refresh();
	Sleep(100);

	cell = field->cell(y, x);
	mvwaddch(window, x, y, cell);
	refresh();
}

void Renderer :: step(int y1, int x1, int y2, int x2, unsigned long color2, GameField* field)
{
	chtype cell1 = field->cell(y1, x1);
	chtype cell2 = field->cell(y2, x2);

	mvwaddch(window, x1, y1, cell1);
	mvwaddch(window, x2, y2, cell2 | color2 | A_BLINK);
	refresh();
}
