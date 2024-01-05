#ifndef DEF_IMPOSTEUR
#define DEF_IMPOSTEUR
#include "to_include.hpp"

class Imposteur : public Amogus{
	public:
		//const
		int action;
		bool chasser;
		int cooldown_pasBouger;
		int cooldown_kill;
		int id_victime;
		static Color const ImposteurColor;
		Imposteur();
		Imposteur(float x, float y, int i);
		void chase();
		void kill();
		virtual void findNextDest() override;
		virtual const Color& getRoleColor() override;
};

#endif