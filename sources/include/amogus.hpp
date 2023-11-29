#ifndef DEF_AMONGUS
#define DEF_AMONGUS


class Amogus
{
    protected: 
        Vector2 position;
        double vision;
        double interaction;
        double vitesse;
        bool weapon;
        bool alive;
    public:
        /*constructeur*/
        Amogus(double v, double i, double vit, bool w, Vector2 pos, bool life);
        /*getter*/
        Vector2 get_position();
        double get_vision();
        double get_interaction();
        double get_vitesse();
        bool isArmed();
        bool isAlive();
        /*setter*/
        void set_position(Vector2 pos);
        void set_vision(double v);
        void set_interaction(double interaction);
        void set_vitesse(double v);
        void setArmed(bool w);
        void setAlive(bool life);
        /*autre*/
        void move(); //à modifier en cas de présence d'arguments
};

#endif