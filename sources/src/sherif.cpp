#include "to_include.hpp"

Sherif::Sherif(double v, double i, double vit, bool w, int c, Vect pos) : Amogus(v, i, vit, w, pos){
    cooldown = c;
}

/*getter*/
int Sherif::get_cooldown(){return cooldown;}
/*setter*/
void Sherif::set_cooldown(int coold){cooldown = coold;}