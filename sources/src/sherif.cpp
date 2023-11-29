#include "to_include.hpp"

Sherif::Sherif():Sherif(1, 1, 1, 1, 15, Vect{0., 0.}, 1) {}

Sherif::Sherif(double v, double i, double vit, bool w, int c, Vect pos, bool life) : Amogus(v, i, vit, w, pos, life){
    cooldown = c;
}

/*getter*/
int Sherif::get_cooldown(){return cooldown;}
/*setter*/
void Sherif::set_cooldown(int coold){cooldown = coold;}