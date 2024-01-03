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
        static Texture2D sprite;
        // -> rajouter un id comme pour amogus
    public:
        //constructeur
        Task();
        Task(float x, float y, int durees);
        static Texture2D sprite;
        //getter
        Vect get_position();
        int get_duree();
        //setter
        void set_position(Vect pos);
        void set_duree(int duree);
        static int getNextFreeId();
        //autre
        void draw();
        static void initAnim();
};



#endif