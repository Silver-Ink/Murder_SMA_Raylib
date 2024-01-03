#ifndef DEF_IMPOSTEUR
#define DEF_IMPOSTEUR
#include "to_include.hpp"

class Imposteur : public Amogus{
	public:
		Imposteur();
		Imposteur(float x, float y, int i);
		virtual void findNextDest(float offset);
};

#endif