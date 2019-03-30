#pragma once
#include "board.h"

struct gamestate {
	int moveChoice;
	int inversions;
};

class bot {

public:
	bot(oneBlankGame * current);
	int getChoice();
	gamestate * choices;
	int choicesize;


};

