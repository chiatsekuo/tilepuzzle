#pragma once
#include "board.h"
#include <iostream>



class gamestate {

public:
	gamestate * parrent = nullptr;
	oneBlankGame*state = nullptr;
	int bestbellowinversion=0;
	int choices;
	gamestate ** children = nullptr;
	void makechildren();
	void expand(int depth);
	void calulatebestbellow();
	void print(int i);
	void clearbelow();
};


class bot {

public:
	bot(oneBlankGame*current);
	int findbest();
	void print();
	gamestate * root;
	

};