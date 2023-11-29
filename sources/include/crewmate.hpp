#ifndef DEF_CREWMATE
#define DEF_CREWMATE

#include "amogus.hpp"
#include "task.hpp"

class Crewmate : public Amogus
{
    
    private:
        int nb_task;
        double proba;
    public:
        /*constructeur*/
        Crewmate();
        Crewmate(double v, double i, double vit, bool w, Vector2 pos, int nt, bool life);
        /*getter*/
        int get_nb_task();
        double get_proba();
        /*setter*/
        void set_nb_task(int nb_task);
        void set_proba(double proba);
};


#endif