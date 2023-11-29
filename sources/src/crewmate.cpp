#include "to_include.hpp"

Crewmate::Crewmate():Crewmate(1, 1, 1, 0, Vect {0.,0.}, 5, 1) {}

Crewmate::Crewmate(double v, double i, double vit, bool w, Vect pos, int nt, bool life) : Amogus(v, i, vit, w, pos, life)
{
    nb_task = nt;
}

/*getter*/
int Crewmate::get_nb_task(){return nb_task;}

/*setter*/
void Crewmate::set_nb_task(int nt){nb_task = nt;}
