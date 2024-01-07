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
	chasser(false),
	cooldown_pasBouger(0),
	cooldown_kill(0)
{
	int nbAmogus = Game::get_nbAmogus();
}

void Imposteur::findNextDest()
{
	int rand;
	float randPos1, randPos2;

	if (!alive)
	{
		setDestination(nullptr);
		return;
	}

	if (cooldown_kill > 0)
	{
		cooldown_kill--;
	}

	if (action == 1 || action == 2)
	{
		if (cooldown_kill <= 0)
		{
			chase();
		}

		if (destination->in(position, 5))
		{
			//printf("Destination atteinte!\n");
			action = 0;
		}
	}
	else if (action == 3)
	{
		if (cooldown_kill <= 0)
		{
			chase();
		}
		cooldown_pasBouger--;
		if (cooldown_pasBouger <= 0)
		{
			//printf("Je bouge DE NOUVEAU!\n");
			action = 0;
		}
	}
	else if (action == 4)
	{
		if (destination->in(position, 10))
		{
			printf("------------------------\nTUER\n--------------------------\n");
			cooldown_kill = 4000;
			Game::get_AmogusById(id_victime)->die();
			if (Game::get_AmogusById(id_victime)->get_type() == 0)
				Game::killCrewmate();
			else
				Game::killImposteur();
			action = 0;
		}
	}
	if (action == 0)
	{
		rand = Game::rand_int2(0, 100);
		if (rand < 50)  // Prend les coordonnée d'une task aléatoire et s'y dirige
		{ 
			//printf("Je vais chercher une task!\n");
			action = 1; 
			rand = Game::rand_int2(0, Game::get_nbPhysicalTask());
			setDestination(Game::get_TaskById(rand)->get_adr_position());
		}
		else if (rand < 75) // se déplace aléatoirement
		{
			//printf("Je me déplace aléatoirement\n");
			action = 2;
			randPos1 = Game::rand_real2(DRAW_RADIUS, Game::SCREEN_WIDTH -(DRAW_RADIUS));
			randPos2 = Game::rand_real2(DRAW_RADIUS, Game::SCREEN_HEIGHT-(DRAW_RADIUS));
			
			dest_prioritaire.set_x(randPos1);
			dest_prioritaire.set_y(randPos2);
			setDestination(&dest_prioritaire);
			follow_dest = true;
			
		}
		else // ne bouge pas
		{
			//printf("Je ne bouge pas\n");
			action = 3;
			cooldown_pasBouger = Game::rand_int2(400, 1400);
			setDestination(nullptr);
			follow_dest = true;
		}
	}
	return;
}

void Imposteur::chase()
{
	int rand;
	int nbre_amogus = 0;
	//Recherche du Amogus le plus proche dans le champ de vision s'il existe
	for(int i = 0; i < Game::get_nbAmogus(); i++)
	{
		if(i != id)
		{
			Vect pos_amogus = Game::get_AmogusById(i)->get_position();
			if((pos_amogus.in(position, distVision)) && Game::get_AmogusById(i)->isAlive()) //Amogus différent de soi-même visible du champ de vision et vivant
			{
				id_victime = i;
				nbre_amogus++;
			}
		}
	}
	if (nbre_amogus > 3 || nbre_amogus == 0)
	{
		return;
	}
	else if (nbre_amogus == 1)
	{
		rand = Game::rand_int2(0,100);
		if (rand < 85)
		{
			setDestination(&Game::get_AmogusById(id_victime)->get_position());
			action = 4;
		}
		else
		{
			cooldown_kill = 400;
		}
	}
	else if (nbre_amogus == 2)
	{
		rand = Game::rand_int2(0,100);
		if (rand < 20)
		{
			setDestination(&Game::get_AmogusById(id_victime)->get_position());
			action = 4;
		}
		else
		{
			cooldown_kill = 400;
		}
	}
	else
	{
		rand = Game::rand_int2(0,100);
		if (rand < 5)
		{
			setDestination(&Game::get_AmogusById(id_victime)->get_position());
			action = 4;
		}
		else
		{
			cooldown_kill = 400;
		}
	}
}

void Imposteur::kill()
{
	setDestination(&Game::get_AmogusById(id_victime)->get_position());
	action = 4;
}

const Color& Imposteur::getRoleColor()
{
	return ImposteurColor;
}
