#include "to_include.hpp"

/// @brief a utiliser pour créer un crewmate sans task et sans infos
/// et en dehors du jeu
Crewmate::Crewmate() : Amogus(100, 100) {}

/// @brief Nécessite d'avoir initilisé game avant
/// @param is_sherif si vrai, n'as pas de taches et a une arme dès le départ
Crewmate::Crewmate(float x, float y, bool is_sherif) :
	Amogus(x, y),
	armed(is_sherif),
	nbTaskCleared(0)
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

void Crewmate::findNextDest()
{
	// a redéfinir
}