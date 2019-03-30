#include "ai.h"

bot::bot(oneBlankGame * current)
{

	oneBlankGame copy = oneBlankGame(current);

	choices = new gamestate[choicesize];

	for (int i = 0; i < choicesize; i++) {
		oneBlankGame testmove(&copy);
		testmove.doMove(i);
		choices[i].moveChoice = i;
		choices[i].inversions = testmove.inversions();
	}

}

int bot::getChoice()
{
	int bestindex = 0;
	for (int i = 0; i < choicesize; i++) {
		if (choices[bestindex].inversions > choices[i].inversions) {
			bestindex = i;
		}
	}
	return choices[bestindex].moveChoice;
}

int minchoice(oneBlankGame * current)
{

	return 0;
}
