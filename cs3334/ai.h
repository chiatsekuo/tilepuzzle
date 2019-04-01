#pragma once
#include "board.h"
#include <iostream>
#include <vector>






struct gamestate{

	oneBlankGame*state = nullptr;
	int f, h, g;
	int steps[50] = {};
};


void expand(std::vector<gamestate> open, std::vector<gamestate> close);
void calulatebestbellow(gamestate * self);
void print(gamestate * self,int i);
void clearbelow(gamestate * self);


void clear(gamestate * s);

gamestate makegamestate(oneBlankGame*current);
class bot {

public:
	bot(oneBlankGame*current);
	int makechildren(gamestate  * self);
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

};