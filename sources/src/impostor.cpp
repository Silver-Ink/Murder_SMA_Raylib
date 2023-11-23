#include "to_include.hpp"

Impostor::Impostor(double v, double i, double vit, bool w, int c, bool k, Vect pos) : Amogus(v, i, vit, w, pos){
    cooldown = c;
    knowledge = k;
}

/*getter*/
int Impostor::get_cooldown() {return cooldown;}
bool Impostor::get_knowledge() {return knowledge;}

/*setter*/
void Impostor::set_cooldown(int c) {cooldown = c;}
void Impostor::set_knowledge(bool k) {knowledge = k;}