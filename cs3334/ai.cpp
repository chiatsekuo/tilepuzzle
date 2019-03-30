#include "ai.h"

bot::bot(oneBlankGame * current)
{
	root = new gamestate();
	root->parrent = nullptr;
	root->state = new  oneBlankGame(current);
	root->expand(3);
	root->calulatebestbellow();
	root->print(0);

	
}

int bot::findbest()
{
	int best = 0;
	for (int i = 0; i < root->choices; i++) {
		if (root->children[i]->bestbellowinversion < root->children[best]->bestbellowinversion) {
			best = i;
		}
	}
	return best;
}

void bot::print()
{
	root->print(0);
}

void gamestate::makechildren()
{
	choices  = state->numOfMoves();
	children = new gamestate * [choices];
	for (int i = 0; i < choices; i++) {
		children[i] = new gamestate();
		children[i]->parrent = this;
		children[i]->state = new oneBlankGame(this->state);
		children[i]->state->doMove(i);
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
		this->bestbellowinversion = this->state->inversions();
		return;
	}
	for (int i = 0; i < this->choices; i++) {
		children[i]->calulatebestbellow();
	}
	bestbellowinversion = this->state->inversions();
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
	}
	else {
		for (int i = 0; i < choices; i++) {
			children[i]->clearbelow();
			delete children;
		}
		delete this->state;
	}
}
