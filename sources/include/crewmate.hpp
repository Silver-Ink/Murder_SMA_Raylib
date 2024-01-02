#ifndef DEF_CREWMATE
#define DEF_CREWMATE

#include "to_include.hpp"

class Crewmate : public Amogus{
	static float const DEFAULT_avoid; //définit le seuil de suspicion auquel on doit fuir l'Amogus concerné

	int nbTaskCleared;
	bool armed;
	int ind_next_task; /*Indice de la tâche que compte réaliser le crewmate 
						-> évite d'avoir à parcourir l'ens des tâches à chaque itération du jeu 
						tant que le crewmate voit toujours son objectif*/

	vector<Task*> lstTasks;
	vector<Information> lstInfo;

public:
	int get_nbTaskCleared();
	int is_armed();

	Crewmate();
	Crewmate(float x, float y, bool is_sherif = false);

	~Crewmate();

	virtual void findNextDest(float offset) override;

};

#endif
