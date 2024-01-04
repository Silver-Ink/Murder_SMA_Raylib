#ifndef DEF_CREWMATE
#define DEF_CREWMATE

#include "to_include.hpp"

class Crewmate : public Amogus
{
	static float const DEFAULT_avoid; //définit le seuil de suspicion auquel on doit fuir l'Amogus concerné
	static Color const CrewmateColor;
	bool * taskDone;
	static Color const SherifColor;
	int occupe;
	int action;
	int cooldown_pasBouger;
	int nbTaskCleared;
	int ind_pp_task;
	bool armed;
	int ind_next_task; /*Indice de la tâche que compte réaliser le crewmate 
						-> évite d'avoir à parcourir l'ens des tâches à chaque itération du jeu 
						tant que le crewmate voit toujours son objectif*/

	vector<Task*> lstTasks;
	vector<Information> lstInfo;
	void checkDead(int id);
	int get_most_sus();


public:
	int get_nbTaskCleared();
	int is_armed();

	Crewmate();
	Crewmate(float x, float y, bool is_sherif = false);

	~Crewmate();

	vector<Task*> getTask();
	int PlusProcheTask();
	void deplacer(float offset, Vect pos_task);
	void fuir(int ind_sus);
 	void setTask(const vector<Task*> & listeTask);
	virtual void findNextDest() override;
	virtual const Color& getRoleColor() override;
};

#endif
