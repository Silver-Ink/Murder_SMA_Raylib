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
        float vitesse;
        bool weapon;
        bool alive;

        Color highlightColor;

        // NE PAS ENLEVER
        // // UP        0
        // // RIGHT     1
        // // DOWN      2
        // // LEFT      3
        // int dir;
    public:
        // static Spritesheet* s_bg  ;
        // static Spritesheet* s_body;
        // static Anim lstAnimBG[4];
        // static Anim lstAnimBody[4];
        // constructeur
        Amogus();
        Amogus(float x, float y, bool weapon=false);

        // getter
        Vect get_position();
        float get_vision();
        float get_interaction();
        float get_vitesse();
        bool isArmed();
        bool isAlive();
        // setter
        void set_position(Vect pos);
        void set_vision(float v);
        void set_interaction(float dist_interract);
        void set_vitesse(float v);
        void setArmed(bool w);
        void setAlive(bool life);
        // autre
        void move(Vect* destination); //à modifier en cas de présence d'arguments
        virtual void update();
        virtual void draw();
        // virtual void findNextDest() = 0;
        void drawDest();




        // NE PAS ENLEVER
        // void draw(int t);

        // static
        // static void initAnim();
};

#endif