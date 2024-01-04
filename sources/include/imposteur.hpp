#ifndef DEF_IMPOSTEUR
#define DEF_IMPOSTEUR
#include "to_include.hpp"

class Imposteur : public Amogus{
	public:
		//const
		int action;
		bool chasser;
		int cooldown_pasBouger;
		static Color const ImposteurColor;


		Imposteur();
		Imposteur(float x, float y, int i);
		bool chase();
		virtual void findNextDest(float offset) override;
		virtual const Color& getRoleColor() override;
};

#endif