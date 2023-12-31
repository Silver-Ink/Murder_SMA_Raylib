#ifndef DEF_AMONGUS
#define DEF_AMONGUS

#include "to_include.hpp"

#define AMOGUS_WIDTH 50
//Pour gérer les effets de bord lors d'un mouvement


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
        Vect dest_prioritaire;

        float distVision;
        float distInterract;
        float speed;
        bool alive;
        int type;

        Color highlightColor;
        int id;
        /// @brief Si vrai, se déplace vers la position contenue dans destination
        /// Si faux, se déplace vers dest_prioritaire
        bool follow_dest;

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
        static Texture2D deadSprite;
        // constructeur
        Amogus();
        Amogus(float x, float y, int type);

        // getter
        Vect& get_position();
        float get_vision();
        float get_interaction();
        float get_speed();
        int get_type();
        bool isAlive();
        static int getNextFreeId();
        // setter
        void set_position(Vect pos);
        void set_vision(float v);
        void set_interaction(float dist_interract);
        void set_speed(float v);
        void die();
        // autre

        ///vérifie si le amogus en vue est mort

        // Méthode abstraite qui determine la prochaine destination a suivre
        void setDestination(Vect* dest); 

        /// @brief Suit une destination prioritaire tant que follow_dest est faux
        /// @param dest position a suivre
        void moveToward(Vect dest);
        /// @brief Suit une destination prioritaire tant que follow_dest est faux
        void moveToward(float angle_dir, float distance);

        virtual void findNextDest() = 0;
        virtual const Color& getRoleColor() = 0;
        virtual void update(float dt);

        void updateFacingDir(Vect& direction);

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