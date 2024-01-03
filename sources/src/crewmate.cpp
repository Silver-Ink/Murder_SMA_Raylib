#include "to_include.hpp"

float const Crewmate::DEFAULT_avoid = 0.7;

/// @brief a utiliser pour créer un crewmate sans task et sans infos
/// et en dehors du jeu
Crewmate::Crewmate() : Amogus(100, 100) {}

/// @brief Nécessite d'avoir initilisé game avant
/// @param is_sherif si vrai, n'as pas de taches et a une arme dès le départ
Crewmate::Crewmate(float x, float y, bool is_sherif) :
	Amogus(x, y),
	armed(is_sherif),
	nbTaskCleared(0),
	ind_next_task(-1)
{
	if (!is_sherif)
	{
		// attribution des Task
		int nbTask = Game::get_nbTaskPerCrewmate();
		lstTasks.reserve(nbTask);
		for (int i = 0; i < nbTask; i++)
		{
			lstTasks.push_back(Game::get_TaskById(i)); // a modifier 
		}
	}

	// initialisation des info
	int nbAmogus = Game::get_nbAmogus();
	lstInfo.resize(nbAmogus);
	lstInfo[id].sus = 0; // suspition envers soit-meme a zéro
}

Crewmate::~Crewmate()
{
	lstTasks.clear(); // Les taches seront free par la classe game
	lstInfo.clear(); // pas des pointeurs donc pas besoin de free
}

int Crewmate::is_armed() {return armed;}

int Crewmate::get_nbTaskCleared() {return nbTaskCleared;}

/// @brief Déplace le crewmate en fonction du contexte
/// @param offset Distance parcouru en une unité de temps
void Crewmate::findNextDest(float offset)
{
	if(!armed)
	{
		//On observe si le crewmate a une tâche en tête auquelle il pourrait se diriger, dans le cas contraire, on essaie de lui en trouver un tant qu'il existe encore des tâches à faire
		if((ind_next_task == -1) && (nbTaskCleared < Game::get_nbTaskPerCrewmate()))
		{
			//Comme le crewmate n'a pas d'objectif en tête (ou alors perdu de vue), on parcourt l'ensemble des tâches pour essayer de lui en trouver un
			int id_task = -1;
			int ind = 0;
			float min_dist = 99999999.;
			for(Task * curr : lstTasks)
			{
				/*On vérifie que la tâche la plus proche soit visible par le crewmate
				 (on part du principe que lstTasks contient que des tâches non réalisés par le crewmate, dès qu'une tâche est réalisé, on la supprime de la liste)*/
				Vect pos_task = curr->get_position(); //copie bit à bit
				float dist_sq_task = pos_task.dist_sq(position);
				if((pos_task.in(position, distVision)) && (dist_sq_task < min_dist))
				{
					id_task = ind;
					min_dist = dist_sq_task;
				} 
				ind++;
			}
			ind_next_task = id_task;
		}

		
		if(ind_next_task == -1 && destination == nullptr) //Plus de tâche à faire ou aucunes tâches en vision
		{
			//Appel méthode roam (se balader)
		}
		else /*Il a un objectif, on vérifie maintenant les joueurs autour afin de savoir 
			 si le crewmate peut se déplacer librement vers la tâche ou alors doit se méfie des autres Amogus et se déplace autrement*/
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
					float dist_sq_amogus = pos_amogus.dist(position);
					if((pos_amogus.in(position, distVision)) && (dist_sq_amogus < min_dist)) //Amogus différent de soi-même visible du champ de vision
					{
						min_dist = dist_sq_amogus;
						ind_sus = i;
					}
				}
			}

			//On vérifie si un quelconque Amogus est visible ou non
			
			if((ind_sus != -1) && lstInfo[ind_sus].sus >= DEFAULT_avoid) //-> On s'éloigne d'un pas s'il est trop suspect
			{
				Vect pos_amogus = Game::get_AmogusById(ind_sus)->get_position();
				if((pos_amogus.get_x() > position.get_x()) && ((position.get_x()-offset) >= (DRAW_RADIUS/2)))
				{
					position.set_x(position.get_x()-offset);
				}
				else if((pos_amogus.get_x() < position.get_x()) && ((position.get_x()+offset) <= SCREEN_WIDTH-(DRAW_RADIUS/2)))
				{
					position.set_x(position.get_x()+offset);
				}
				if((pos_amogus.get_y() > position.get_y()) && ((position.get_y()-offset) >= (DRAW_RADIUS/2)))
				{
					position.set_y(position.get_y()-offset);
				}
				else if((pos_amogus.get_y() < position.get_y()) && ((position.get_y()+offset) <= SCREEN_HEIGHT-(DRAW_RADIUS/2)))
				{
					position.set_y(position.get_y()+offset);
				}

			}
			else//-> On se dirige d'un pas vers la tâche
			{
				Vect pos_task = Game::get_TaskById(ind_next_task)->get_position();
				if((pos_task.get_x() > position.get_x()) && ((position.get_x()+offset) <= SCREEN_WIDTH-(DRAW_RADIUS/2)))
				{
					position.set_x(position.get_x()+offset);
				}
				else if((pos_task.get_x() < position.get_x()) && ((position.get_x()-offset) >= (DRAW_RADIUS/2)))
				{
					position.set_x(position.get_x()-offset);
				}
				if((pos_task.get_y() > position.get_y())&& ((position.get_y()+offset) <= SCREEN_HEIGHT-(DRAW_RADIUS/2)))
				{
					position.set_y(position.get_y()+offset);
				}
				else if((pos_task.get_y() < position.get_y()) && ((position.get_y()-offset) >= (DRAW_RADIUS/2)))
				{
					position.set_y(position.get_y()-offset);
				}
			}

		}

		
	}
	else
	{
		//Appel méthode roam (se balader)
	}
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