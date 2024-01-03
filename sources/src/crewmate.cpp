#include "to_include.hpp"

float const Crewmate::DEFAULT_avoid = 0.7;
Color const Crewmate::CrewmateColor = {0, 
									   178,
									   255,
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
	int rand;
	float randPos1, randPos2;
	if (occupe)
		return;
	if (action == 1)
	{
		fuir();
		//deplacement
		if (destination->in(position, distVision)) //Lorsqu'on arrive à destination, on repasse à l'état neutre
			action = 0;
		return;
	}
	else if (action == 2)
	{
		fuir();
		//deplacement
		if (destination->in(position, distVision)) //Lorsqu'on arrive à destination, on repasse à l'état neutre
			action = 0;
	}
	else if (action == 3)
	{
		fuir();
		cooldown_pasBouger--;
		if (cooldown_pasBouger <= 0) //Lorsque le temps de l'état immobile est écoulé
			action = 0;
	}
	else if (action == 4)
	{
		//deplacement
		if (destination->in(position, distVision)) //Lorsqu'on arrive à destination, on repasse à l'état neutre
			action = 0;
	}
	else if (action == 0)
	{	
		rand = Game::rand_int2(0, 100);
		if (rand < 65 && nbTaskCleared < Game::get_nbTaskPerCrewmate()) 
		{ 
			action = 1; 
			follow_dest = true;
			/*Recherche de la task la plus proche*/
			int ind_pp_task = PlusProcheTask();
			if(ind_pp_task != -1) //Si on a une task en vue
			{
				setDestination(&(Game::get_TaskById(ind_next_task)->get_position()));
			}
			else //Sinon, on se déplace aléatoirement
			{
				action = 2;
				randPos1 = Game::rand_real2(DRAW_RADIUS/2, Game::SCREEN_WIDTH -(DRAW_RADIUS/2));
				randPos2 = Game::rand_real2(DRAW_RADIUS/2, Game::SCREEN_HEIGHT-(DRAW_RADIUS/2));
				Vect dest_fuite;
				dest_fuite.set_x(randPos1);
				dest_fuite.set_y(randPos2);
				float distance = dest_fuite.dist(position);
				dest_fuite -= position;
				moveToward(dest_fuite.angle(), distance);
			}		
		}
		else if (rand < 85) //Déplacement aléatoire
		{
			action = 2;
			randPos1 = Game::rand_real2(DRAW_RADIUS/2, Game::SCREEN_WIDTH -(DRAW_RADIUS/2));
			randPos2 = Game::rand_real2(DRAW_RADIUS/2, Game::SCREEN_HEIGHT-(DRAW_RADIUS/2));
			Vect dest_fuite;
			dest_fuite.set_x(randPos1);
			dest_fuite.set_y(randPos2);
			float distance = dest_fuite.dist(position);
			dest_fuite -= position;
			moveToward(dest_fuite.angle(), distance);
		}
		else //On ne bouge plus
		{
			action = 3;
			cooldown_pasBouger = Game::rand_int2(400, 1400);
			setDestination(nullptr);
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
		Vect dest_fuite;
		dest_fuite.set_x(randX);
		dest_fuite.set_y(randY);
		float distance = dest_fuite.dist(position);
		dest_fuite -= position;
		moveToward(dest_fuite.angle(), distance);
		action = 4;
	}
}

/*void Crewmate::deplacer(float offset, Vect pos_task)
{
	if((pos_task.get_x() > position.get_x()) && ((position.get_x()+offset) <= Game::SCREEN_WIDTH -(DRAW_RADIUS/2)))
	{
		position.set_x(position.get_x()+offset);
	}
	else if((pos_task.get_x() < position.get_x()) && ((position.get_x()-offset) >= (DRAW_RADIUS/2)))
	{
		position.set_x(position.get_x()-offset);
	}
	if((pos_task.get_y() > position.get_y())&& ((position.get_y()+offset) <= Game::SCREEN_HEIGHT-(DRAW_RADIUS/2)))
	{
		position.set_y(position.get_y()+offset); 
	}
	else if((pos_task.get_y() < position.get_y()) && ((position.get_y()-offset) >= (DRAW_RADIUS/2)))
	{
		position.set_y(position.get_y()-offset);
	}
}*/

vector<Task*> Crewmate::getTask()
{
	return lstTasks;
}

void Crewmate::setTask(const vector<Task*>& listeTask)
{
	lstTasks = listeTask;
}

/*void Crewmate::roam() -> il pourrait avoir en argument is_sherif pour distinguer des comportements différents ainsi que l'offset

	TODO

	Méthode qui va définir une destination choisi de manière aléatoire avec l'idée suivante (vous pourrez proposer une bien meilleure idée):
	
	L'écran est divisé en 4 zones (haut-gauche, haut-droit, bas-gauche et bas-droit), on garde en mémoire la zone courante de l'Amogus dans un attribut (initialiser dans le constructeur en fct de ses coordonnées).
	On choisit aléatoirement une zone différente de la zone courante et on génère un point de sorte à ce que ce point soit plus proche de la zone choisi que la position actuelle de l'Amogus.
	Cette méthode donne un risque d'aller-retour mais la manière de se déplacer reste semi-aléatoire avec des chances de ressemblance à une "exploration" (l'Amogus pourra tout de même réaliser des tours en faisant des zigzags ou non)
	Quand l'Amongus atteint la zone, on change la zone en mémoire.
	On pourrait vérifier ici (ou ailleurs) qu'après d'avoir effectuer le pas, on regarde si l'Amogus a toujours sa tâche en vue (si il en a une) ou non.

*/


const Color& Crewmate::getRoleColor()
{
	return CrewmateColor;
}