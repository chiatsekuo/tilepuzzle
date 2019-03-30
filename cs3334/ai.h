#pragma once
#include "board.h"

class bot {

public:
	bot(board * current);

	gamestate * choices;


};

struct gamestate {
	int movex;
	int movey;
	char movedir;
	int inversions;
};