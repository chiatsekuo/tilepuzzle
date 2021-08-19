#pragma once
#include "board.h"
#include <iostream>
#include <vector>










struct gamestate {
	oneBlankGame*state = nullptr;
	int f, h, g;
	int steps[50] = {};
};
void clear(gamestate * s);
gamestate makegamestate(oneBlankGame*current);
class bot {
public:
	bot(oneBlankGame*current);
	int makechildren(gamestate  * self);
	int sort();
	int deletedups();
	int expand();
	bool foundanswer();
	int loadbest();
	int findbest();
	std::vector<gamestate> openlist;
	std::vector<gamestate> closed;
	gamestate * root;
	int depth = 1;
	int solvedto = -1;
	int stepssize = 0;
	int steps[50] = { 0 };
	int index = 0;
	int ming = 0;
};

struct gamestate2 {
	rowChangeGame*state = nullptr;
	int f, h, g;
	int steps[50] = {};
};
void clear(gamestate2 * s);
gamestate2 makegamestate2(rowChangeGame*current);
class bot2 {
public:
	bot2(rowChangeGame*current);
	int makechildren(gamestate2  * self);
	int expand();
	int sort();
	bool foundanswer();
	int loadbest();
	int findbest();
	std::vector<gamestate2> openlist;
	std::vector<gamestate2> closed;
	gamestate2 * root;
	int depth = 1;
	int solvedto = -1;
	int stepssize = 0;
	int steps[50] = { 0 };
	int index = 0;
	int ming = 0;
	
};