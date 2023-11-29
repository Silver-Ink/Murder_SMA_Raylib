#include "to_include.hpp"

Amogus::Amogus(double v, double i, double vit, bool w, Vector2 pos, bool life){
    alive = life;
    position = pos;
    vision = v;
    interaction = i;
    vitesse = vit;
    weapon = w;
}

/*getter*/
Vector2 Amogus::get_position() {return position;}
double Amogus::get_vision(){return vision;}
double Amogus::get_interaction(){return interaction;}
double Amogus::get_vitesse(){return vitesse;}
bool Amogus::isArmed(){return weapon;}
bool Amogus::isAlive(){return alive;}

/*setter*/
void Amogus::set_position(Vector2 pos) {position = pos;}
void Amogus::set_interaction(double i){interaction = i;}
void Amogus::set_vision(double v){vision = v;}
void Amogus::set_vitesse(double v){vitesse = v;}
void Amogus::setArmed(bool w){weapon = w;}
void Amogus::setAlive(bool life) {alive = life;}
