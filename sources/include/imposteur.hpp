#ifndef DEF_IMPOSTEUR
#define DEF_IMPOSTEUR
#include "to_include.hpp"

class Imposteur : public Amogus{
	public:
		//const
		static Color const ImposteurColor;


		Imposteur();
		Imposteur(float x, float y, int i);
		virtual void findNextDest() override;
		virtual const Color& getRoleColor() override;
};

#endif