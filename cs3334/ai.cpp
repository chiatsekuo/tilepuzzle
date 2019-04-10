#include "ai.h"

bot::bot(oneBlankGame * current)
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
		add.state = new oneBlankGame(self->state);
		add.state->doMove(i);
		add.h = add.state->aimanhattandistance();
		add.f = add.h + add.g;
		//add.parrent = self;
		openlist.push_back(add);
	}
	return 0;
}

int bot::sort()
{
	for (int i = 0; i < openlist.size(); i++) {
		for (int ii = i; ii > 0; ii--) {
			if (openlist[ii].f > openlist[ii-1].f) {
				gamestate temp = openlist[ii];
				openlist[ii] = openlist[ii - 1];
				openlist[ii - 1] = temp;
			}

		}
	}
	return 0;
}

int bot::deletedups()
{
	return 0;
}

int bot::expand()
{
	int minindex = -1;
	for (int i = openlist.size()-1; i > -1; i--) {
		if (openlist[i].f <=ming) {
			minindex = i;
			ming = openlist[i].f;
			break;
		}
	}
	if (minindex != -1) {
		for (int i = 0; i < closed.size(); i++) {
			if (openlist[minindex].state->issame(closed[i].state)) {
				openlist.erase(openlist.begin() + minindex);
				return 0;
			}
		}
		ming--;
		closed.push_back(openlist[minindex]);
		openlist.erase(openlist.begin() + minindex);
		makechildren(&closed[closed.size() - 1]);
	}
	else {
		ming++;
	}
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

gamestate makegamestate(oneBlankGame*game)
{
	gamestate end;
	end.state = game;
	for (int i = 0; i < 50; i++) {
		end.steps[i]=-1;
	}
	return end;
}
//---------------------------------------------

bot2::bot2(rowChangeGame * current)
{
	openlist.push_back(makegamestate2(current));
	openlist[0].g = 0;
	openlist[0].h = openlist[0].state->aimanhattandistance();
	openlist[0].f = openlist[0].g + openlist[0].h;
}

int bot2::makechildren(gamestate2 * self)
{
	int num = self->state->numOfMoves();
	for (int i = 0; i < num; i++) {
		gamestate2 add;

		for (int ii = 0; ii < 50; ii++) {
			add.steps[ii] = self->steps[ii];
		}
		add.steps[self->g] = i;
		add.g = self->g + 1;
		add.state = new rowChangeGame(self->state);
		add.state->doMove(i);
		add.h = add.state->aimanhattandistance();
		add.f = add.h + add.g;
		//add.parrent = self;
		openlist.push_back(add);
	}
	return 0;
}

int bot2::expand()
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

bool bot2::foundanswer()
{
	for (int i = 0; i < closed.size(); i++) {
		if (closed[i].state->aimanhattandistance() < 1) {
			return true;
		}
	}
	return false;
}

int bot2::loadbest()
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

int bot2::findbest()
{
	return steps[index++];
}

void clear(gamestate2 * s)
{
	delete s->state;
}

gamestate2 makegamestate2(rowChangeGame*game)
{
	gamestate2 end;
	end.state = game;
	for (int i = 0; i < 50; i++) {
		end.steps[i] = -1;
	}
	return end;
}
