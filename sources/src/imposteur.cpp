#include "to_include.hpp"


Color const Imposteur::ImposteurColor = {255, 
									   0,
									   0,
									   255
									   };

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
const Color& Imposteur::getRoleColor()
{
	return ImposteurColor;
}
