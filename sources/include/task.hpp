#ifndef DEF_TASK
#define DEF_TASK

#include "to_include.hpp"

class Task
{
    protected:
        Vect position;
        int duree;
        int id;
        static int nextFreeID;
    public:
        //constructeur
        Task();
        Task(float x, float y, int durees);
        //getter
        Vect get_position();
        int get_duree();
        //setter
        void set_position(Vect pos);
        void set_duree(int duree);
        static int getNextFreeId();
};



#endif