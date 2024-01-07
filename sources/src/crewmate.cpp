#include "to_include.hpp"

float const Crewmate::DEFAULT_avoid = 0.7;
Color const Crewmate::CrewmateColor = {0, 178, 255, 255};
Color const Crewmate::SherifColor   = {0, 217, 120, 255};

/// @brief a utiliser pour créer un crewmate sans task et sans infos
/// et en dehors du jeu
Crewmate::Crewmate() : Amogus(100, 100, 0) {}

/// @brief Nécessite d'avoir initilisé game avant
/// @param is_sherif si vrai, n'as pas de taches et a une arme dès le départ
Crewmate::Crewmate(float x, float y, bool is_sherif) :
	Amogus(x, y, 0),
	armed(is_sherif),
	nbTaskCleared(0),
	occupe(0),
	action(0),
	cooldown_pasBouger(0),
	ind_pp_task(-1),
	cooldown_kill(0)
{
	// initialisation des info
	int nbAmogus = Game::get_nbAmogus();
	lstInfo.resize(nbAmogus);
	for (int i = 0; i < Game::get_nbAmogus(); i++)
	{
		if (i == id)
			lstInfo.at(i).sus = 0.0; // suspition envers soit-meme a zéro
		else
			lstInfo.at(i).sus = (float) Game::get_nbImpostorAlive() / (float) (Game::get_nbAmogus() - 1);	
	}
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
	for (int i = 0; i < Game::get_nbTaskPerCrewmate(); i++)
    {
		if(!taskDone[lstTasks.at(i)->get_taskId()])
		{
			Vect pos_t = *(lstTasks.at(i)->get_adr_position());
			if((pos_t.in(position, distVision)) && (pos_t.dist(position) < min))
			{
				min = pos_t.dist(position);
				ind_task = lstTasks.at(i)->get_taskId();
			}	
		}
	}
	// for(Task * curr : lstTasks)
	// {
	// 	//On vérifie que la task ne soit pas déjà réalisée
	// 	if(!taskDone[curr->get_taskId()])
	// 	{
	// 		//On vérifie qu'il soit dans le champ de vision du crewmate et de distance minimale
	// 		Vect pos_t = curr->get_position();
	// 		if((pos_t.in(position, distVision)) && (pos_t.dist(position) < min))
	// 		{
	// 			min = pos_t.dist(position);
	// 			ind_task = curr->get_taskId();
	// 		}	
	// 	}
	// }
	return ind_task;
}

/// @brief Déplace le crewmate en fonction du contexte
/// @param offset Distance parcouru en une unité de temps
void Crewmate::findNextDest()
{
	//printf("ACTION : %d\n", action);
	int rand;
	float randPos1, randPos2;
	if (!alive)
	{
		setDestination(nullptr);
		return;
	}
	if (occupe > 0)
	{
		occupe--;
		return;
	}
	if (cooldown_kill > 0)
	{
		cooldown_kill--;
	}
	updateInfo();
	if (action == 1)
	{
		if (!armed || (armed && cooldown_kill <= 0))
			fuirOrChase();
		if (destination->in(position, distInterract)) //Lorsqu'on arrive à destination, on repasse à l'état neutre
		{
			taskDone[ind_pp_task] = true;
			nbTaskCleared++;
			action = 0;
			//printf("Destination atteinte! Fin tâche: %d, idTask: %d\n", nbTaskCleared, ind_pp_task);
			occupe = 200 * Game::get_TaskById(ind_pp_task)->get_duree();
			//printf("Duree: %d\n", occupe);
		}
		return;
	}
	else if (action == 2)
	{
		if (!armed || (armed && cooldown_kill <= 0))
			fuirOrChase();
		if (destination->in(position, distInterract)) //Lorsqu'on arrive à destination, on repasse à l'état neutre
		{
			//printf("Destination atteinte!\n");
			action = 0;
		}
	}
	else if (action == 3)
	{
		if (!armed || (armed && cooldown_kill <= 0))
			fuirOrChase();
		cooldown_pasBouger--;
		if (cooldown_pasBouger <= 0)
		{
			//printf("JE BOUGE DE NOUVEAU!\n");
			action = 0;
		} //Lorsque le temps de l'état immobile est écoulé
	}
	else if (action == 4)
	{
		if (destination->in(position, distInterract)) //Lorsqu'on arrive à destination, on repasse à l'état neutre
		{
			action = 0;
		}	
	}
	else if (action == 5)
	{
		if (destination->in(position, distInterract)) //Lorsqu'on arrive à destination, on repasse à l'état neutre
		{
			printf("-------------------\nTUER IMPOSTEUR\n----------------------\n");
			printf("Cet Amogus avait %lf chance d'être un tueur\n", lstInfo.at(id_victime).sus);
			Game::get_AmogusById(id_victime)->die();
			if (Game::get_AmogusById(id_victime)->get_type() == 0)
				Game::killCrewmate();
			else
				Game::killImposteur();
			cooldown_kill = 4000;
			action = 0;
		}	
	}
	else //action == 0
	{	
		rand = Game::rand_int2(0, 100);
		if (nbTaskCleared >= Game::get_nbTaskPerCrewmate() && is_armed() == false)
		{
			armed = true;
			printf("FIN DE TACHE! :D \n");
		}
			
		if (rand < 65 && nbTaskCleared < Game::get_nbTaskPerCrewmate() && !is_armed()) 
		{ 	 
			follow_dest = true; 
			/*Recherche de la task la plus proche*/
			ind_pp_task = PlusProcheTask();
			if(ind_pp_task != -1) //Si on a une task en vue
			{
				action = 1;
				//printf("Task trouvé, je me déplace vers elle!\n");
				setDestination(Game::get_TaskById(ind_pp_task)->get_adr_position());
				follow_dest = true;
			}
			else //Sinon, on se déplace aléatoirement
			{
				//printf("Je vois pas de task donc je me déplace aléatoirement\n");
				action = 2;
				randPos1 = Game::rand_real2(DRAW_RADIUS, Game::SCREEN_WIDTH -(DRAW_RADIUS));
				randPos2 = Game::rand_real2(DRAW_RADIUS, Game::SCREEN_HEIGHT-(DRAW_RADIUS));

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
			//printf("Je me deplace aléatoirement\n");
			action = 2;
			randPos1 = Game::rand_real2(DRAW_RADIUS, Game::SCREEN_WIDTH -(DRAW_RADIUS));
			randPos2 = Game::rand_real2(DRAW_RADIUS, Game::SCREEN_HEIGHT-(DRAW_RADIUS));
			
			dest_prioritaire.set_x(randPos1);
			dest_prioritaire.set_y(randPos2);
			setDestination(&dest_prioritaire);
			follow_dest = true;
			
			//Vect prio(randPos1, randPos2, false);
			//moveToward(prio);

		}
		else //On ne bouge plus
		{
			action = 3;
			cooldown_pasBouger = Game::rand_int2(400, 1400);
			//printf("Je ne bouge plus pendant %d sec\n", cooldown_pasBouger / 200);
			setDestination(nullptr);
			follow_dest = true;
		}
	} 
}

void Crewmate::fuirOrChase()
{
	for (int i = 0; i < Game::get_nbAmogus(); i++)
    {
		if(i != id)
		{
			Vect pos_amogus = Game::get_AmogusById(i)->get_position();
			if(pos_amogus.in(position, distVision) && Game::get_AmogusById(i)->isAlive() && lstInfo.at(i).sus > DEFAULT_avoid)
			{
				id_victime = i;
				if (armed)
				{
					setDestination(&Game::get_AmogusById(id_victime)->get_position());
					action = 5;
					return;
				}
				else
				{
					Vect pos_amogus = Game::get_AmogusById(i)->get_position();
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
					dest_prioritaire.set_x(randX);
					dest_prioritaire.set_y(randY);
					setDestination(&dest_prioritaire);
					follow_dest = true;
					action = 4;
					printf(" FUIR!\n");
					return;
				}
			}
		}
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

float Crewmate::getSusById(int nbr)
{
	return lstInfo.at(nbr).sus;
}

const Color& Crewmate::getRoleColor()
{
	return armed ? SherifColor : CrewmateColor ;
}

void Crewmate::updateInfo()
{
    for (int i = 0; i < Game::get_nbAmogus(); i++)
    {
		if(i != id)
		{
			Vect pos_amogus = Game::get_AmogusById(i)->get_position();
			if(pos_amogus.in(position, distVision) && !Game::get_AmogusById(i)->isAlive() && lstInfo.at(i).alive)
			{
				lstInfo.at(i).sus = 0.0;
				lstInfo.at(i).alive = false;
				for (int j = 0; j < Game::get_nbAmogus(); j++)
    			{
					if(j != id)
					{
						Vect pos_amogus2 = Game::get_AmogusById(j)->get_position();
						if(pos_amogus2.in(position, distVision) && Game::get_AmogusById(j)->isAlive())
						{
							lstInfo.at(j).sus += 0.1;
							if (armed && Game::get_AmogusById(j)->get_type() == 1)
								printf("Je vois un imposteur avec %lf %% d'être imposteur\n",lstInfo.at(j).sus );
						}
						else if (!pos_amogus2.in(position, distVision) && Game::get_AmogusById(j)->isAlive())
						{
							float min = (float) Game::get_nbImpostorAlive() / (float) (Game::get_nbCrewmateAlive() + Game::get_nbImpostorAlive() - 1);
							if (lstInfo.at(j).sus < min)
							{
								printf("Mise à jour des autres à %lf %% d'être imposteur\n", min);
								//TODO: parcourir plutôt les infos pour compter le nombre de personne encore en vie que le sherif a en tête et non pas la variable static
								lstInfo.at(j).sus = min;
							}
						}
					}
				}
			}
		}
    }
}