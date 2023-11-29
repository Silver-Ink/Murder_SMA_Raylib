#ifndef DEF_SHERIF
#define DEF_SHERIF

#include "to_include.hpp"

class Sherif : public Amogus
{
    private :
        int cooldown;
    public:
        /*constructeur*/
        Sherif();
        Sherif(double v, double i , double vit, bool w , int c, Vect pos, bool life);
        /*getter*/
        int get_cooldown();
        /*setter*/
        void set_cooldown(int);
};

#endif