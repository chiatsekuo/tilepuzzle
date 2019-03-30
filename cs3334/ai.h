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
	bot(board * current);

	gamestate * choices;


};

