#ifndef DEF_IMPOSTOR
#define DEF_IMPOSTOR

#include "./amogus.hpp"

class Impostor : public Amogus
{
    private:
        int cooldown;
        bool knowledge;
    public:
        /*constructeur*/
        Impostor(double v, double i, double vit, bool w, int c, bool k, Vect pos);
        /*getter*/
        int get_cooldown();
        bool get_knowledge();
        /*setter*/
        void set_cooldown(int value);
        void set_knowledge(bool value);

};


#endif