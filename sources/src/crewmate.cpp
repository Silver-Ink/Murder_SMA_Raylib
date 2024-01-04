#include "to_include.hpp"

float const Crewmate::DEFAULT_avoid = 0.7;
Color const Crewmate::CrewmateColor = {0, 
									   178,
									   255,
									   255
									   };
Color const Crewmate::SherifColor =   {0, 
									   217,
									   120,
									   255
									   };

/// @brief a utiliser pour créer un crewmate sans task et sans infos
/// et en dehors du jeu
Crewmate::Crewmate() : Amogus(100, 100, 0) {}

/// @brief Nécessite d'avoir initilisé game avant
/// @param is_sherif si vrai, n'as pas de taches et a une arme dès le départ
Crewmate::Crewmate(float x, float y, bool is_sherif) :
	Amogus(x, y, 0),
	armed(is_sherif),
	nbTaskCleared(0),
	occupe(false),
	action(0),
	cooldown_pasBouger(0)
	//ind_next_task(-1)
{
	// initialisation des info
	int nbAmogus = Game::get_nbAmogus();
	lstInfo.resize(nbAmogus);
	lstInfo[id].sus = 0; // suspition envers soit-meme a zéro
	taskDone = new bool[Game::get_nbPhysicalTask()];
	for(int i = 0; i < Game::get_nbPhysicalTask(); i++) taskDone[i] = false;
}

Crewmate::~Crewmate()
{
	lstTasks.clear(); // Les taches seront free par la classe game
	lstInfo.clear(); // pas des pointeurs donc pas besoin de free
}

int Crewmate::is_armed() {return armed;}

int Crewmate::get_nbTaskCleared() {return nbTaskCleared;}

//Renvoie -1 si aucune task n'a été trouvé.
int Crewmate::PlusProcheTask()
{
	float min = 999999999.;
	int ind_task = -1;
	for(Task * curr : lstTasks)
	{
		//On vérifie que la task ne soit pas déjà réalisée
		if(!taskDone[curr->get_taskId()])
		{
			//On vérifie qu'il soit dans le champ de vision du crewmate et de distance minimale
			Vect pos_t = curr->get_position();
			if((pos_t.in(position, distVision)) && (pos_t.dist(position) < min))
			{
				min = pos_t.dist(position);
				ind_task = curr->get_taskId();
			}	
		}
	}
	return ind_task;
}

/// @brief Déplace le crewmate en fonction du contexte
/// @param offset Distance parcouru en une unité de temps
void Crewmate::findNextDest()
{
	printf("ACTION : %d\n", action);
	int rand;
	float randPos1, randPos2;
	if (occupe)
		return;
	if (action == 1)
	{
		printf("IF ACTION==1\n");
		fuir();
		printf("IF ACTION==1 APRES FUIR\n");
		if(!destination) printf("BOZO HAHAHAHAHAAH\n");
		if (destination->in(position, distInterract)) //Lorsqu'on arrive à destination, on repasse à l'état neutre
			action = 0;
		return;
	}
	else if (action == 2)
	{
		fuir();
		if(!destination) printf("BOZO HAHAHAHAHAAH\n");
		if (destination->in(position, distInterract)) //Lorsqu'on arrive à destination, on repasse à l'état neutre
			action = 0;
	}
	else if (action == 3)
	{
		fuir();
		if(!destination) printf("BOZO HAHAHAHAHAAH\n");
		printf("IF ACTION==3 APRES FUIR\n");
		cooldown_pasBouger--;
		if (cooldown_pasBouger <= 0) //Lorsque le temps de l'état immobile est écoulé
			action = 0;
	}
	else if (action == 4)
	{
		if(!destination) printf("BOZO HAHAHAHAHAAH\n");
		if (destination->in(position, distInterract)) //Lorsqu'on arrive à destination, on repasse à l'état neutre
			action = 0;
	}
	else //action == 0
	{	
		printf("ELSE ACTION 0\n");
		rand = Game::rand_int2(0, 100);
		if (rand < 65 && nbTaskCleared < Game::get_nbTaskPerCrewmate()) 
		{ 
			printf("RAND ACTION 1\n");
			action = 1; 
			follow_dest = true; 
			/*Recherche de la task la plus proche*/
			int ind_pp_task = PlusProcheTask();
			if(ind_pp_task != -1) //Si on a une task en vue
			{
				setDestination(Game::get_TaskById(ind_pp_task)->get_adr_position());
				follow_dest = true;
			}
			else //Sinon, on se déplace aléatoirement
			{
				printf("RAND ACTION 1 ALEATOIRE 2\n");
				action = 2;
				randPos1 = Game::rand_real2(DRAW_RADIUS/2, Game::SCREEN_WIDTH -(DRAW_RADIUS/2));
				randPos2 = Game::rand_real2(DRAW_RADIUS/2, Game::SCREEN_HEIGHT-(DRAW_RADIUS/2));

				dest_prioritaire.set_x(randPos1);
				dest_prioritaire.set_y(randPos2);
				setDestination(&dest_prioritaire);
				follow_dest = true;
				//Vect prio(randPos1, randPos2, true);
				//moveToward(prio);

			}		
		}
		else if (rand < 85) //Déplacement aléatoire
		{
			printf("RAND ACTION 2\n");
			action = 2;
			randPos1 = Game::rand_real2(DRAW_RADIUS/2, Game::SCREEN_WIDTH -(DRAW_RADIUS/2));
			randPos2 = Game::rand_real2(DRAW_RADIUS/2, Game::SCREEN_HEIGHT-(DRAW_RADIUS/2));
			
			dest_prioritaire.set_x(randPos1);
			dest_prioritaire.set_y(randPos2);
			setDestination(&dest_prioritaire);
			follow_dest = true;
			
			//Vect prio(randPos1, randPos2, false);
			//moveToward(prio);

		}
		else //On ne bouge plus
		{
			printf("RAND ACTION 3\n");
			action = 3;
			cooldown_pasBouger = Game::rand_int2(400, 1400);
			setDestination(nullptr);
			follow_dest = true;
		}
	} 
}


void Crewmate::fuir()
{
	/*Ici, on parcourt les Amogus pour trouver celui le plus proche et réagir si celui-ci est trop suspect
	-> cas a modifier si on souhaite qq chose de plus complexe*/
	int ind_sus = -1;
	float min_dist = 999999999.;
	//Recherche du Amogus le plus proche dans le champ de vision s'il existe
	for(int i = 0; i < Game::get_nbAmogus(); i++)
	{
		if(i != id)
		{
			Vect pos_amogus = Game::get_AmogusById(i)->get_position();
			if((pos_amogus.in(position, distVision)) && (pos_amogus.dist(position) < min_dist)) //Amogus différent de soi-même visible du champ de vision
			{
				min_dist = pos_amogus.dist(position);
				ind_sus = i;
			}
		}
	}

	//On vérifie si un quelconque Amogus est visible ou non
	if((ind_sus != -1) && lstInfo[ind_sus].sus >= DEFAULT_avoid) 
	{
		printf("IF DE FUIR!\n");
		Vect pos_amogus = Game::get_AmogusById(ind_sus)->get_position();
		float randX, randY;
		if((pos_amogus.get_x() > position.get_x())) {
			randX = Game::rand_real2((DRAW_RADIUS/2), position.get_x());
		} else {
			randX = Game::rand_real2(position.get_x(), Game::SCREEN_WIDTH-(DRAW_RADIUS/2));
		}
		if((pos_amogus.get_y() > position.get_y())) {
			randY = Game::rand_real2((DRAW_RADIUS/2), position.get_y());
		} else {
			randY = Game::rand_real2(position.get_y(), Game::SCREEN_HEIGHT-(DRAW_RADIUS/2));
		}
		/*
		Vect dest_fuite;
		printf("CRASH ??????\n");
		dest_fuite.set_x(randX);
		dest_fuite.set_y(randY);
		float distance = dest_fuite.dist(position);
		dest_fuite -= position;
		moveToward(dest_fuite.angle(), distance); */
		dest_prioritaire.set_x(randX);
		dest_prioritaire.set_y(randY);
		setDestination(&dest_prioritaire);
		follow_dest = true;
		action = 4;
	}

}


vector<Task*> Crewmate::getTask()
{
	return lstTasks;
}

void Crewmate::setTask(const vector<Task*>& listeTask)
{
	lstTasks = listeTask;
}

const Color& Crewmate::getRoleColor()
{
	return armed ? SherifColor : CrewmateColor ;
}