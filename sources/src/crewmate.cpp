#include "to_include.hpp"

/// @brief a utiliser pour créer un crewmate sans task et sans infos
/// et en dehors du jeu
Crewmate::Crewmate() : Amogus(100, 100, 0) {}

/// @brief Nécessite d'avoir initilisé game avant
/// @param is_sherif si vrai, n'as pas de taches et a une arme dès le départ
Crewmate::Crewmate(float x, float y, bool is_sherif) :
	Amogus(x, y, 0),
	armed(is_sherif),
	nbTaskCleared(0)
{
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

vector<Task*> Crewmate::getTask()
{
	return lstTasks;
}

void Crewmate::setTask(const vector<Task*>& listeTask)
{
	lstTasks = listeTask;
}