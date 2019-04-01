#pragma once
#include "board.h"

struct gamestate {
	int movex;
	int movey;
	char movedir;
	int inversions;
};

class bot {

public:
	bot(oneBlankGame * current);
	int getchoice();
	gamestate * choices;


};

