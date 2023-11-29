#include "to_include.hpp"

Impostor::Impostor():Impostor(1, 1, 1, 1, 15, 0, Vect{0., 0.}, 1) {}

Impostor::Impostor(double v, double i, double vit, bool w, int c, bool k, Vect pos, bool life) : Amogus(v, i, vit, w, pos, life){
    cooldown = c;
    knowledge = k;
}

/*getter*/
int Impostor::get_cooldown() {return cooldown;}
bool Impostor::get_knowledge() {return knowledge;}

/*setter*/
void Impostor::set_cooldown(int c) {cooldown = c;}
void Impostor::set_knowledge(bool k) {knowledge = k;}