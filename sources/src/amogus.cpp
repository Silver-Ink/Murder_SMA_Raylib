#include "to_include.hpp"

Amogus::Amogus(double v, double i, double vit, bool w, Vect pos){
    position = pos;
    vision = v;
    interaction = i;
    vitesse = vit;
    weapon = w;
}

/*getter*/
Vect Amogus::get_position() {return position;}
double Amogus::get_vision(){return vision;}
double Amogus::get_interaction(){return interaction;}
double Amogus::get_vitesse(){return vitesse;}
bool Amogus::isArmed(){return weapon;}

/*setter*/
void Amogus::set_position(Vect pos) {position = pos;}
void Amogus::set_interaction(double i){interaction = i;}
void Amogus::set_vision(double v){vision = v;}
void Amogus::set_vitesse(double v){vitesse = v;}
void Amogus::setArmed(bool w){weapon = w;}
