#ifndef DEF_TASK
#define DEF_TASK

#include "to_include.hpp"

class Task
{
    protected:
        Vector2 position;
        int duree;
    public:
        /*constructeur*/
        Task();
        Task(Vector2 position, int duree);
        /*getter*/
        Vector2 get_position();
        int get_duree();
        /*setter*/
        void set_position(Vector2 pos);
        void set_duree(int duree);
        /*autre*/
        void move(); //à modifier en cas de présence d'arguments
};



#endif