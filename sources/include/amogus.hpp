#ifndef DEF_AMONGUS
#define DEF_AMONGUS

#include "to_include.hpp"

class Amogus
{
    protected: 
        Vect position;
        double vision;
        double interaction;
        double vitesse;
        bool weapon;
        bool alive;
    public:
        /*constructeur*/

        Amogus(double v, double i, double vit, bool w, Vect pos, bool life);
        /*getter*/
        Vect get_position();
        double get_vision();
        double get_interaction();
        double get_vitesse();
        bool isArmed();
        bool isAlive();
        /*setter*/
        void set_position(Vect pos);
        void set_vision(double v);
        void set_interaction(double interaction);
        void set_vitesse(double v);
        void setArmed(bool w);
        void setAlive(bool life);
        /*autre*/
        void move(); //à modifier en cas de présence d'arguments
};

#endif