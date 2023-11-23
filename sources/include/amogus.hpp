#ifndef DEF_AMONGUS
#define DEF_AMONGUS


class Amogus
{
    
    protected: 
        Vect position;
        double vision;
        double interaction;
        double vitesse;
        bool weapon;
    public:
        /*constructeur*/
        Amogus(double v, double i, double vit, bool w, Vect pos);
        /*getter*/
        Vect get_position();
        double get_vision();
        double get_interaction();
        double get_vitesse();
        bool isArmed();
        /*setter*/
        void set_position(Vect pos);
        void set_vision(double v);
        void set_interaction(double interaction);
        void set_vitesse(double v);
        void setArmed(bool w);
        /*autre*/
        void move(); //à modifier en cas de présence d'arguments
};

#endif