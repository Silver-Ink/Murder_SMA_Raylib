#ifndef DEF_AMONGUS
#define DEF_AMONGUS

#include "to_include.hpp"

#define AMOGUS_WIDTH 50

class Amogus
{
    //const
    public:
        static float const DEFAULT_distVision;
        static float const DEFAULT_distInterract;
        static float const DEFAULT_vitesse;

        static float const DRAW_RADIUS;
        static float const DRAW_OUTLINE_RADIUS;

    protected: 
        
        Vect position;
        // Pointeur vers une position, qui permet de suivre une position mouvante
        Vect* destination;

        float distVision;
        float distInterract;
        float speed;
        bool alive;

        Color highlightColor;
        int id;

        static int nextFreeID;
        // NE PAS ENLEVER
        // // DOWN      0
        // // RIGHT     1
        // // UP        2
        // // LEFT      3
        int dir;
    public:
        static Spritesheet* s_bg  ;
        static Spritesheet* s_body;
        static Anim* lstAnimBG;
        static Anim* lstAnimBody;
        // constructeur
        Amogus();
        Amogus(float x, float y);

        // getter
        Vect& get_position();
        float get_vision();
        float get_interaction();
        float get_speed();
        bool isAlive();
        static int getNextFreeId();
        // setter
        void set_position(Vect pos);
        void set_vision(float v);
        void set_interaction(float dist_interract);
        void set_speed(float v);
        void setAlive(bool life);
        // autre
        void moveToward(Vect* dest); //à modifier en cas de présence d'arguments
        // Méthode abstraite qui determine la prochaine destination a suivre
        virtual void findNextDest() = 0;
        virtual void update(float dt);

        virtual void draw();
        void drawDest();
        void drawVisionRange();
        void drawInteractRange();





        // NE PAS ENLEVER
        // void draw(int t);

        // static
        static void initAnim();
};

#endif