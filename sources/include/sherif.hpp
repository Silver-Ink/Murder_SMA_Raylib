#ifndef DEF_SHERIF
#define DEF_SHERIF

#include "amogus.hpp"

class Sherif : public Amogus
{
    private :
        int cooldown;
    public:
        /*constructeur*/
        Sherif();
        Sherif(double v, double i , double vit, bool w , int c, Vector2 pos, bool life);
        /*getter*/
        int get_cooldown();
        /*setter*/
        void set_cooldown(int);
};

#endif