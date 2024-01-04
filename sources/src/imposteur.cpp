#include "to_include.hpp"


Color const Imposteur::ImposteurColor = {255, 
									   0,
									   0,
									   255
									   };

Imposteur::Imposteur(): Imposteur(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2, 1) {}

Imposteur::Imposteur(float x, float y, int i = 1) :
	Amogus(x, y, i),
	action(0),
	chasser(false)
{
	int nbAmogus = Game::get_nbAmogus();
}

void Imposteur::findNextDest()
{
	/*int rand;
	float randPos1;
	float randPos2;
	if (action == 1 || action == 2)
	{
		if (destination->in(position, 5))
			action = 0;
	}
	else if (action == 3)
	{
		cooldown_pasBouger--;
		if (cooldown_pasBouger <= 0)
			action = 0;
	}
	if (action == 0)
	{
		rand = Game::rand_int2(0, 100);
		if (rand < 50)  // Prend les coordonnée d'une task aléatoire et s'y dirige
		{ 
			action = 1; 
			rand = Game::rand_int2(0, Game::get_nbPhysicalTask());
			destination = & Game::get_TaskById(rand)->get_position();
		}
		else if (rand < 75)
		{
			action = 2;
			randPos1 = Game::rand_real2(0, Game::SCREEN_WIDTH -(DRAW_RADIUS/2));
			randPos2 = Game::rand_real2(0, Game::SCREEN_HEIGHT-(DRAW_RADIUS/2));
			destination->set_x(randPos1);
			destination->set_y(randPos2);
		}
		else
		{
			action = 3;
			cooldown_pasBouger = Game::rand_int2(400, 1400);
			setDestination(nullptr);
		}
	}*/
	return;
}

bool Imposteur::chase()
{
	int rand;
	int nbre_amogus = 0;
	//Recherche du Amogus le plus proche dans le champ de vision s'il existe
	for(int i = 0; i < Game::get_nbAmogus(); i++)
	{
		if(i != id)
		{
			Vect pos_amogus = Game::get_AmogusById(i)->get_position();
			if((pos_amogus.in(position, distVision))) //Amogus différent de soi-même visible du champ de vision
			{
				nbre_amogus++;
			}
		}
	}
	if (nbre_amogus > 3 || nbre_amogus == 0)
	{
		return false;
	}
	if (nbre_amogus == 1)
	{
		rand = Game::rand_int2(0,100);
		if (rand < 85)
			return true;
		else
			return false;
	}
	else if (nbre_amogus == 2)
	{
		rand = Game::rand_int2(0,100);
		if (rand < 20)
			return true;
		else
			return false;
	}
	else
	{
		rand = Game::rand_int2(0,100);
		if (rand < 5)
			return true;
	}
	return false;
}

const Color& Imposteur::getRoleColor()
{
	return ImposteurColor;
}
