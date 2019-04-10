#include "ai.h"





/*
bot::bot(oneBlankGame * current)
{
	root = new gamestate();
	root->parrent = nullptr;
	root->state = new oneBlankGame(current);
	root->choices = root->state->numOfMoves();
	root->expand(depth);


	
}

int bot::findbest()
{
	if (root->state->aimanhattandistance() == 0) {
		return 0;
	}

	int best = 0;
	for (int i = 0; i < root->choices; i++) {
		if (root->children[i]->bestbellowinversion < root->children[best]->bestbellowinversion) {
			best = i;
		}
	}
	for (int i = 0; i < root->choices; i++) {
		if (i != best) {
			root->children[i]->clearbelow();
		}
	}
	gamestate * newhead = root->children[best];
	delete root->children;
	delete root->state;
	root = newhead;
	if (depth > 1) {
		depth--;
	}
	return best;
}

int bot::buildtree()
{
	this->root->calulatebestbellow();
	bool allsame = true;
	while (allsame)
	{
		root->expand(depth);
		root->calulatebestbellow();
		int best = root->children[0]->bestbellowinversion;//find best inversions
		for (int i = 0; i < root->choices; i++) {
			if (root->children[i]->bestbellowinversion < best) {
				best = root->children[i]->bestbellowinversion;
			}
		}
		if (best != 0) {//it must be to improvemnt
			depth++;
			continue;
		}
		else {
			solvedto = best;
			allsame = false;
		}
	}
	return 0;
}

bool bot::done()
{
	if (root->state->inversions() == 0) {
		return true;
	}
	else {
		return false;
	}
}

void bot::print()
{
	root->print(0);
}*/


/*
void gamestate::makechildren()
{
	
	children = new gamestate * [choices];
	for (int i = 0; i < choices; i++) {
		children[i] = new gamestate();
		children[i]->parrent = this;
		children[i]->state = new oneBlankGame(this->state);
		children[i]->state->doMove(i);
		children[i]->choices = children[i]->state->numOfMoves();
	}
	

}

void gamestate::expand(int depth)
{
	if (depth == 0) {
		return;
	}
	if (this->children == nullptr) {
		this->makechildren();
	}
	for (int i = 0; i < choices; i++) {
		children[i]->expand(depth-1);
	}
}

void gamestate::calulatebestbellow()
{

	if (children == nullptr) {
		this->bestbellowinversion = this->state->aiinversion();
		return;
	}
	for (int i = 0; i < this->choices; i++) {
		children[i]->calulatebestbellow();
	}
	bestbellowinversion = this->state->aiinversion();
	for (int i = 0; i < choices; i++) {
		if (bestbellowinversion > children[i]->bestbellowinversion) {
			bestbellowinversion = children[i]->bestbellowinversion;
		}
	}
	
}

void gamestate::print(int indent)
{
	for (int k = 0; k < indent; k++) {
		std::cout << " ";
	}
	std::cout << "min: " << this->bestbellowinversion << std::endl;
	if (children != nullptr) {
		for (int i = 0; i < choices; i++) {
			children[i]->print(indent + 1);
		}
	}

}

void gamestate::clearbelow()
{
	if (children == nullptr) {
		delete this->state;
		return;
	}
	else {
		for (int i = 0; i < choices; i++) {
			children[i]->clearbelow();
			delete children[i];
			
		}
		delete children;
		delete this->state;

	}
}
*/

bot::bot(board * current)
{
	openlist.push_back(makegamestate(current));
	openlist[0].g = 0;
	openlist[0].h = openlist[0].state->aimanhattandistance();
	openlist[0].f = openlist[0].g + openlist[0].h;
}

int bot::makechildren(gamestate * self)
{
	int num = self->state->numOfMoves();
	for (int i = 0; i < num; i++) {
		gamestate add;

		for (int ii = 0; ii < 50; ii++) {
			add.steps[ii] = self->steps[ii];
		}
		add.steps[self->g] = i;
		add.g = self->g + 1;
		add.state = new board(self->state);
		add.state->doMove(i);
		add.h = add.state->aimanhattandistance();
		add.f = add.h + add.g;
		//add.parrent = self;
		openlist.push_back(add);
	}
	return 0;
}

int bot::expand()
{
	int minindex = 0;
	for (int i = 0; i < openlist.size(); i++) {
		if (openlist[i].f < openlist[minindex].f) {
			minindex = i;
		}
	}
	closed.push_back(openlist[minindex]);
	openlist.erase(openlist.begin() + minindex);
	makechildren(&closed[closed.size() - 1]);
	return 0;
}

bool bot::foundanswer()
{
	for (int i = 0; i < closed.size(); i++) {
		if (closed[i].state->aimanhattandistance()<1) {
			return true;
		}
	}
	return false;
}

int bot::loadbest()
{
	for (int i = 0; i < closed.size(); i++) {
		if (closed[i].state->aimanhattandistance() < 1) {
			stepssize = closed[i].g;
			for (int ii = 0; ii < stepssize; ii++) {
				steps[ii] = closed[i].steps[ii];
			}
			break;
		}
	}
	return 0;
}

int bot::findbest()
{
	return steps[index++];
}

void clear(gamestate * s)
{
	delete s->state;
}

gamestate makegamestate(board*game)
{
	gamestate end;
	end.state = game;
	for (int i = 0; i < 50; i++) {
		end.steps[i]=-1;
	}
	return end;
}
