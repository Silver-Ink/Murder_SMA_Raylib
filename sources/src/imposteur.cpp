#include "to_include.hpp"


Imposteur::Imposteur(): Amogus(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2, 1) {}

Imposteur::Imposteur(float x, float y, int i = 1) :
	Amogus(x, y, i)
{
	int nbAmogus = Game::get_nbAmogus();
}

void Imposteur::findNextDest(float offset)
{
	// a redéfinir
}

