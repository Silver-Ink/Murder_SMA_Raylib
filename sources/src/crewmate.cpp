#include "to_include.hpp"

Crewmate::Crewmate(double v, double i, double vit, bool w, Vect pos, int nt) : Amogus(v, i, vit, w, pos)
{
    nb_task = nt;
}

/*getter*/
int Crewmate::get_nb_task(){return nb_task;}

/*setter*/
void Crewmate::set_nb_task(int nt){nb_task = nt;}
