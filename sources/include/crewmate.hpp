#ifndef DEF_CREWMATE
#define DEF_CREWMATE

#include "to_include.hpp"

class Crewmate : public Amogus{

	int nbTaskCleared;
	bool armed;

	vector<Task*> lstTasks;
	vector<Information> lstInfo;

public:
	int get_nbTaskCleared();
	int is_armed();

	Crewmate();
	Crewmate(float x, float y, bool is_sherif = false);

	~Crewmate();

	virtual void findNextDest() override;

};

#endif
