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
        //getter
        Vect& get_position();
        Vect* get_adr_position();
        int get_duree();
        int get_taskId();
        //setter
        void set_position(Vect pos);
        void set_duree(int duree);
        static int getNextFreeId();
        //autre
        void draw();
        static void initAnim();
};



#endif