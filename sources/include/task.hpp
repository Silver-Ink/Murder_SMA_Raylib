#ifndef DEF_TASK
#define DEF_TASK

#include "to_include.hpp"

class Task
{
    protected:
        Vect position;
        int duree;
    public:
        /*constructeur*/
        Task();
        Task(Vect position, int duree);
        /*getter*/
        Vect get_position();
        int get_duree();
        /*setter*/
        void set_position(Vect pos);
        void set_duree(int duree);
        /*autre*/
        void move(); //à modifier en cas de présence d'arguments
};



#endif